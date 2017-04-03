#include "Weapon.h"

Weapon::Weapon(SDL_Texture *texture, 
	Animation *curr_anim, 
	const char *name, 
	entity_type type, 
	iPoint position, int depth) : Entity(texture, curr_anim, name, type, position, depth), m_taken(false), m_hits_made(0) {}