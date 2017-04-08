#ifndef __GARCIA_H__
#define __GARCIA_H__

#include "Entity.h"
#include "Enemy.h"

class Animation;
class GarciaFSM;
class Garcia : public Enemy
{

private:
	std::list<int*> m_animation_list;
	GarciaFSM *garcia_fsm = nullptr;

public:
	Garcia(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	Garcia(const Garcia &garcia);
	~Garcia();
	virtual void UpdateFSM();

public:
	
	size_t m_punch_hits = 0;

	Animation m_npc_garcia_idle_right;
	Animation m_npc_garcia_idle_left;

	Animation m_npc_garcia_walk_right;
	Animation m_npc_garcia_walk_left;

	Animation m_npc_garcia_punch_right1;
	Animation m_npc_garcia_punch_right2;

	Animation m_npc_garcia_punch_left1;
	Animation m_npc_garcia_punch_left2;

	Animation m_npc_garcia_damage_received_right;
	Animation m_npc_garcia_damage_received_left;

	Animation m_npc_garcia_down_right;
	Animation m_npc_garcia_down_left;

	Animation m_npc_garcia_up_right;
	Animation m_npc_garcia_up_left;



};


#endif
