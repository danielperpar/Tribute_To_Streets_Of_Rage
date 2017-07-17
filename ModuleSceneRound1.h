#ifndef __MODULESCENEROUND1_H__
#define __MODULESCENEROUND1_H__

#include "Module.h"
#include <vector>
#include <list>

struct SDL_Texture;
class ScenarioElement;
class Entity;
class GUI;
class Player;
class Garcia;
class ModuleSceneRound1 : public Module
{
public:
	ModuleSceneRound1(bool active = true);
	virtual ~ModuleSceneRound1();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	void LoadSceneAssets();

	GUI *gui = nullptr;
	Entity *foreground = nullptr;

	//-------------------- SCENE BOUNDARIES -------------------
	int upper_limit = 90;
	int lower_limit = 150;

	//------------------------------------ENEMIES SPAWN TRIGGERS ----------------------------------------
	bool first_trigger_reached = false;

	std::list<Entity*> dynamic_entities;
	bool entity_erased = false;

private:
	std::list<int*> animation_list;
	std::vector<Entity*> scenario_entities;
	
	SDL_Texture *tx_background = nullptr;
	SDL_Texture *tx_foreground = nullptr;
	SDL_Texture *tx_neons = nullptr;
	SDL_Texture *tx_gui = nullptr;
	SDL_Texture *tx_garcia = nullptr;
	
	Animation neonPinEPot;
	Animation neonBreakfastDiner;
	Animation neonLDevo;
	Animation neonRachShop;
	Animation neonAbcShop;
	Animation neonCafeRestaurant;
	
	
	Entity* GenerateEnemy(entity_type type, iPoint position, Player *player, std::list<Entity*> &dynamic_entities);
	
	//----------------------------------- ENEMIES PROTOTYPES---------------------------------------------------
	Garcia *garcia_prototype = nullptr;




};

#endif // __MODULESCENEROUND1_H__