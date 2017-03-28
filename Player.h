#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include <list>
#include "Entity.h"
#include "Point.h"

class Enemy;
enum class player_state
{
	START,
	IDLE,
	IDLE_S_PRESSED,
	WALKING,
	JUMPING,
	JUMPING_KICKING,
	PUNCH,
	PUNCHING_COMBO_1,
	PUNCHING_COMBO_2,
	PUNCHING_COMBO_3,
	BACK_PUNCHING,
	GRAB,
	GRAB_KICK,
	GRAB_HEAD_HIT,
	GRAB_AIR_SPIN_RIGHT,
	GRAB_AIR_SPIN_LEFT,
	GRAB_AIR_SPIN_FINISHER_RIGHT,
	GRAB_AIR_SPIN_FINISHER_LEFT,
	WEAPON_PIPE_IDLE,
	WEAPON_PIPE_WALKING,
	WEAPON_PIPE_ATTACK_LEFT,
	WEAPON_PIPE_ATTACK_RIGHT,
	WEAPON_KNIFE_IDLE,
	WEAPON_KNIFE_WALKING,
	WEAPON_KNIFE_ATTACK_LEFT,
	WEAPON_KNIFE_ATTACK_RIGHT,
	DAMAGED,
	DAMAGED_FLOATING,
	UP,
	DEAD

};




struct SDL_Texture;
class Player : public Entity{

public:
	Player(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth);

public:
	
	
	bool facing_right = true;
	float m_speed = 1.0f;

	bool m_jump_up = true;
	iPoint m_jump_start_pos;
	float m_jump_speed = 1.0f;
	int m_max_jump_height = 36;
	bool m_jumping = false;

	size_t m_kick_hits = 0;
	bool m_continue_combo_grab = false;
	
	float m_timer_count = 0.0f;
	float m_timer_speed = 1.0f;

	float m_combo_timer = 0.0f;

	bool m_in_combo_time = true;
	size_t m_punch_combo_hits = 0;
	
	bool m_carrying_weapon_pipe = false;
	bool m_carrying_weapon_knife = false;

	bool m_restart_animation = true;

	bool m_float_attack = false;

	bool m_looking_each_other = false;

	bool m_dead = false;
	int m_life = 100;

	size_t m_down_accel = 2;
	size_t m_down_vel = 1;
	size_t m_down_count = 0;
	size_t m_down_frames = 30;
	size_t m_down_update_count = 0;
	size_t m_down_update_time = 6;
	
	//enemy who hits player
	Enemy *m_enemy_attacking_player = nullptr;

	//Axis X origin taken from the upper left vertex related to the rectangle containing the player sprite to the player's back neck position
	size_t m_x_ref = 70;

	player_state m_state = player_state::IDLE;

	Animation idle_right1;
	Animation idle_right2;
	Animation idle_right3;
	Animation idle_left1;
	Animation idle_left2;
	Animation idle_left3;
	
	Animation walk_right;
	Animation walk_left;

	Animation jump_right1;
	Animation jump_right2;
	Animation jump_left1;
	Animation jump_left2;
	
	Animation air_kick_right;
	Animation air_kick_left;

	Animation punch_combo_right1;
	Animation punch_combo_right2;
	Animation punch_combo_right3;
	Animation punch_combo_left1;
	Animation punch_combo_left2;
	Animation punch_combo_left3;

	size_t punch_combo_timeout = 15;

	Animation back_punch_right1;
	Animation back_punch_right2;
	
	Animation back_punch_left1;
	Animation back_punch_left2;

	
	Animation grab_right;
	Animation grab_kick_head_combo_right1;
	Animation grab_kick_head_combo_right2;


	Animation grab_left;
	Animation grab_kick_head_combo_left1;
	Animation grab_kick_head_combo_left2;

	Animation grab_air_spin_combo_right1;
	Animation grab_air_spin_combo_right2;
	Animation grab_air_spin_combo_right3;
	Animation grab_air_spin_combo_right4;
	Animation grab_air_spin_combo_right5;
	Animation grab_air_spin_combo_right6;
	Animation grab_air_spin_combo_right7;

	Animation grab_air_spin_combo_left1;
	Animation grab_air_spin_combo_left2;
	Animation grab_air_spin_combo_left3;
	Animation grab_air_spin_combo_left4;
	Animation grab_air_spin_combo_left5;
	Animation grab_air_spin_combo_left6;
	Animation grab_air_spin_combo_left7;

	Animation grab_air_spin_combo_finisher_right1;
	Animation grab_air_spin_combo_finisher_right2;
	Animation grab_air_spin_combo_finisher_right3;
	
	Animation grab_air_spin_combo_finisher_left1;
	Animation grab_air_spin_combo_finisher_left2;
	Animation grab_air_spin_combo_finisher_left3;

	Animation weapon_pipe_idle_right;
	Animation weapon_pipe_walk_right;
	Animation weapon_pipe_attack_right;
	Animation weapon_pipe_throw_right;

	Animation weapon_pipe_idle_left;
	Animation weapon_pipe_walk_left;
	Animation weapon_pipe_attack_left;
	Animation weapon_pipe_throw_left;

	Animation weapon_knife_idle_right;
	Animation weapon_knife_walk_right;
	Animation weapon_knife_attack_right;
	Animation weapon_knife_throw_right;

	Animation weapon_knife_idle_left;
	Animation weapon_knife_walk_left;
	Animation weapon_knife_attack_left;
	Animation weapon_knife_throw_left;

	Animation damage_received_right;
	Animation damage_received_left;

	Animation down_right;
	Animation down_left;

	Animation up_right;
	Animation up_left;

	Animation *current_animation;

	
private:
	std::list<int*> m_animation_list;

};

#endif // !__PLAYER_H__

