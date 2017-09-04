#ifndef __ANTONIO_H__
#define __ANTONIO_H__

#include "Enemy.h"
#include "Entity.h"
#include <list>
#include "ModuleCollision.h"

class Animation;
class AntonioFSM;
class Player;
struct Collider;
struct CollisionInfo;
class Antonio : public Enemy
{

private:

	std::list<int*> animation_list;
	void LoadAntonioAnimations();
	void LoadOffsets();
	void LoadDamage();
	void LoadConfig();

public:

	Antonio(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	Antonio(const Antonio &antonio);
	virtual ~Antonio();

	virtual void UpdateFSM();
	virtual void OnCollision(const CollisionInfo &col_info_antonio, const CollisionInfo &col_info_other);
	void OnCollisionEnter(const CollisionInfo &col_info_antonio, const CollisionInfo &col_info_other);
	virtual void OnCollisionExit(const CollisionInfo &col_info_other);
	void SetPlayer(Player *player);
	void ApplyDamage(int damage);

	AntonioFSM *antonio_fsm = nullptr;
	Player *the_player = nullptr;
	bool entered_knocked_down = false;
	bool carrying_boomerang = true;
	int kick_damage = 0;

	// ----------------------------- SPRITE HEIGHT REFERENCE ----------------------
	int ref_y = 51;

	// ----------------------------- COLLIDER Y OFFSET ---------------------------
	int body_collider_offset_y = 47;
	int hit_collider_offset_y = 70;
	
	//------------------- KNOCKDOWN MOVEMENT -------------------------
	bool bouncing_down = false;
	int bouncing_frames = 20;
	int bouncing_inflection = 10;
	int bouncing_frames_count = 0;

	//------------------------- DEAD BLINK EFFECT ---------------------------
	bool blink = true;
	int blink_counter = 0;
	int blink_wait_frames = 10;
	int blink_times_counter = 0;
	int blink_max_times = 5;

	iPoint pos_before_knockdown;
	int down_count = 0;
	int down_frames = 20;
	int down_inflection = 10;
	bool up = false;

	// -------------- OFFSETS IN SOMERSAULT------------------------ 
	iPoint start_pos = { 0,0 };
	bool offset_applied = false;
	bool offset_applied_2 = false;
	int body_collider_wide = 36;
	int body_collider_original = 18;
	int body_collider_adjusted_x = 10;
	bool body_coll_adjustment_made = false;

	//right
	iPoint offset_right_1 = { 10,5 };
	iPoint offset_right_2 = { 25,5 };
	iPoint offset_right_3 = { 20,0 };
	iPoint offset_right_4 = { 20,10 };
	iPoint offset_right_5 = { 30,0 };
	iPoint offset_right_6 = { 20,15 };
	iPoint offset_right_7 = { 90,0 };

	//left
	iPoint offset_left_1 = { 10,5 };
	iPoint offset_left_2 = { 25,5 };
	iPoint offset_left_3 = { 15,0 };
	iPoint offset_left_4 = { 77,20 };
	iPoint offset_left_5 = { 15,3 };
	iPoint offset_left_6 = { 50,40 };

	//-------------------------------- BOOMERANG ATTACK CASTING SPOTS
	int offset_cast_y = 50;
	int offset_cast_x_left = 20;
	int offset_cast_x_right = 115;
	iPoint cast_left = { 0,0 };
	iPoint cast_right = { 0,0 };
	iPoint spawn_position = { 0, 0 };

	int boomerang_offset_left_x = 10;
	int boomerang_offset_left_y = 40;
	int boomerang_offset_right_x = 100;
	int boomerang_offset_right_y = 40;
	
	//Chase time out frames
	int chase_time_out = 180;
	int chase_counter = 0;

	//frames to allow attack animation to finish before transition
	int num_frames = 30;
	int frames_counter = 0;

	//prekick frames to allow player to attack the boss
	int prekick_frames = 30;
	int prekick_counter = 0;

	//----------------------- AUDIO-----
	bool kick_played = false;

	//-------------------------------------- ANIMATIONS --------------------------
	Animation antonio_boomerang_idle_right;
	Animation antonio_boomerang_idle_left;

	Animation antonio_idle_right;
	Animation antonio_idle_left;

	Animation antonio_boomerang_walk_right;
	Animation antonio_boomerang_walk_left;

	Animation antonio_walk_right;
	Animation antonio_walk_left;

	Animation antonio_kick_right;
	Animation antonio_kick_left;

	Animation antonio_throw_boomerang_right;
	Animation antonio_throw_boomerang_left;

	Animation antonio_recover_boomerang_right;
	Animation antonio_recover_boomerang_left;

	Animation antonio_grabbed_right;
	Animation antonio_grabbed_left;

	Animation antonio_grabbed_finisher_right;
	Animation antonio_grabbed_finisher_left;

	Animation antonio_grabbed_finisher_horiz_right;
	Animation antonio_grabbed_finisher_horiz_left;

	Animation antonio_grabbed_finisher_vert_right;
	Animation antonio_grabbed_finisher_vert_left;

	Animation antonio_down_right1;
	Animation antonio_down_right2;

	Animation antonio_down_left1;
	Animation antonio_down_left2;

	Animation antonio_up_right;
	Animation antonio_up_left;

	Animation antonio_dead_blink_effect;

	Animation antonio_damaged_right;
	Animation antonio_damaged_left;
};



#endif