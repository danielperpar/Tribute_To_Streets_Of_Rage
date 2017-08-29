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
	int max_spawn_points = 7;
	int *amount_at_points;
	int starting_trigger = 800;
	int *reached_triggers;
	bool spawn_boss = true;
	//----------------- AMOUNT OF ENEMIES AT EACH SPAWN POINT

	int amount_at_point_0 = 1;
	int amount_at_point_1 = 2;
	int amount_at_point_2 = 2;
	int amount_at_point_3 = 1;
	int amount_at_point_4 = 2;
	int amount_at_point_5 = 1;
	int amount_at_point_6 = 2;

	int offset_spawn_right = 250;
	int offset_spawn_left = 150;
	
	//---------------- SPAWN POINT COORDINATE-Y

	int spawn_0_0_y = 150;	//spawn point 0 enemy 0
	
	int spawn_1_0_y = 100;  //spawn point 1 enemy 0
	int spawn_1_1_y = 110;  //spawn point 1 enemy 1
							
	int spawn_2_0_y = 100;
	int spawn_2_1_y = 200;

	int spawn_3_0_y = 300;
	
	int spawn_4_0_y = 500;
	int spawn_4_1_y = 300;
	
	int spawn_5_0_y = 200;

	int spawn_6_0_y = 200;
	int spawn_6_1_y = 400;

	
	bool trigger_0_reached = false;
	bool trigger_1_reached = false;
	bool trigger_2_reached = false;
	bool trigger_3_reached = false;
	bool trigger_4_reached = false;
	bool trigger_5_reached = false;
	bool trigger_6_reached = false;


};

#endif