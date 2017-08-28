#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include <list>
#include <set>
#include "Module.h"
#include "ModuleParticles.h"
#include "Globals.h"

enum collider_type
{
	ENEMY_BODY,
	ENEMY_HIT,
	PLAYER_BODY,
	PLAYER_HIT,
	DESTROYABLE,
	BOOMERANG,
	HEALTH_CHICKEN
};

enum contact_direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};


class Entity;
struct CollisionInfo;
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

	bool CheckCollision(const Collider *collider, CollisionInfo &col_info1, CollisionInfo &col_info2) const;
	
	
};

struct CollisionInfo
{
public:
	CollisionInfo() : collider(nullptr), contact_direction_x(contact_direction::DOWN), contact_direction_y(contact_direction::DOWN) {}
	
	CollisionInfo(const Collider *col, contact_direction cdx, contact_direction cdy) : collider(col), contact_direction_x(cdx), contact_direction_y(cdy){}
	
	CollisionInfo(const CollisionInfo &col_info)
	{
		collider = col_info.collider;
		contact_direction_x = col_info.contact_direction_x;
		contact_direction_y = col_info.contact_direction_y;
	}
	
	CollisionInfo& operator=(CollisionInfo col_info)
	{
		collider = col_info.collider;
		contact_direction_x = col_info.contact_direction_x;
		contact_direction_y = col_info.contact_direction_y;
		return (*this);

	}

	const Collider *collider;
	contact_direction contact_direction_x;
	contact_direction contact_direction_y;
};

class ModuleCollision : public Module
{
public:

	CollisionInfo collision_info1 = CollisionInfo(nullptr, contact_direction::LEFT, contact_direction::DOWN);
	CollisionInfo collision_info2 = CollisionInfo(nullptr, contact_direction::LEFT, contact_direction::DOWN);

	ModuleCollision();
	~ModuleCollision();

	bool Start();
	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	Collider* AddCollider(const SDL_Rect& rect, Entity *entity, collider_type col_t);
	void DebugDraw();
	void OnCollision(const CollisionInfo &col_info1, const CollisionInfo &col_info2) const;

private:

	std::list<Collider*> colliders;
	int collision_matrix[7][7];
	bool debug = false;
	void NotifyCollision(const CollisionInfo &col_info1, const CollisionInfo &col_info2) const;
};

#endif // __ModuleCollision_H__