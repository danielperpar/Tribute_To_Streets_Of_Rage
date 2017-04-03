#ifndef __PUNKY_H__
#define __PUNKY_H__

#include "Entity.h"
#include "Enemy.h"

class Punky : public Enemy
{
public:
	Punky(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	Punky(const Punky &punky);
	~Punky();


public:

	size_t m_ground_attack_range = 50;
	size_t m_ground_attack_speed = 1;


	Animation m_npc_punky_idle_right;
	Animation m_npc_punky_idle_left;

	Animation m_npc_punky_walk_right;
	Animation m_npc_punky_walk_left;

	Animation m_npc_punky_ground_attack_right1;
	Animation m_npc_punky_ground_attack_right2;
	Animation m_npc_punky_ground_attack_left1;
	Animation m_npc_punky_ground_attack_left2;

private:
	std::list<int*> m_animation_list;

};


#endif
