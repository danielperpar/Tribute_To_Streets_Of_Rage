#ifndef __GARCIA_H__
#define __GARCIA_H__

#include "Animation.h"
#include "Enemy.h"
#include <list>
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"
#include "Point.h"

class Animation;
class GarciaFSM;
class Player;
struct Collider;
struct CollisionInfo;
class Garcia : public Enemy
{

private:
	std::list<int*> animation_list;
	void LoadGarciaAnimations();
	void LoadDamage();
	void LoadConfig();

public:
	Garcia(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	Garcia(const Garcia &garcia);
	virtual ~Garcia();
	virtual void UpdateFSM();
	virtual void OnCollision(const CollisionInfo &col_info_garcia, const CollisionInfo &col_info_other);
	void OnCollisionEnter(const CollisionInfo &col_info_garcia, const CollisionInfo &col_info_other);
	virtual void OnCollisionExit(const CollisionInfo &col_info_other);
	void SetPlayer(Player *player);
	virtual void ApplyDamage(int damage);

	//frames to allow attack animation to finish before transition
	int num_frames = 0;// 60;
	int frames_counter = 0;
	bool punch_finished = false;

	GarciaFSM *garcia_fsm = nullptr;
	Player *the_player = nullptr;
	int punch_hits = 0;
	int punch_damage = 0;

	int evasive_v_offset = 20;
	int evasive_h_offset = 120;
	bool evasive_started_facing_right = false;

	iPoint pos_before_knockdown;
	int down_count = 0;
	int down_frames = 20;
	int down_inflection = 10;
	bool up = false;

	iPoint start_pos = { 0,0 };
	bool offset_applied = false;
	bool offset_applied_2 = false;

	//---------------------------------- OFFSETS IN SOMERSAULT ATTACK ------------------
	//right
	iPoint offset_right_2 = { 10,0 };
	iPoint offset_right_3 = { 15,0 };
	iPoint offset_right_4 = { 25,15 };
	iPoint offset_right_5 = { 20,20 };
	iPoint offset_right_6 = { 20,40 };
	iPoint offset_right_7 = { 50,0 };
	
	//left
	iPoint offset_left_3 = { 15,0 };
	iPoint offset_left_4 = { 40,15 };
	iPoint offset_left_5 = { 65,20 };
	iPoint offset_left_6 = { 20,40 };
	iPoint offset_left_7 = { 50,0 };

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
	
	//---------------------------------------- GARCIA ANIMATIONS ---------------------------------------------
	Animation garcia_idle_right;
	Animation garcia_idle_left;

	Animation garcia_walk_right;
	Animation garcia_walk_left;

	Animation garcia_punch_right1;
	Animation garcia_punch_right2;

	Animation garcia_punch_left1;
	Animation garcia_punch_left2;

	Animation garcia_damaged_right;
	Animation garcia_damaged_left;

	Animation garcia_down_right1;
	Animation garcia_down_left1;

	Animation garcia_down_right2;
	Animation garcia_down_left2;

	Animation garcia_up_right;
	Animation garcia_up_left;

	Animation garcia_grabbed_right;
	Animation garcia_grabbed_left;

	Animation garcia_grabbed_finisher_right;
	Animation garcia_grabbed_finisher_left;

	Animation garcia_grabbed_finisher_horiz_right;
	Animation garcia_grabbed_finisher_horiz_left;

	Animation garcia_grabbed_finisher_vert_right;
	Animation garcia_grabbed_finisher_vert_left;

	Animation garcia_dead_blink_effect;
};


#endif
