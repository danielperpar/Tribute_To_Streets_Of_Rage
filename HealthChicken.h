#ifndef __HEALTH_CHICKEN_H__
#define __HEALTH_CHICKEN_H__

#include "Entity.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL.h"

class HealthChicken : public Entity
{

private:
	std::list<int*> animation_list;

public:
	HealthChicken(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int m_depth);
	HealthChicken(const HealthChicken &chicken);
	virtual ~HealthChicken();
	void LoadSprite();
	void LoadCollider();
	
	Collider *chicken_collider = nullptr;
	SDL_Rect chicken_collider_rect;
	Animation chicken_animation;

};




#endif
