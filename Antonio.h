#ifndef __ANTONIO_H__
#define __ANTONIO_H__

#include "Enemy.h"
#include "Entity.h"
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
	void LoadStats();
	void LoadAntonioAnimations();

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
	int life = 400;
	iPoint speed_vect = { 1,1 };
	int speed = 0;
	Player *the_player = nullptr;
	// ----------------------------- SPRITE HEIGHT REFERENCE ----------------------
	int ref_y = 50;
	// ----------------------------- COLLIDER Y OFFSET ---------------------------
	int body_collider_offset_y = 47;
	int hit_collider_offset_y = 70;
	/*bool m_carrying_boomerang = false;
	bool m_ai_throw_boomerang = false;

	Particle *m_boomerang = nullptr;
	*/
	
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
	// -------------- Offsets in somersault animation -> TODO:poner valores en el json
	iPoint start_pos = { 0,0 };
	bool offset_applied = false;
	bool offset_applied_2 = false;
	int depth_margin = 3;
	int body_collider_wide = 36;
	int body_collider_original = 18;
	int body_collider_adjusted_x = 10;
	bool body_coll_adjustment_made = false;

	//right
	int offset_right_x1 = 10;
	int offset_right_y1 = 5;
	int offset_right_x2 = 25;
	int offset_right_y2 = 5;
	int offset_right_x3 = 20;
	int offset_right_x4 = 20;
	int offset_right_y4 = 10;
	int offset_right_x5 = 30;
	int offset_right_x6 = 20;
	int offset_right_y6 = 15;
	int offset_right_x7 = 90;
	int offset_right_y7 = 0;

	//left
	int offset_left_x1 = 10;
	int offset_left_y1 = 5;
	int offset_left_x2 = 25;
	int offset_left_y2 = 5;
	int offset_left_x3 = 15;
	int offset_left_x4 = 77;
	int offset_left_y4 = 20;
	int offset_left_x5 = 15;
	int offset_left_y5 = 3;
	int offset_left_x6 = 50;
	int offset_left_y6 = 40;

	//-------------------------------- BOOMERANG ATTACK CASTING SPOTS
	int offset_cast_y = 50;
	int offset_cast_x_left = 25;
	int offset_cast_x_right = 110;
	iPoint cast_left = { 0,0 };
	iPoint cast_right = { 0,0 };
	iPoint spawn_position = { 0, 0 };

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
};



#endif