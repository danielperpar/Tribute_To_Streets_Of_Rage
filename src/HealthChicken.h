#ifndef __HEALTH_CHICKEN_H__
#define __HEALTH_CHICKEN_H__

#include "Entity.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "../3rdparty/SDL/include/SDL.h"

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
	void LoadOffset();

	void OnPickup();
	
	int depth_offset = 46;
	int depth_margin = 3;
	Collider *chicken_collider = nullptr;
	SDL_Rect chicken_collider_rect;
	Animation chicken_animation;

};




#endif
