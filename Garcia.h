#ifndef __GARCIA_H__
#define __GARCIA_H__

#include "Animation.h"
#include "Entity.h"
#include <list>
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"

class Animation;
class GarciaFSM;
class Player;
struct Collider;
struct CollisionInfo;
class Garcia : public Entity
{

private:
	std::list<int*> animation_list;
	void LoadStats();
	void LoadColliders();
	void LoadGarciaAnimations();

public:
	Garcia(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	Garcia(const Garcia &garcia);
	virtual ~Garcia();
	virtual void UpdateFSM();
	void OnCollision(const CollisionInfo &col_info_garcia, const CollisionInfo &col_info_other);
	void OnCollisionEnter(const CollisionInfo &col_info_garcia, const CollisionInfo &col_info_other);
	void OnCollisionExit(const CollisionInfo &col_info_other);
	void SetPlayer(Player *player);

	GarciaFSM *garcia_fsm = nullptr;
	int life = 100;
	iPoint speed_vect = { 1,1 };
	int speed = 0;
	Player *the_player = nullptr;
	size_t punch_hits = 0;

	int evasive_v_offset = 20;
	int evasive_h_offset = 120;
	bool evasive_started_facing_right = false;

	iPoint pos_before_knockdown;
	int down_count = 0;
	int down_frames = 20;
	int down_inflection = 10;
	bool up = false;

	//----------------------------------------  GARCIA COLLIDERS -----------------------------------------------
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
	bool right_collision = false;
	bool left_collision = false;
	bool up_collision = false;
	bool down_collision = false;

	bool left_blocked = false;
	bool right_blocked = false;
	bool up_blocked = false;
	bool down_blocked = false;

	CollisionInfo hit_collider_status = CollisionInfo(nullptr, contact_direction::LEFT, contact_direction::DOWN);

	// ----------------------------------  VARIABLES THAT CONTROL GARCIA FSM LOGIC -----------------------------------
	bool facing_right = false;
	bool idle = true;
	bool walk_left = false;
	bool walk_right = false;
	bool walk_up = false;
	bool walk_down = false;
	bool attack = false;
	bool evasive = false;
	bool damaged = false;
	bool knocked_down = false;
	bool grabbed = false;
	bool player_in_sight = true; // test

	//----------------------------------------------------------------------------------------------------------


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

};


#endif
