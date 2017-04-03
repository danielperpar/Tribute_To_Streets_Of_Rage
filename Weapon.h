#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Entity.h"
#include "Point.h"

struct SDL_Texture;
class Animation;
class Weapon : public Entity{

public:
	Weapon(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	
public:	

	bool m_taken;
	size_t m_hits_made;


};


#endif // !__WEAPON_H__

