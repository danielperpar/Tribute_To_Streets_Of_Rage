#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Globals.h"

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