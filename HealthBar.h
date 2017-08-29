#ifndef __HEALT_BAR_H__
#define __HEALTH_BAR_H__

#include "Entity.h"

class HealthBar : public Entity
{
public:
	HealthBar(int starting_width, SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int m_depth);
	virtual ~HealthBar();	
	void ScaleHPBar(int health, int max_health);

	int starting_width = 0;

};

#endif