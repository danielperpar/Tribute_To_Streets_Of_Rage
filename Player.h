#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include <list>
#include "Entity.h"
#include "Point.h"

struct SDL_Texture;
class PlayerFSM;
class Player : public Entity{

private:
	std::list<int*> animation_list;
	
public:
	Player(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	virtual ~Player();
	void LoadPlayerAnimations();

	int speed = 1;
	int life = 100;
	PlayerFSM *player_fsm = nullptr;

	// ----------------------------------  VARIABLES THAT CONTROL PLAYER FSM LOGIC -----------------------------------
	bool facing_right = true;
	bool idle = true;
	bool walk_left = false;
	bool walk_right = false;
	bool walk_up = false;
	bool walk_down = false;

	//----------------------------------------------------------------------------------------------------------



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
	

	size_t m_down_accel = 2;
	size_t m_down_vel = 1;
	size_t m_down_count = 0;
	size_t m_down_frames = 30;
	size_t m_down_update_count = 0;
	size_t m_down_update_time = 6;

	//Axis X origin taken from the upper left vertex related to the rectangle containing the player sprite to the player's back neck position
	size_t m_x_ref = 70;

	Animation anim_idle_right1;
	Animation anim_idle_right2;
	Animation anim_idle_right3;

	Animation anim_idle_left1;
	Animation anim_idle_left2;
	Animation anim_idle_left3;

	Animation anim_walk_right;
	Animation anim_walk_left;

	Animation anim_jump_right1;
	Animation anim_jump_right2;
	Animation anim_jump_left1;
	Animation anim_jump_left2;

	Animation anim_air_kick_right;
	Animation anim_air_kick_left;

	Animation anim_punch_combo_right1;
	Animation anim_punch_combo_right2;
	Animation anim_punch_combo_right3;
	Animation anim_punch_combo_left1;
	Animation anim_punch_combo_left2;
	Animation anim_punch_combo_left3;

	size_t punch_combo_timeout = 15;

	Animation anim_back_punch_right1;
	Animation anim_back_punch_right2;

	Animation anim_back_punch_left1;
	Animation anim_back_punch_left2;


	Animation anim_grab_right;
	Animation anim_grab_kick_head_combo_right1;
	Animation anim_grab_kick_head_combo_right2;


	Animation anim_grab_left;
	Animation anim_grab_kick_head_combo_left1;
	Animation anim_grab_kick_head_combo_left2;

	Animation anim_grab_air_spin_combo_right1;
	Animation anim_grab_air_spin_combo_right2;
	Animation anim_grab_air_spin_combo_right3;
	Animation anim_grab_air_spin_combo_right4;
	Animation anim_grab_air_spin_combo_right5;
	Animation anim_grab_air_spin_combo_right6;
	Animation anim_grab_air_spin_combo_right7;

	Animation anim_grab_air_spin_combo_left1;
	Animation anim_grab_air_spin_combo_left2;
	Animation anim_grab_air_spin_combo_left3;
	Animation anim_grab_air_spin_combo_left4;
	Animation anim_grab_air_spin_combo_left5;
	Animation anim_grab_air_spin_combo_left6;
	Animation anim_grab_air_spin_combo_left7;

	Animation anim_grab_air_spin_combo_finisher_right1;
	Animation anim_grab_air_spin_combo_finisher_right2;
	Animation anim_grab_air_spin_combo_finisher_right3;

	Animation anim_grab_air_spin_combo_finisher_left1;
	Animation anim_grab_air_spin_combo_finisher_left2;
	Animation anim_grab_air_spin_combo_finisher_left3;

	Animation anim_weapon_pipe_idle_right;
	Animation anim_weapon_pipe_walk_right;
	Animation anim_weapon_pipe_attack_right;
	Animation anim_weapon_pipe_throw_right;

	Animation anim_weapon_pipe_idle_left;
	Animation anim_weapon_pipe_walk_left;
	Animation anim_weapon_pipe_attack_left;
	Animation anim_weapon_pipe_throw_left;

	Animation anim_weapon_knife_idle_right;
	Animation anim_weapon_knife_walk_right;
	Animation anim_weapon_knife_attack_right;
	Animation anim_weapon_knife_throw_right;

	Animation anim_weapon_knife_idle_left;
	Animation anim_weapon_knife_walk_left;
	Animation anim_weapon_knife_attack_left;
	Animation anim_weapon_knife_throw_left;

	Animation anim_damage_received_right;
	Animation anim_damage_received_left;

	Animation anim_down_right;
	Animation anim_down_left;

	Animation anim_up_right;
	Animation anim_up_left;

};

#endif // !__PLAYER_H__

