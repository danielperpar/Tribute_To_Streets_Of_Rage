#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include <list>
#include "Point.h"
#include "Entity.h"


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

	//------------------------------------ENEMIES SPAWN TRIGGERS ----------------------------------------
	bool first_trigger_reached = false;
	
private:
	SDL_Texture *tx_enemies = nullptr;
	Garcia *garcia_prototype = nullptr;
	Antonio *antonio_prototype = nullptr;
	void GenerateEnemy(entity_type type, iPoint position, Player *player, std::list<Entity*> &dynamic_entities);
	void SpawnEnemies(int spawn_point, int amount, entity_type type);

	iPoint **spawn_points;
	int max_spawn_points = 7;
	int *amount_at_points;
	int *triggers;
	int *reached_triggers;
	
	//----------------- AMOUNT OF ENEMIES AT EACH SPAWN POINT

	int amount_at_point_0 = 1;
	int amount_at_point_1 = 2;
	int amount_at_point_2 = 3;
	int amount_at_point_3 = 3;
	int amount_at_point_4 = 4;
	int amount_at_point_5 = 2;
	int amount_at_point_6 = 2;

	int offset_spawn_right = 250;
	int offset_spawn_left = 100;
	
	//---------------- SPAWN POINT COORDINATE-Y

	int spawn_0_0_y = 150;	//spawn point 0 enemy 0
	
	int spawn_1_0_y = 100;  //spawn point 1 enemy 0
	int spawn_1_1_y = 110;  //spawn point 1 enemy 1

	int spawn_2_0_y = 100;
	int spawn_2_1_y = 150;
	int spawn_2_2_y = 200;

	int spawn_3_0_y = 300;
	int spawn_3_1_y = 200;
	int spawn_3_2_y = 100;

	int spawn_4_0_y = 500;
	int spawn_4_1_y = 400;
	int spawn_4_2_y = 300;
	int spawn_4_3_y = 200;

	int spawn_5_0_y = 200;
	int spawn_5_1_y = 300;

	int spawn_6_0_y = 200;
	int spawn_6_1_y = 400;

	
	//Enemies spawn triggers
	int player_trigger_0 = 800;
	int player_trigger_1 = 900;
	int player_trigger_2 = 1000;
	int player_trigger_3 = 1100;
	int player_trigger_4 = 1200;
	int player_trigger_5 = 1300;
	int player_trigger_6 = 1400;

	bool trigger_0_reached = false;
	bool trigger_1_reached = false;
	bool trigger_2_reached = false;
	bool trigger_3_reached = false;
	bool trigger_4_reached = false;
	bool trigger_5_reached = false;
	bool trigger_6_reached = false;


};

#endif