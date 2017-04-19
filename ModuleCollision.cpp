#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include <iostream>
using namespace std;

ModuleCollision::ModuleCollision()
{
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

bool ModuleCollision::Start()
{
	//collision_matrix = new int[100];
	memset(collision_matrix, 0, sizeof(int) * 49);
	
	collision_matrix[ENEMY_BODY][PLAYER_BODY] = 1;
	collision_matrix[ENEMY_BODY][PLAYER_HIT] = 1;
	collision_matrix[ENEMY_BODY][DESTROYABLE] = 1;
	collision_matrix[ENEMY_HIT][PLAYER_BODY] = 1;
	collision_matrix[COLLECTABLE][PLAYER_BODY] = 1;
	collision_matrix[PLAYER_BODY][ENEMY_BODY] = 1;
	collision_matrix[PLAYER_BODY][ENEMY_HIT] = 1;
	collision_matrix[PLAYER_BODY][COLLECTABLE] = 1;
	collision_matrix[PLAYER_BODY][DESTROYABLE] = 1;
	collision_matrix[PLAYER_BODY][BOSS_AOE] = 1;
	collision_matrix[PLAYER_HIT][ENEMY_BODY] = 1;
	collision_matrix[PLAYER_HIT][DESTROYABLE] = 1;
	collision_matrix[DESTROYABLE][ENEMY_BODY] = 1;
	collision_matrix[DESTROYABLE][PLAYER_BODY] = 1;
	collision_matrix[BOSS_AOE][PLAYER_BODY] = 1;

	return true;
}

update_status ModuleCollision::PreUpdate()
{
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
	
	//Update collisions between enemies and player
	/*for (std::list<Entity*>::iterator it = App->entities.begin(); it != App->entities.end(); it++)
	{
		if ((*it)->type == entity_type::ENEMY)
		{
			bool collision = App->player->m_player_collider->CheckCollision(((Enemy*)*it)->m_enemy_hit_collider->m_rect);
			if (!collision)
				((Enemy*)*it)->m_enemy_to_hit = false;
		}
	}*/

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update()
{
	//for (list<Collider*>::iterator it1 = colliders.begin(); it1 != colliders.end(); ++it1)
	//{
	//	for (list<Collider*>::iterator it2 = it1; it2 != colliders.end();)
	//	{
	//		if (colliders.end() != ++it2)
	//		{
	//			//if (m_collision_matrix[(*it1)->m_collider_type][(*it2)->m_collider_type] == 1)
	//			if (m_collision_matrix[(*it1)->m_collider_type * 10 + (*it2)->m_collider_type] == 1)
	//			{
	//				bool collision = (*it1)->CheckCollision((*it2)->m_rect);
	//				if (collision)
	//				{
	//					//DEBUG
	//					//LOG("it1 = (%d, %d, %d, %d) it2=(%d, %d, %d, %d)", (*it1)->m_rect.x, (*it1)->m_rect.y, (*it1)->m_rect.w, (*it1)->m_rect.h, (*it2)->m_rect.x, (*it2)->m_rect.y, (*it2)->m_rect.w, (*it2)->m_rect.h)
	//						(*it1)->OnCollision(*it1, *it2);
	//				}
	//			}
	//		}
	//	}
	//}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (debug == true)
		DebugDraw();
	
	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		App->renderer->DrawQuad((*it)->rect, 255, 0, 0, 80);
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

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	
	bool collisionX = false;
	bool collisionY = false;

	if (r.x >= this->rect.x)
	{
		if (r.x - this->rect.x <= this->rect.w)
			collisionX = true;
	}
	else
	{
		if (this->rect.x - r.x <= r.w)
			collisionX = true;
	}

	if (r.y >= this->rect.y)
	{
		if (r.y - this->rect.y <= this->rect.h) {
			collisionY = true;
		}
	}
	else
	{
		if (this->rect.y - r.y <= r.h)
			collisionY = true;
	}

	return collisionX && collisionY;

}

void Collider::OnCollision(Collider* collider1, Collider* collider2) const
{
	////collision between player and enemy
	//if (collider1->m_collider_type == COMMON_ENEMY_HIT || collider2->m_collider_type == COMMON_ENEMY_HIT ||
	//	collider1->m_collider_type == COMMON_ENEMY_RANGED_ATTACK || collider2->m_collider_type == COMMON_ENEMY_RANGED_ATTACK
	//	) 
	//{
	//	Collider* enemy_collider = collider1->m_entity->type == entity_type::ENEMY ? collider1 : collider2;
	//	((Enemy*)(enemy_collider->m_entity))->m_ai_walk = false;
	//	((Enemy*)(enemy_collider->m_entity))->m_ai_attack = true;
	//	

	//	if(enemy_collider->m_collider_type != COMMON_ENEMY_RANGED_ATTACK && App->player->player->depth == ((Enemy*)(enemy_collider->m_entity))->depth)
	//		((Enemy*)(enemy_collider->m_entity))->m_enemy_to_hit = true;
	//}

	
	

	//if (collider1->m_collider_type == BOSS_BOOMERANG_AREA || collider2->m_collider_type == BOSS_BOOMERANG_AREA) {
	//	//throw boomerang special attack
	//	App->enemies->m_enemy->m_ai_walk = false;
	//	App->enemies->m_enemy->m_ai_attack = true;

	//}

}
