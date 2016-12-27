#ifndef __FOOD_H__
#define __FOOD_H__

#include "Entity.h"
#include "Point.h"

struct SDL_Texture;
class Food : public Entity{
public:
	Food(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth);

public:	
	bool m_taken;
};



#endif // !__FOOD_H__

