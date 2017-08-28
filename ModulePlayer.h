#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Globals.h"

//Player movement limits
#define MIN_Y_POSITION 90
#define MAX_Y_POSITION 150
#define MIN_X_POSITION 700
#define MAX_X_POSITION 3870

class Player;
struct SDL_Texture;
class ModulePlayer : public Module
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();
	bool Start();
	update_status Update();

	Player *the_player = nullptr;

private:
	SDL_Texture *tx_player = nullptr;
};

#endif