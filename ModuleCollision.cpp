#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "AIController.h"
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
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_collision_matrix[i][j] = 0;
		}
	}

	m_collision_matrix[COMMON_ENEMY_HIT][PLAYER] = 1;
	m_collision_matrix[COMMON_ENEMY_GRAB][PLAYER] = 1;
	m_collision_matrix[BOSS_ENEMY_HIT][PLAYER] = 1;
	m_collision_matrix[BOSS_ENEMY_GRAB][PLAYER] = 1;
	m_collision_matrix[WEAPON][PLAYER] = 1;
	m_collision_matrix[FOOD][PLAYER] = 1;
	m_collision_matrix[PLAYER][COMMON_ENEMY_HIT] = 1;
	m_collision_matrix[PLAYER][COMMON_ENEMY_GRAB] = 1;
	m_collision_matrix[PLAYER][BOSS_ENEMY_HIT] = 1;
	m_collision_matrix[PLAYER][BOSS_ENEMY_GRAB] = 1;
	m_collision_matrix[PLAYER][WEAPON] = 1;
	m_collision_matrix[PLAYER][FOOD] = 1;
	m_collision_matrix[PLAYER][BOSS_BOOMERANG] = 1;
	m_collision_matrix[PLAYER][BOSS_BOOMERANG_AREA] = 1;
	m_collision_matrix[PLAYER][DESTROYABLE_ITEM] = 1;
	m_collision_matrix[BOSS_BOOMERANG][PLAYER] = 1;
	m_collision_matrix[BOSS_BOOMERANG_AREA][PLAYER] = 1;
	m_collision_matrix[DESTROYABLE_ITEM][PLAYER] = 1;

	
	return true;
}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->m_to_delete == true)
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
	m_time = SDL_GetTicks();
	if (m_time - m_update_time >= m_dt)
	{
		m_do_logic = true;
	}
	if (m_do_logic)
	{
		m_do_logic = false;
		m_update_time = SDL_GetTicks();


		for (list<Collider*>::iterator it1 = colliders.begin(); it1 != colliders.end(); ++it1)
		{
			for (list<Collider*>::iterator it2 = it1; it2 != colliders.end();)
			{
				if (colliders.end() != ++it2)
				{
					if (m_collision_matrix[(*it1)->m_collider_type][(*it2)->m_collider_type] == 1)
					{
						bool collision = (*it1)->CheckCollision((*it2)->m_rect);
						if (collision)
						{
							//DEBUG
							LOG("it1 = (%d, %d, %d, %d) it2=(%d, %d, %d, %d)", (*it1)->m_rect.x, (*it1)->m_rect.y, (*it1)->m_rect.w, (*it1)->m_rect.h, (*it2)->m_rect.x, (*it2)->m_rect.y, (*it2)->m_rect.w, (*it2)->m_rect.h)
								(*it1)->OnCollision(*it1, *it2);
						}
					}
				}
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
			debug = !debug;

		if (debug == true)
			DebugDraw();
	}
	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		App->renderer->DrawQuad((*it)->m_rect, 255, 0, 0, 80);
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	colliders.clear();

	return true;
}

Collider* ModuleCollision::AddCollider(const SDL_Rect& rect, Entity *entity, collider_type c_type)
{
	Collider* ret = new Collider(rect, entity, c_type);

	colliders.push_back(ret);

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	// TODO 7: Create by hand (avoid consulting the internet) a simple collision test
	// Return true if the argument and the own rectangle are intersecting
	bool collisionX = false;
	bool collisionY = false;

	if (r.x >= this->m_rect.x)
	{
		if (r.x - this->m_rect.x <= this->m_rect.w)
			collisionX = true;
	}
	else
	{
		if (this->m_rect.x - r.x <= r.w)
			collisionX = true;
	}

	if (r.y >= this->m_rect.y)
	{
		if (r.y - this->m_rect.y <= this->m_rect.h) {
			collisionY = true;
		}
	}
	else
	{
		if (this->m_rect.y - r.y <= r.h)
			collisionY = true;
	}

	return collisionX && collisionY;

}

void Collider::OnCollision(Collider* collider1, Collider* collider2) const
{
	//collision between player and enemy
	if (collider1->m_collider_type == COMMON_ENEMY_HIT || collider2->m_collider_type == COMMON_ENEMY_HIT) 
	{
		Collider* enemy_collider = collider1->m_entity->m_type == entity_type::ENEMY ? collider1 : collider2;
		((Enemy*)(enemy_collider->m_entity))->m_ai_walk = false;
		((Enemy*)(enemy_collider->m_entity))->m_ai_attack = true;

		App->player->m_player->m_enemy_attacking_player = ((Enemy*)(enemy_collider->m_entity));
		App->player->m_player->m_enemy_at_range = ((Enemy*)(enemy_collider->m_entity));
	}

	
	

	//if (collider1->m_collider_type == BOSS_BOOMERANG_AREA || collider2->m_collider_type == BOSS_BOOMERANG_AREA) {
	//	//throw boomerang special attack
	//	App->enemies->m_enemy->m_ai_walk = false;
	//	App->enemies->m_enemy->m_ai_attack = true;

	//}

}
