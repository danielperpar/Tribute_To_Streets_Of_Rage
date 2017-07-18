#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include <list>
#include "Point.h"
#include "Entity.h"


class Garcia;
struct SDL_Texture;
class Player;
class ModuleEnemies : public Module
{
public:
	ModuleEnemies(bool active = true);
	~ModuleEnemies();
	bool Start();
	bool CleanUp();
	update_status Update();

	//------------------------------------ENEMIES SPAWN TRIGGERS ----------------------------------------
	bool first_trigger_reached = false;
	
private:
	SDL_Texture *tx_garcia = nullptr;
	Garcia *garcia_prototype = nullptr;
	Entity* GenerateEnemy(entity_type type, iPoint position, Player *player, std::list<Entity*> &dynamic_entities);
};

#endif