#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"

enum class entity_type
{
	FOOD,
	WEAPON,
	DESTROYABLE_ITEM,
	PLAYER,
	GARCIA,
	GARCIA_KNIFE,
	NORA,
	ANTONIO,
	PARTICLE
};

struct SDL_Texture;
class Entity {

public:
	Entity(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int m_depth);
	Entity();
	virtual ~Entity();

public:
	const char *m_name = nullptr;
	entity_type m_type;
	iPoint m_position = { 0,0 };
	int m_depth = 0;
	SDL_Texture *m_texture = nullptr;
};



#endif // !ENTITY_H

