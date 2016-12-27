#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"

enum class entity_type
{
	FOOD,
	WEAPON,
	DESTROYABLE_ITEM,
	PLAYER,
	ENEMY
};

struct SDL_Texture;
class Entity {

public:
	Entity(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int m_depth);

	virtual ~Entity();

public:
	const char *m_name = nullptr;
	entity_type m_type;
	iPoint m_position;
	int m_depth;
	SDL_Texture *texture = nullptr;
};



#endif // !ENTITY_H

