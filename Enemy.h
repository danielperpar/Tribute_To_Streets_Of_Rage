#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Animation.h"
#include <list>
#include "Entity.h"
#include "Point.h"
#include "AIController.h"


enum class enemy_state
{
	IDLE,
	WALKING,
	PUNCH1,
	PUNCH2,
	KNIFE_ATTACK,
	GROUND_ATTACK,
	WHIP_ATTACK,
	KICK,
	THROW_BOOMERANG,
	RECOVER_BOOMERANG
	
};



struct SDL_Texture;
class Enemy : public Entity {

public:
	Enemy(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth);


public:
	
	enemy_state m_state;
	bool m_face_right = true;
	float m_speed = 1.0f;
	size_t m_timer_count = 0;
	size_t m_timer_speed = 0;
	bool m_restart_animation = true;

	size_t m_ground_attack_range = 50;
	size_t m_ground_attack_speed = 1;

	size_t m_punch_hits = 0;

	iPoint m_start_position;
	bool m_boomerang_forward = true;
	
	float m_t_acum = 0;

	//updated by the colision module
	int m_life = 100;
	bool m_dead = false;
	bool m_player_to_hit = true;
	bool m_carrying_boomerang = true;

	//AI signals
	bool m_ai_idle = true;
	bool m_ai_walk = true;
	bool m_ai_attack = false;
	bool m_ai_throw_boomerang = false;

	//Axis X origin taken from the upper left vertex related to the rectangle containing the enemy sprite to the enemy's back neck position
	size_t m_x_ref = 70;

	AIController m_ai_controller;

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

	Animation m_npc_antonio_throw_boomerang_right;
	Animation m_npc_antonio_throw_boomerang_left;

	Animation m_npc_antonio_recover_boomerang_right;
	Animation m_npc_antonio_recover_boomerang_left;

	Animation m_npc_item_boomerang_right;
	Animation m_npc_item_boomerang_left;
	
	Animation m_npc_boomerang_shadow_right;
	Animation m_npc_boomerang_shadow_left;

	void AdvanceAnimation(size_t initial_sprite_duration, Animation *next_anim_sprite, bool restart_animation);

private:
	std::list<int*> m_animation_list;

};

#endif // !__ENEMY_H__


