#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "AIController.h"
#include "ModuleEnemies.h"
#include <iostream>
using namespace std;

ModuleCollision::ModuleCollision()
{
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

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
					if ((*it1)->m_collider_type != (*it2)->m_collider_type)
					{
						if (!((*it1)->m_collider_type == BOSS_ENEMY_HIT && (*it2)->m_collider_type == WEAPON ||
							(*it1)->m_collider_type == WEAPON && (*it2)->m_collider_type == BOSS_ENEMY_HIT ||

							(*it1)->m_collider_type == BOSS_ENEMY_GRAB && (*it2)->m_collider_type == WEAPON ||
							(*it1)->m_collider_type == WEAPON && (*it2)->m_collider_type == BOSS_ENEMY_GRAB ||

							(*it1)->m_collider_type == COMMON_ENEMY_HIT && (*it2)->m_collider_type == FOOD ||
							(*it1)->m_collider_type == FOOD && (*it2)->m_collider_type == COMMON_ENEMY_HIT ||

							(*it1)->m_collider_type == COMMON_ENEMY_GRAB && (*it2)->m_collider_type == FOOD ||
							(*it1)->m_collider_type == FOOD && (*it2)->m_collider_type == COMMON_ENEMY_GRAB ||

							(*it1)->m_collider_type == COMMON_ENEMY_HIT && (*it2)->m_collider_type == WEAPON ||
							(*it1)->m_collider_type == WEAPON && (*it2)->m_collider_type == COMMON_ENEMY_HIT ||

							(*it1)->m_collider_type == COMMON_ENEMY_GRAB && (*it2)->m_collider_type == WEAPON ||
							(*it1)->m_collider_type == WEAPON && (*it2)->m_collider_type == COMMON_ENEMY_GRAB ||

							(*it1)->m_collider_type == COMMON_ENEMY_GRAB && (*it2)->m_collider_type == COMMON_ENEMY_HIT ||
							(*it1)->m_collider_type == COMMON_ENEMY_HIT && (*it2)->m_collider_type == COMMON_ENEMY_GRAB
							)

							)
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
	
	if (collider1->m_collider_type == COMMON_ENEMY_HIT || collider2->m_collider_type == COMMON_ENEMY_HIT) {
		
		App->enemies->m_enemy->m_ai_walk = false;
		App->enemies->m_enemy->m_ai_attack = true;
		
	}



	/*Collider* laserCollider = nullptr;
	Collider* playerCollider = nullptr;
	Collider* wallCollider = nullptr;

	switch (collider1->c_type)
	{
	case collider_type::LASER:
	laserCollider = collider1;
	break;
	case collider_type::PLAYER:
	playerCollider = collider1;
	break;
	case collider_type::WALL:
	wallCollider = collider1;
	break;
	}

	switch (collider2->c_type)
	{
	case collider_type::LASER:
	laserCollider = collider2;
	break;
	case collider_type::PLAYER:
	playerCollider = collider2;
	break;
	case collider_type::WALL:
	wallCollider = collider2;
	break;
	}

	if (laserCollider != nullptr)
	{
	laserCollider->particle->to_delete = true;
	laserCollider->to_delete = true;
	App->particles->AddParticle(*(App->particles->explosionParticle), laserCollider->rect.x, laserCollider->rect.y, collider_type::EXPLOSION);
	}

	if (playerCollider != nullptr)
	{
	destroyed = true;
	playerCollider->to_delete = true;
	App->particles->AddParticle(*(App->particles->explosionParticle), playerCollider->rect.x, playerCollider->rect.y, collider_type::EXPLOSION);

	App->fade->FadeToBlack((Module*)App->scene_intro, (Module*)App->scene_space);
	}*/
}
