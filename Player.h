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
	
	
	bool m_face_right = true;
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

	bool m_continue_combo = false;
	size_t m_upper_punch_hits = 0;
	
	bool m_carrying_weapon_pipe = false;
	bool m_carrying_weapon_knife = false;

	bool m_restart_animation = true;

	bool m_float_attack = false;

	int m_max_screen_pos_y = 150;
	int m_min_screen_pos_y = 90;
	int m_max_screen_pos_x = 3870;
	int m_min_screen_pos_x = 700;

	//updated by the colision module
	Enemy *m_enemy_at_range = nullptr;
	bool m_enemy_to_grab = false;
	bool m_enemy_alive = true;
	bool m_dead = false;
	int m_life = 100;
	
	//enemy who hits player
	Enemy *m_enemy_attacking_player = nullptr;

	//Axis X origin taken from the upper left vertex related to the rectangle containing the player sprite to the player's back neck position
	size_t m_x_ref = 70;

	player_state m_state = player_state::IDLE;

	Animation m_idle_right1;
	Animation m_idle_right2;
	Animation m_idle_right3;
	Animation m_idle_left1;
	Animation m_idle_left2;
	Animation m_idle_left3;
	size_t m_idle1_duration = 150;
	size_t m_idle2_duration = 25;
	size_t m_idle3_duration = 25;

	Animation m_walk_right;
	Animation m_walk_left;

	Animation m_jump_right1;
	Animation m_jump_right2;
	Animation m_jump_left1;
	Animation m_jump_left2;
	size_t m_jump1_duration = 10;
	size_t m_jump2_duration = 10;

	Animation m_air_kick_right;
	Animation m_air_kick_left;

	Animation m_punch_combo_right1;
	Animation m_punch_combo_right2;
	Animation m_punch_combo_right3;
	Animation m_punch_combo_left1;
	Animation m_punch_combo_left2;
	Animation m_punch_combo_left3;

	size_t m_punch_combo_duration = 9;
	size_t m_punch_combo_timeout = 15;

	Animation m_back_punch_right1;
	Animation m_back_punch_right2;
	
	Animation m_back_punch_left1;
	Animation m_back_punch_left2;

	size_t m_back_punch_duration = 10;


	Animation m_grab_right;
	Animation m_grab_kick_head_combo_right1;
	Animation m_grab_kick_head_combo_right2;

	size_t m_grab_kick_head_duration = 10;

	Animation m_grab_left;
	Animation m_grab_kick_head_combo_left1;
	Animation m_grab_kick_head_combo_left2;

	Animation m_grab_air_spin_combo_right1;
	Animation m_grab_air_spin_combo_right2;
	Animation m_grab_air_spin_combo_right3;
	Animation m_grab_air_spin_combo_right4;
	Animation m_grab_air_spin_combo_right5;
	Animation m_grab_air_spin_combo_right6;
	Animation m_grab_air_spin_combo_right7;

	Animation m_grab_air_spin_combo_left1;
	Animation m_grab_air_spin_combo_left2;
	Animation m_grab_air_spin_combo_left3;
	Animation m_grab_air_spin_combo_left4;
	Animation m_grab_air_spin_combo_left5;
	Animation m_grab_air_spin_combo_left6;
	Animation m_grab_air_spin_combo_left7;

	size_t m_grab_air_spin_duration = 10;

	Animation m_grab_air_spin_combo_finisher_right1;
	Animation m_grab_air_spin_combo_finisher_right2;
	Animation m_grab_air_spin_combo_finisher_right3;
	
	Animation m_grab_air_spin_combo_finisher_left1;
	Animation m_grab_air_spin_combo_finisher_left2;
	Animation m_grab_air_spin_combo_finisher_left3;

	size_t m_grab_air_spin_finisher2_duration = 20;

	Animation m_weapon_pipe_idle_right;
	Animation m_weapon_pipe_walk_right;
	Animation m_weapon_pipe_attack_right;
	Animation m_weapon_pipe_throw_right;

	Animation m_weapon_pipe_idle_left;
	Animation m_weapon_pipe_walk_left;
	Animation m_weapon_pipe_attack_left;
	Animation m_weapon_pipe_throw_left;

	Animation m_weapon_knife_idle_right;
	Animation m_weapon_knife_walk_right;
	Animation m_weapon_knife_attack_right;
	Animation m_weapon_knife_throw_right;

	Animation m_weapon_knife_idle_left;
	Animation m_weapon_knife_walk_left;
	Animation m_weapon_knife_attack_left;
	Animation m_weapon_knife_throw_left;

	Animation m_damage_received_right;
	Animation m_damage_received_left;

	Animation m_down_right;
	Animation m_down_left;

	Animation m_up_right;
	Animation m_up_left;

	Animation *m_current_animation;

	void AdvanceAnimation(size_t initial_sprite_duration,  Animation *next_anim_sprite, bool restart_animation);
	
private:
	std::list<int*> m_animation_list;

};

#endif // !__PLAYER_H__

