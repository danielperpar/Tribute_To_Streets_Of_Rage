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
	SDL_Rect m_rect = { 0,0,0,0 };
	bool m_to_delete = false;
	collider_type m_collider_type;
	Entity *m_entity;

	

	Collider(SDL_Rect rectangle, Entity *entity, collider_type c_type) : 
		m_rect(rectangle), m_entity(entity), m_collider_type(c_type)
	{}

	void SetPos(int x, int y)
	{
		m_rect.x = x;
		m_rect.y = y;
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

	Collider* AddCollider(const SDL_Rect& rect, Entity *entity, collider_type c_type);
	void DebugDraw();

private:

	std::list<Collider*> colliders;
	int* m_collision_matrix;
	bool debug = false;
	
	Uint32 m_time = 0;
	Uint32 m_update_time = 0;
	Uint32 m_dt = 10;
	bool m_do_logic = true;
};

#endif // __ModuleCollision_H__