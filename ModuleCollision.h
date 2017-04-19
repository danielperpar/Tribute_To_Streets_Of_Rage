#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include <list>
#include <set>
#include "Module.h"
#include "ModuleParticles.h"
#include "Globals.h"

class Entity;
class Enemy;
struct Collider
{
	SDL_Rect rect = { 0,0,0,0 };
	bool to_delete = false;
	collider_type type;
	Entity *entity;

	Collider() {}

	Collider(SDL_Rect rectangle, Entity *entity, collider_type col_t) : 
		rect(rectangle), entity(entity), type(col_t)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
	void OnCollision(Collider* collider1, Collider* collider2) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	bool Start();
	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	Collider* AddCollider(const SDL_Rect& rect, Entity *entity, collider_type col_t);
	void DebugDraw();

private:

	std::list<Collider*> colliders;
	int collision_matrix[7][7];
	bool debug = false;
	
};

#endif // __ModuleCollision_H__