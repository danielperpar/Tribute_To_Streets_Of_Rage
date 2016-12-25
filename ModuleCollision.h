#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include <list>
#include "Module.h"
#include "ModuleParticles.h"
#include "Globals.h"

// TODO 9: Create a matrix of game specific types of collision for early discard
// Example: lasers should not collide with lasers but should collider with walls
// enemy shots will collide with other enemies ? and against walls ?

struct Collider
{
	SDL_Rect rect = { 0,0,0,0 };
	bool to_delete = false;
	collider_type c_type;
	Particle *particle;

	// TODO 10: Add a way to notify other classes that a collision happened

	Collider(SDL_Rect rectangle, Particle *particle, collider_type c_type) : // expand this call if you need to
		rect(rectangle), particle(particle), c_type(c_type)
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

	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	Collider* AddCollider(const SDL_Rect& rect, Particle *particle, collider_type c_type);
	void DebugDraw();

private:

	std::list<Collider*> colliders;
	bool debug = false;
};

#endif // __ModuleCollision_H__