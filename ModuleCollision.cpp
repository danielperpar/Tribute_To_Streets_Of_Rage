#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "Player.h"
#include "Garcia.h"
#include "Antonio.h"
#include "ModuleSceneRound1.h"
#include "Enemy.h"

using namespace std;

ModuleCollision::ModuleCollision()
{
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

bool ModuleCollision::Start()
{
	memset(collision_matrix, 0, sizeof(int) * 49);
	
	collision_matrix[ENEMY_BODY][PLAYER_BODY] = 1;
	collision_matrix[ENEMY_BODY][PLAYER_HIT] = 1;
	collision_matrix[ENEMY_BODY][DESTROYABLE] = 1;
	collision_matrix[ENEMY_HIT][PLAYER_BODY] = 1;
	collision_matrix[PLAYER_BODY][ENEMY_BODY] = 1;
	collision_matrix[PLAYER_BODY][ENEMY_HIT] = 1;
	collision_matrix[PLAYER_BODY][DESTROYABLE] = 1;
	collision_matrix[PLAYER_BODY][BOOMERANG] = 1;
	collision_matrix[PLAYER_HIT][ENEMY_BODY] = 1;
	collision_matrix[PLAYER_HIT][DESTROYABLE] = 1;
	collision_matrix[DESTROYABLE][ENEMY_BODY] = 1;
	collision_matrix[DESTROYABLE][PLAYER_BODY] = 1;
	collision_matrix[BOOMERANG][PLAYER_BODY] = 1;
	collision_matrix[PLAYER_BODY][HEALTH_CHICKEN] = 1;
	collision_matrix[HEALTH_CHICKEN][PLAYER_BODY] = 1;

	return true;
}

update_status ModuleCollision::PreUpdate()
{
	
	CollisionInfo ci1;
	CollisionInfo ci2;
	//update player collision status
	bool erased = false;

	Player *the_player = App->player->the_player;
	for (list<std::pair<CollisionInfo, CollisionInfo>>::iterator it = the_player->player_collision_status.begin(); it != the_player->player_collision_status.end();)
	{
		erased = false;
		if ((*it).second.collider->to_delete)
		{			
			the_player->OnCollisionExit(*it);
			it = the_player->player_collision_status.erase(it);
			erased = true;
		}
		else
		{
			if ((*it).first.collider->type == collider_type::PLAYER_BODY)
			{
				bool collision = the_player->body_collider->CheckCollision((*it).second.collider, ci1, ci2);
				if (!collision)
				{
					the_player->OnCollisionExit(*it);

					it = the_player->player_collision_status.erase(it);
					erased = true;
				}
			}
			else if ((*it).first.collider->type == collider_type::PLAYER_HIT)
			{
				bool collision = the_player->hit_collider->CheckCollision((*it).second.collider, ci1, ci2);
				if (!collision)
				{				
					it = the_player->player_collision_status.erase(it);
					erased = true;
				}
			}
		}

		if (!erased)
			it++;

	}

	//update enemy hit collider status
	std::list<Entity*> &dynamics = App->scene_round1->dynamic_entities;
	Enemy *enemy = nullptr;
	for (std::list<Entity*>::iterator it = dynamics.begin(); it != dynamics.end(); it++)
	{
		if ((*it)->type == entity_type::GARCIA || (*it)->type == entity_type::ANTONIO)
		{
			if ((*it)->type == entity_type::GARCIA)
			{
				enemy = (Garcia*)(*it);
			}
			else if ((*it)->type == entity_type::ANTONIO)
			{
				enemy = (Antonio*)(*it);
			}

			if (enemy->hit_collider_status.collider != nullptr)
			{
				if (enemy->hit_collider_status.collider->to_delete)
				{
					enemy->OnCollisionExit(enemy->hit_collider_status);
					enemy->hit_collider_status.collider = nullptr;
				}
				else
				{
					bool collision = enemy->hit_collider->CheckCollision(enemy->hit_collider_status.collider, ci1, ci2);
					if (!collision)
					{
						enemy->OnCollisionExit(enemy->hit_collider_status);
						enemy->hit_collider_status.collider = nullptr;
					}
				}				
			}		
		}
	}
	

	// Remove all colliders scheduled for deletion
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update()
{
	for (list<Collider*>::iterator it1 = colliders.begin(); it1 != colliders.end(); it1++)
	{
		for (list<Collider*>::iterator it2 = it1; it2 != colliders.end();)
		{
			if (colliders.end() != ++it2)
			{
				if (collision_matrix[(*it1)->type][(*it2)->type] == 1)		
				{
					bool collision = (*it1)->CheckCollision(*it2, collision_info1, collision_info2);
					if (collision)
					{
						//DEBUG
						//LOG("it1 = (%d, %d, %d, %d) it2=(%d, %d, %d, %d)", (*it1)->m_rect.x, (*it1)->m_rect.y, (*it1)->m_rect.w, (*it1)->m_rect.h, (*it2)->m_rect.x, (*it2)->m_rect.y, (*it2)->m_rect.w, (*it2)->m_rect.h)
						OnCollision(collision_info1, collision_info2);
					}
				}
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (debug == true)
		DebugDraw();
	
	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
	{
		if((*it)->type == collider_type::PLAYER_BODY || (*it)->type == collider_type::PLAYER_HIT)
			App->renderer->DrawQuad((*it)->rect, 0, 255, 0, 80);
		else if ((*it)->type == collider_type::ENEMY_BODY || (*it)->type == collider_type::ENEMY_HIT)
			App->renderer->DrawQuad((*it)->rect, 255, 0, 0, 80);
		else //Draw health chicken collider
			App->renderer->DrawQuad((*it)->rect, 255, 0, 255, 90);
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders ");

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	colliders.clear();

	//RELEASE_ARRAY(collision_matrix);

	return true;
}

Collider* ModuleCollision::AddCollider(const SDL_Rect& rect, Entity *entity, collider_type col_t)
{
	Collider* ret = new Collider(rect, entity, col_t);

	colliders.push_back(ret);

	return ret;
}

void ModuleCollision::OnCollision(const CollisionInfo &col_info1, const CollisionInfo &col_info2) const
{
	NotifyCollision(col_info1, col_info2);
	NotifyCollision(col_info2, col_info1);
}

void ModuleCollision::NotifyCollision(const CollisionInfo &col_info1, const CollisionInfo &col_info2) const
{
	const Collider *collider1 = col_info1.collider;
	const Collider *collider2 = col_info2.collider;
	Enemy *enemy = nullptr;

	switch (collider1->type)
	{
		case collider_type::PLAYER_BODY:
		case collider_type::PLAYER_HIT:
		{
			Player *player = (Player*)(collider1->entity);
			player->OnCollision(col_info1, col_info2);
			break;
		}
		case collider_type::ENEMY_HIT:
		{
			if (collider1->entity->type == entity_type::GARCIA)
			{
				enemy = (Garcia*)(collider1->entity);
			}
			else if (collider1->entity->type == entity_type::ANTONIO)
			{
				enemy = (Antonio*)(collider1->entity);
			}

			enemy->OnCollision(col_info1, col_info2);
			break;
		}
	}
}
// -----------------------------------------------------

bool Collider::CheckCollision(const Collider *collider, CollisionInfo &col_info1, CollisionInfo &col_info2) const
{
	SDL_Rect r = collider->rect;

	//Each collider will receive info about its collision.
	//collision_info1 is related to "this" collider, collision_info2 is related to the other collider

	CollisionInfo collision_info1 = CollisionInfo(this, contact_direction::LEFT, contact_direction::DOWN);
	CollisionInfo collision_info2 = CollisionInfo(collider, contact_direction::LEFT, contact_direction::DOWN);

	bool collisionX = false;
	bool collisionY = false;

	if (r.x >= this->rect.x)
	{
		if (r.x - this->rect.x <= this->rect.w)
		{
			collisionX = true;
			collision_info1.contact_direction_x = contact_direction::RIGHT;
			collision_info2.contact_direction_x = contact_direction::LEFT;
		}
	}
	else
	{
		if (this->rect.x - r.x <= r.w)
		{
			collisionX = true;
			collision_info1.contact_direction_x = contact_direction::LEFT;
			collision_info2.contact_direction_x = contact_direction::RIGHT;
		}
	}

	if (r.y >= this->rect.y)
	{
		if (r.y - this->rect.y <= this->rect.h) 
		{
			collisionY = true;
			collision_info1.contact_direction_y = contact_direction::DOWN;
			collision_info2.contact_direction_y = contact_direction::UP;
		}
	}
	else
	{
		if (this->rect.y - r.y <= r.h)
		{
			collisionY = true;
			collision_info1.contact_direction_y = contact_direction::UP;
			collision_info2.contact_direction_y = contact_direction::DOWN;
		}
	}

	
	col_info1 = collision_info1;
	col_info2 = collision_info2;
	

	return collisionX && collisionY;

}




