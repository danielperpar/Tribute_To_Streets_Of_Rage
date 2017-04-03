#ifndef __MODULESCENEROUND1_H__
#define __MODULESCENEROUND1_H__

#include "Module.h"
#include <vector>
#include <list>

struct SDL_Texture;
class ScenarioElement;
class Entity;
class GUI;
class ModuleSceneRound1 : public Module
{
private:
	std::list<int*> animation_list;
	std::vector<Entity*> scenario_entities;
	std::vector<Entity*> dynamic_entities;
	
	SDL_Texture* tx_background = nullptr;
	SDL_Texture* tx_foreground = nullptr;
	SDL_Texture* tx_neons = nullptr;
	SDL_Texture* tx_gui = nullptr;

	Animation neonPinEPot;
	Animation neonBreakfastDiner;
	Animation neonLDevo;
	Animation neonRachShop;
	Animation neonAbcShop;
	Animation neonCafeRestaurant;

public:
	ModuleSceneRound1(bool active = true);
	virtual ~ModuleSceneRound1();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

	void LoadSceneAssets();
	
	// ----------------------------------  VARIABLES THAT CONTROL PLAYER FSM LOGIC -----------------------------------
	bool facing_right = true;
	bool idle = true;
	bool walk_left = false;
	bool walk_right = false;
	bool walk_up = false;
	bool walk_down = false;

	
	//-----------------------------  FOREGROUND ENTITIES TO BE RENDERED ----------------------------------------------------
	GUI *gui = nullptr;
	ScenarioElement *foreground = nullptr;
};

#endif // __MODULESCENEROUND1_H__