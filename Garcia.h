#ifndef __GARCIA_H__
#define __GARCIA_H__

#include "Animation.h"
#include "Entity.h"
#include <list>
#include "SDL/include/SDL.h"

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
	void OnCollisionEnter(const CollisionInfo &col_info_garcia, const CollisionInfo &col_info_other);
	void OnCollisionExit(const CollisionInfo &col_info_garcia, const CollisionInfo &col_info_other);

	GarciaFSM *garcia_fsm = nullptr;
	int life = 100;
	iPoint speed_vect = { 1,1 };
	int speed = 0;
	Player *the_player = nullptr;
	size_t m_punch_hits = 0;

	void SetPlayer(Player *player);
	
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
	bool colliding = false;
	bool right_collision = false;
	bool left_collision = false;
	bool up_collision = false;
	bool down_collision = false;

	int left_block_count = 0;
	int right_block_count = 0;
	int up_block_count = 0;
	int down_block_count = 0;

	std::vector<std::pair<Collider*, contact_direction>> collision_vector;

	// ----------------------------------  VARIABLES THAT CONTROL GARCIA FSM LOGIC -----------------------------------
	bool facing_right = false;
	bool idle = true;
	bool walk_left = false;
	bool walk_right = false;
	bool walk_up = false;
	bool walk_down = false;
	bool attack = false;
	bool attack_finished = false;
	bool damaged = false;
	bool knocked_down = false;
	bool player_in_sight = true; //test
	bool player_at_range = false;
	bool look_each_other = false;

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
	Animation garcia_damage_left;

	Animation garcia_down_right;
	Animation garcia_down_left;

	Animation garcia_up_right;
	Animation garcia_up_left;



};


#endif
