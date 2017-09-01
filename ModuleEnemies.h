#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include <list>
#include "Point.h"
#include "Entity.h"
#include "ModuleWindow.h"

class Garcia;
class Antonio;
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

private:
	SDL_Texture *tx_enemies = nullptr;
	Garcia *garcia_prototype = nullptr;
	Antonio *antonio_prototype = nullptr;
	void GenerateEnemy(entity_type type, iPoint position, Player *player, std::list<Entity*> &dynamic_entities);
	void SpawnEnemies(int spawn_point, int amount, entity_type type);

	iPoint **spawn_points;
	int max_spawn_points = 21;
	int *amount_at_points;
	int starting_trigger = 800;
	int *reached_triggers;
	bool spawn_boss = true;
	
	int offset_spawn_right = 250;
	int offset_spawn_left = 150;
};

#endif