#ifndef __ANTONIO_H__
#define __ANTONIO_H__

#include "Enemy.h"
#include "Entity.h"

class Animation;
class Antonio : public Enemy
{

public:
	Antonio(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	Antonio(const Antonio &antonio);
	~Antonio();


public:

	bool m_carrying_boomerang = false;
	bool m_ai_throw_boomerang = false;

	Particle *m_boomerang = nullptr;

	Animation m_npc_antonio_boomerang_idle_right;
	Animation m_npc_antonio_boomerang_idle_left;

	Animation m_npc_antonio_idle_right;
	Animation m_npc_antonio_idle_left;

	Animation m_npc_antonio_boomerang_walk_right;
	Animation m_npc_antonio_boomerang_walk_left;

	Animation m_npc_antonio_walk_right;
	Animation m_npc_antonio_walk_left;

	Animation m_npc_antonio_kick_right;
	Animation m_npc_antonio_kick_left;

	Animation m_npc_antonio_throw_boomerang_right;
	Animation m_npc_antonio_throw_boomerang_left;

	Animation m_npc_antonio_recover_boomerang_right;
	Animation m_npc_antonio_recover_boomerang_left;

private:
	std::list<int*> m_animation_list;
};



#endif