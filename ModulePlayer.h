#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleCollision.h"
#include "Player.h"
#include "Enemy.h"

struct SDL_Texture;


class ModulePlayer : public Module
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* collider1, Collider* collider2);

	SDL_Texture *graphics;
	Player *player = nullptr;
	Collider* playerCollider;
	Enemy *enemy = nullptr;
	
	
private:	
	Uint32 time = 0;
	Uint32 update_time = 0;
	Uint32 dt = 10;
	bool do_logic = true;
};

#endif