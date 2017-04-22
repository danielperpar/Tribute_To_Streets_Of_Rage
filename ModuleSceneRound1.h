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
	update_status Update();
	bool CleanUp();

	void LoadSceneAssets();

	GUI *gui = nullptr;
	Entity *foreground = nullptr;


	//------------------------------------ENEMIES SPAWN TRIGGERS ----------------------------------------
	bool first_trigger_reached = false;
	Player *the_player = nullptr;
	

private:
	std::list<int*> animation_list;
	std::vector<Entity*> scenario_entities;
	std::vector<Entity*> dynamic_entities;
	
	SDL_Texture *tx_background = nullptr;
	SDL_Texture *tx_foreground = nullptr;
	SDL_Texture *tx_neons = nullptr;
	SDL_Texture *tx_gui = nullptr;
	SDL_Texture *tx_player = nullptr;
	SDL_Texture *tx_garcia = nullptr;
	
	Animation neonPinEPot;
	Animation neonBreakfastDiner;
	Animation neonLDevo;
	Animation neonRachShop;
	Animation neonAbcShop;
	Animation neonCafeRestaurant;
	
	
	Entity* GenerateEnemy(entity_type type, iPoint position, Player *player, std::vector<Entity*> &dynamic_entities);
	
	//----------------------------------- ENEMIES PROTOTYPES---------------------------------------------------
	Garcia *garcia_prototype = nullptr;




};

#endif // __MODULESCENEROUND1_H__