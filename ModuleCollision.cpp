#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
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
	// TODO 8: Check collisions between all colliders. 
	// After making it work, review that you are doing the minumum checks possible
	for (list<Collider*>::iterator it1 = colliders.begin(); it1 != colliders.end(); ++it1)
	{
		for (list<Collider*>::iterator it2 = it1; it2 != colliders.end();)
		{
			if (colliders.end() != ++it2)
			{
				if ((*it1)->c_type != (*it2)->c_type)
				{
					if (!((*it1)->c_type == LASER && (*it2)->c_type == PLAYER || (*it1)->c_type == PLAYER && (*it2)->c_type == LASER))
					{
						bool collision = (*it1)->CheckCollision((*it2)->rect);
						if (collision)
						{
							//DEBUG
							LOG("it1 = (%d, %d, %d, %d) it2=(%d, %d, %d, %d)", (*it1)->rect.x, (*it1)->rect.y, (*it1)->rect.w, (*it1)->rect.h, (*it2)->rect.x, (*it2)->rect.y, (*it2)->rect.w, (*it2)->rect.h)
							(*it1)->OnCollision(*it1, *it2);
						}
					}
				}
			}
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(debug == true)
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
	LOG("Freeing all colliders");

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	colliders.clear();

	return true;
}

Collider* ModuleCollision::AddCollider(const SDL_Rect& rect, Particle *particle, collider_type c_type)
{
	Collider* ret = new Collider(rect, particle, c_type);

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
	App->player->OnCollision(collider1, collider2);
}
