#ifndef __NORA_H__
#define __NORA_H__

#include "Entity.h"
#include "Enemy.h"

class Animation;
class Nora : public Enemy
{
public:
	Nora(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	Nora(const Nora &nora);
	~Nora();


public:

	Animation m_npc_nora_idle_right;
	Animation m_npc_nora_idle_left;

	Animation m_npc_nora_walk_right;
	Animation m_npc_nora_walk_left;

	Animation m_npc_nora_attack_right1;
	Animation m_npc_nora_attack_right2;
	Animation m_npc_nora_attack_left1;
	Animation m_npc_nora_attack_left2;

private:
	std::list<int*> m_animation_list;

};


#endif // !__NORA_H__

