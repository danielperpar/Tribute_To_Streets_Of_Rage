#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include <list>
#include "Entity.h"
#include "Point.h"
#include "GameTimer.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;
class PlayerFSM;
class Player : public Entity{

private:
	std::list<int*> animation_list;
	PlayerFSM *player_fsm = nullptr;
	void LoadPlayerAnimations();
	void LoadStats();
	void LoadColliders();
	
	
public:
	Player(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	virtual ~Player();	
	virtual void UpdateFSM();
	void OnCollision(const CollisionInfo &col_info_player, const CollisionInfo &col_info_other);
	void OnCollisionEnter(const CollisionInfo &col_info_player, const CollisionInfo &col_info_other);
	void OnCollisionExit(const CollisionInfo &col_info_other);

	int speed = 0;
	int life = 0;
	//----------------------------------------  PLAYER COLLIDERS -----------------------------------------------
	Collider *body_collider = nullptr;
	Collider *hit_collider = nullptr;
	SDL_Rect body_rect;
	SDL_Rect hit_rect;

	//int ref_x = 70;
	int body_collider_offset_right = 0;
	int hit_collider_offset_right = 0;
	int body_collider_offset_left = 0;
	int hit_collider_offset_left = 0;

	// ---------------------------------------- COLLISION ----------------------------------------
	bool right_blocked = false;
	bool left_blocked = false;
	bool up_blocked = false;
	bool down_blocked = false;

	int left_block_count = 0;
	int right_block_count = 0;
	int up_block_count = 0;
	int down_block_count = 0;

	//colliders colliding with player's body
	std::list<CollisionInfo> body_collision_status;
	

	// ----------------------------------  VARIABLES THAT CONTROL PLAYER FSM LOGIC -----------------------------------
	bool facing_right = true;
	bool idle = true;
	bool walk_left = false;
	bool walk_right = false;
	bool walk_up = false;
	bool walk_down = false;
	bool jump = false;
	bool landed = true;
	bool hit_hold = false;
	bool hit_down = false;
	bool attack_finished = false;
	bool damaged = false;
	bool knocked_down = false;
	//----------------------------------------------------------------------------------------------------------
	

	//jump
	bool jump_up = true;
	iPoint jump_start_pos = { 0 , 0 };
	int jump_speed = 2;
	int max_jump_height = 20;
	int jump_count = 0;

	//combo
	int combo_max_time = 120;
	bool in_combo_time = true;
	int punch_combo_hits = 0;
	bool enemy_at_range = true;
	 
	//knocked down
	int down_vel = 1;
	int down_count = 0;
	int down_frames = 20;
	int down_inflection = 10;
	bool up = false;
	iPoint pos_before_knockdown = { 0,0 };
	
	size_t m_kick_hits = 0;
	bool m_continue_combo_grab = false;

	bool m_carrying_weapon_pipe = false;
	bool m_carrying_weapon_knife = false;

	bool m_restart_animation = true;

	bool m_float_attack = false;

	bool m_looking_each_other = false;

	bool m_dead = false;
	
	//---------------------------------------- PLAYER ANIMATIONS ---------------------------------------------
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

	Animation anim_ground_right1;
	Animation anim_ground_right2;
	Animation anim_ground_left1;
	Animation anim_ground_left2;

	Animation anim_up_right;
	Animation anim_up_left;

};

#endif // !__PLAYER_H__

