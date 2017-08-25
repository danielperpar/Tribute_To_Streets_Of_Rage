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
	
	void LoadPlayerAnimations();
	void LoadStats();
	void LoadColliders();
	void LoadOtherParameters();
	
public:
	Player(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	virtual ~Player();	
	PlayerFSM *player_fsm = nullptr;
	virtual void UpdateFSM();
	void OnCollision(const CollisionInfo &col_info_player, const CollisionInfo &col_info_other);
	void OnCollisionEnter(const CollisionInfo &col_info_player, const CollisionInfo &col_info_other);
	void OnCollisionExit(const std::pair<CollisionInfo, CollisionInfo> &col_info_pair);
	
	int speed = 0;
	int life = 0;	
	bool god_mode = false;
	//distance in x-axis from the upper left corner of the sprite 
	//to the player's head upper point used as a point of reference or origin of coordinates
	int ref_x = 70;

	//start - respawn position
	iPoint respawn_position;

	//jump
	bool jump_up = true;
	iPoint jump_start_pos = { 0 , 0 };
	int jump_speed = 2;
	int max_jump_height = 20;
	int jump_count = 0;

	//combo
	int combo_max_frames = 60;
	int punch_combo_hits = 0;
	bool enemy_at_range = true;
	bool start_combo_timer = false;
	int combo_timer_count = 0;

	//grab hit
	bool allow_grab = true;
	int grab_hit_counter = 0;
	int max_grab_kick = 2;

	//knocked down
	int down_vel = 1;
	int down_count = 0;
	int down_frames = 20;
	int down_inflection = 10;
	bool up = false;
	iPoint pos_before_knockdown = { 0,0 };

	//------------------------------- ATTACKS DAMAGES----------------
	int simple_damage = 35;
	int air_finisher_damage = 100;

	//------------------------------- DEAD ANIMATION COUNTER--------------
	int dead_max_times = 3;
	int dead_times = 0;

	//----------------------------------------  PLAYER COLLIDERS -----------------------------------------------
	Collider *body_collider = nullptr;
	Collider *hit_collider = nullptr;
	SDL_Rect body_rect;
	SDL_Rect hit_rect;

	int body_collider_offset_right = 0;
	int hit_collider_offset_right = 0;
	int body_collider_offset_left = 0;
	int hit_collider_offset_left = 0;
	
	// ---------------------------------------- COLLISION ----------------------------------------
	bool right_blocked = false;
	bool left_blocked = false;
	bool up_blocked = false;
	bool down_blocked = false;

	bool enemy_to_grab = false;
	int release_grab_offset = 0;

	//------ position offsets in air somersault -------- TODO: Poner valores en el json
	//right
	int offset_right_x_1 = 6;
	int offset_right_y_1 = 5;

	int offset_right_x_2 = 0;
	int offset_right_y_2 = 40;

	int offset_right_x_3 = 4;
	int offset_right_y_3 = 65;
	
	int offset_right_x_4 = 4;
	int offset_right_y_4 = 65;

	int offset_right_x_5 = 0;
	int offset_right_y_5 = 40;

	int offset_right_x_6 = 0;
	int offset_right_y_6 = 6;

	int offset_right_x_7 = 40;
	int offset_right_y_7 = 0;

	//left
	int offset_left_x_1 = 6;
	int offset_left_y_1 = 5;

	int offset_left_x_2 = 0;
	int offset_left_y_2 = 40;

	int offset_left_x_3 = 2;
	int offset_left_y_3 = 65;

	int offset_left_x_4 = 2;
	int offset_left_y_4 = 65;

	int offset_left_x_5 = 0;
	int offset_left_y_5 = 40;

	int offset_left_x_6 = 3;
	int offset_left_y_6 = 6;

	int offset_left_x_7 = 40;
	int offset_left_y_7 = 0;

	//Enemy to react to
	Entity *enemy_attacker = nullptr;

	//Attacked, Grabbed enemy
	Entity *punched_enemy = nullptr;
	Entity *grabbed_enemy = nullptr;
	
	//colliders colliding with player's body or hit area
	std::list<std::pair<CollisionInfo, CollisionInfo>> player_collision_status;

	// ----------------------------------  VARIABLES THAT CONTROL PLAYER FSM LOGIC -----------------------------------
	bool start = false;
	bool facing_right = true;
	bool idle = true;
	bool walk_left = false;
	bool walk_right = false;
	bool walk_up = false;
	bool walk_down = false;
	bool jump = false;
	bool jump_finished = false;
	bool hit_hold = false;
	bool hit_down = false;
	bool attack_finished = false;
	bool damaged = false;
	bool knocked_down = false;
	bool somersault_finished = false;
	bool finisher_finished = false;
	//----------------------------------------------------------------------------------------------------------
	
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
	Animation anim_grab_air_spin_combo_finisher_right4;
	Animation anim_grab_air_spin_combo_finisher_right5;
	Animation anim_grab_air_spin_combo_finisher_right6;

	Animation anim_grab_air_spin_combo_finisher_left1;
	Animation anim_grab_air_spin_combo_finisher_left2;
	Animation anim_grab_air_spin_combo_finisher_left3;
	Animation anim_grab_air_spin_combo_finisher_left4;
	Animation anim_grab_air_spin_combo_finisher_left5;
	Animation anim_grab_air_spin_combo_finisher_left6;

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

	Animation anim_deadBlink_right;
	Animation anim_deadBlink_left;

};

#endif // !__PLAYER_H__

