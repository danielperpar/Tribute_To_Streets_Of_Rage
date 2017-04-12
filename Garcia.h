#ifndef __GARCIA_H__
#define __GARCIA_H__

#include "Animation.h"
#include "Entity.h"
#include <list>

class Animation;
class GarciaFSM;
class Player;
class Garcia : public Entity
{

private:
	std::list<int*> animation_list;
	

public:
	Garcia(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	Garcia(const Garcia &garcia);
	virtual ~Garcia();
	virtual void UpdateFSM();

	GarciaFSM *garcia_fsm = nullptr;
	float move_inc = 0.0f;
	int life = 100;
	Player *the_player = nullptr;
	size_t m_punch_hits = 0;
	void SetPlayer(Player *player);
	
	
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
