#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Animation.h"
#include <list>
#include "Entity.h"
#include "Point.h"


enum class enemy_state
{
	IDLE,
	WALKING_RIGHT,
	WALKING_LEFT,
	WALKING_UP,
	WALKING_DOWN,
};



struct SDL_Texture;
class Enemy : public Entity {

public:
	Enemy(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth);


public:
	bool m_dead;
	int m_life;
	enemy_state m_state;
	bool m_face_right = false;
	float m_speed = 1.0f;

	Animation *m_current_animation = nullptr;

	Animation m_npc_garcia_idle_right;
	Animation m_npc_garcia_idle_left;

	Animation m_npc_garcia_walk_right;
	Animation m_npc_garcia_walk_left;

	Animation m_npc_garcia_punch_right1;
	Animation m_npc_garcia_punch_right2;
	Animation m_npc_garcia_punch_left1;
	Animation m_npc_garcia_punch_left2;
	
	size_t m_npc_garcia_punch_duration = 10;

	Animation m_npc_garcia_knife_attack_right;
	Animation m_npc_garcia_knife_attack_left;



private:
	std::list<int*> m_animation_list;

};

#endif // !__ENEMY_H__


