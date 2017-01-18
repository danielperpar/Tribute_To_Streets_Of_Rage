#ifndef __GARCIAKNIFE_H__
#define __GARCIAKNIFE_H__

#include "Entity.h"
#include "Enemy.h"

class GarciaKnife : Enemy
{
public:
	GarciaKnife(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth);
	~GarciaKnife();



public:
	AIController m_ai_controller;

	Animation *m_current_animation = nullptr;

	Animation m_npc_garcia_knife_idle_right;
	Animation m_npc_garcia_knife_idle_left;

	Animation m_npc_garcia_knife_walk_right;
	Animation m_npc_garcia_knife_walk_left;

	Animation m_npc_garcia_knife_attack_right;
	Animation m_npc_garcia_knife_attack_left;

private:
	std::list<int*> m_animation_list;
};


#endif


