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
	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

	Player *the_player = nullptr;

private:
	SDL_Texture *tx_player = nullptr;
	int start_offset_x = 60;
	int start_offset_y = 5;
	void LoadConfig();
};

#endif