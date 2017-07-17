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
	virtual ~Antonio();

	virtual void UpdateFSM();
	virtual void OnCollision(const CollisionInfo &col_info_antonio, const CollisionInfo &col_info_other);
	void OnCollisionEnter(const CollisionInfo &col_info_antonio, const CollisionInfo &col_info_other);
	virtual void OnCollisionExit(const CollisionInfo &col_info_other);
	void SetPlayer(Player *player);
	void ApplyDamage(int damage);

	AntonioFSM *antonio_fsm = nullptr;
	int life = 100;
	bool destroy_this = false;
	iPoint speed_vect = { 1,1 };
	int speed = 0;
	Player *the_player = nullptr;


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

	// ----------------------------------  VARIABLES THAT CONTROL ANTONIO FSM LOGIC -----------------------------------
	bool facing_right = false;
	bool idle = true;
	bool walk_left = false;
	bool walk_right = false;
	bool walk_up = false;
	bool walk_down = false;
	bool kick = false;
	bool damaged = false;
	bool knocked_down = false;
	bool grabbed = false;
	bool player_in_sight = true; // test

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

	Animation antonio_dead_blink_effect;
};



#endif