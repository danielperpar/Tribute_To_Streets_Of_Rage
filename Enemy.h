#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Animation.h"
#include <list>
#include "Entity.h"
#include "Point.h"


enum class enemy_state
{
	IDLE,
	WALKING,
	WALKING_RIGHT,
	WALKING_LEFT,
	WALKING_UP,
	WALKING_DOWN,
	PUNCH1,
	PUNCH2,
	KNIFE_ATTACK,
	GROUND_ATTACK,
	WHIP_ATTACK,
	KICK
	
};



struct SDL_Texture;
class Enemy : public Entity {

public:
	Enemy(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth);


public:
	bool m_dead = false;
	bool m_player_to_hit = true;
	int m_life;
	enemy_state m_state;
	bool m_face_right = true;
	float m_speed = 1.0f;
	size_t m_timer_count = 0;
	size_t m_timer_speed = 0;
	bool m_restart_animation = true;

	size_t m_ground_attack_range = 50;
	size_t m_ground_attack_speed = 1;

	size_t m_punch_hits = 0;

	bool m_carrying_boomerang = true;

	Animation *m_current_animation = nullptr;

	Animation m_npc_garcia_idle_right;
	Animation m_npc_garcia_idle_left;

	Animation m_npc_garcia_walk_right;
	Animation m_npc_garcia_walk_left;

	Animation m_npc_garcia_punch_right1;
	Animation m_npc_garcia_punch_right2;
	Animation m_npc_garcia_punch_left1;
	Animation m_npc_garcia_punch_left2;
	
	Animation m_npc_garcia_knife_idle_right;
	Animation m_npc_garcia_knife_idle_left;

	Animation m_npc_garcia_knife_walk_right;
	Animation m_npc_garcia_knife_walk_left;

	Animation m_npc_garcia_knife_attack_right;
	Animation m_npc_garcia_knife_attack_left;

	Animation m_npc_punky_idle_right;
	Animation m_npc_punky_idle_left;

	Animation m_npc_punky_walk_right;
	Animation m_npc_punky_walk_left;

	Animation m_npc_punky_ground_attack_right;
	Animation m_npc_punky_ground_attack_left;

	Animation m_npc_nora_idle_right;
	Animation m_npc_nora_idle_left;

	Animation m_npc_nora_walk_right;
	Animation m_npc_nora_walk_left;

	Animation m_npc_nora_attack_right;
	Animation m_npc_nora_attack_left;

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

	void AdvanceAnimation(size_t initial_sprite_duration, Animation *next_anim_sprite, bool restart_animation);

private:
	std::list<int*> m_animation_list;

};

#endif // !__ENEMY_H__


