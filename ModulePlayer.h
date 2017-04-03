#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleCollision.h"
#include "Player.h"
#include "Enemy.h"

struct SDL_Texture;
class PlayerFSM;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	// ----------------------------------  VARIABLES THAT CONTROL FSM LOGIC -----------------------------------
	bool facing_right = true;
	bool idle = true;
	bool walk_left = false;
	bool walk_right = false;
	bool walk_up = false;
	bool walk_down = false;

	//----------------------------------------------------------------------------------------------------------

	void UpdateColliderPosition();
	bool LookingEachOther(Enemy *enemy);

	SDL_Texture *graphics = nullptr;
	Player *player = nullptr;
	Collider *m_player_collider = nullptr;
	
	
private:	
	Uint32 time = 0;
	Uint32 update_time = 0;
	Uint32 dt = 10;
	bool do_logic = true;
	PlayerFSM *player_fsm = nullptr;


};

#endif