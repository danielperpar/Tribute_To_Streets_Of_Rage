#ifndef __FOOD_H__
#define __FOOD_H__

#include "Entity.h"
#include "Point.h"

struct SDL_Texture;
class Animation;
class Food : public Entity{
public:
	Food(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);

public:	
	bool m_taken;
};



#endif // !__FOOD_H__

