#ifndef __MODULESCENEROUND1_H__
#define __MODULESCENEROUND1_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneRound1 : public Module
{
public:
	ModuleSceneRound1(bool active = true);
	~ModuleSceneRound1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	SDL_Texture* foreground = nullptr;
	SDL_Texture* shop_neons = nullptr;
	SDL_Texture* gui = nullptr;
	
	Animation neonPinEPot;
	Animation neonBreakfastDiner;
	Animation neonLDevo;
	Animation neonRachShop;
	Animation neonAbcShop;
	Animation neonCafeRestaurant;
	std::list<int*> animation_list;


};

#endif // __MODULESCENEROUND1_H__