#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleSceneRound1.h"
#include "Garcia.h"
#include "GarciaFSM.h"
#include "Antonio.h"
#include "AntonioFSM.h"
#include "ModuleRender.h"
#include "Player.h"
#include "ModuleParticles.h"

ModuleEnemies::ModuleEnemies(bool active) : Module(active) {}

ModuleEnemies::~ModuleEnemies()
{}

// Load assets
bool ModuleEnemies::Start()
{
	LOG("Loading enemies prototypes");
	tx_enemies = App->textures->Load("assets/spritesheets/enemies.png");

	garcia_prototype = new Garcia(tx_enemies, nullptr, "garcia", entity_type::GARCIA, { 0, 0 }, 0);
	antonio_prototype = new Antonio(tx_enemies, nullptr, "antonio", entity_type::ANTONIO, { 0, 0 }, 0);
	antonio_prototype->cast_left = { -App->renderer->camera.x * App->renderer ->camera_speed/SCREEN_SIZE - antonio_prototype->offset_cast_x_left, antonio_prototype->offset_cast_y };
	antonio_prototype->cast_right = { -App->renderer->camera.x * App->renderer->camera_speed /SCREEN_SIZE + SCREEN_WIDTH - antonio_prototype->offset_cast_x_right, antonio_prototype->offset_cast_y };
	antonio_prototype->spawn_position = { -App->renderer->camera.x * App->renderer->camera_speed /SCREEN_SIZE + SCREEN_WIDTH, antonio_prototype->offset_cast_y };
	
	//Initialize spawnpoints array
	spawn_points = new iPoint*[max_spawn_points];
	spawn_points[0] = new iPoint[amount_at_point_0];
	spawn_points[1] = new iPoint[amount_at_point_1];
	spawn_points[2] = new iPoint[amount_at_point_2];	
	spawn_points[3] = new iPoint[amount_at_point_3];
	spawn_points[4] = new iPoint[amount_at_point_4];
	spawn_points[5] = new iPoint[amount_at_point_5];	
	spawn_points[6] = new iPoint[amount_at_point_6];

	spawn_points[0][0] = iPoint(starting_trigger + offset_spawn_right, spawn_0_0_y);
	
	spawn_points[1][0] = iPoint(starting_trigger + 100 + offset_spawn_right, spawn_1_0_y);
	spawn_points[1][1] = iPoint(starting_trigger + 100 - offset_spawn_left, spawn_1_1_y);

	spawn_points[2][0] = iPoint(starting_trigger + 200 + offset_spawn_right, spawn_2_0_y);
	spawn_points[2][1] = iPoint(starting_trigger + 200 - offset_spawn_left, spawn_2_1_y);
	spawn_points[2][2] = iPoint(starting_trigger + 200 + offset_spawn_left, spawn_2_2_y);

	spawn_points[3][0] = iPoint(starting_trigger + 300 + offset_spawn_right, spawn_3_0_y);
	spawn_points[3][1] = iPoint(starting_trigger + 300 - offset_spawn_left, spawn_3_1_y);
	spawn_points[3][2] = iPoint(starting_trigger + 300 + offset_spawn_right, spawn_3_2_y);

	spawn_points[4][0] = iPoint(starting_trigger + 400 - offset_spawn_left, spawn_4_0_y);
	spawn_points[4][1] = iPoint(starting_trigger + 400 + offset_spawn_right, spawn_4_1_y);
	spawn_points[4][2] = iPoint(starting_trigger + 400 - offset_spawn_left, spawn_4_2_y);
	spawn_points[4][3] = iPoint(starting_trigger + 400 + offset_spawn_right, spawn_4_3_y);

	spawn_points[5][0] = iPoint(starting_trigger + 500 - offset_spawn_left, spawn_5_0_y);
	spawn_points[5][1] = iPoint(starting_trigger + 500 + offset_spawn_right, spawn_5_1_y);

	spawn_points[6][0] = iPoint(starting_trigger + 600 +offset_spawn_right, spawn_6_0_y);
	spawn_points[6][1] = iPoint(starting_trigger + 600 +offset_spawn_right, spawn_6_1_y);

	//Initialize array of amount of enemies at each spawn point
	amount_at_points = new int[max_spawn_points];
	amount_at_points[0] = amount_at_point_0;
	amount_at_points[1] = amount_at_point_1;
	amount_at_points[2] = amount_at_point_2;
	amount_at_points[3] = amount_at_point_3;
	amount_at_points[4] = amount_at_point_4;
	amount_at_points[5] = amount_at_point_5;
	amount_at_points[6] = amount_at_point_6;

	//Initialize reached_triggers array
	reached_triggers = new int[max_spawn_points];
	memset(reached_triggers, 0, max_spawn_points * sizeof(int));

	return true;
}

// Unload assets
bool ModuleEnemies::CleanUp()
{
	LOG("Unloading enemies");
	RELEASE(garcia_prototype);
	RELEASE(antonio_prototype);
	
	for (int i = 0; i < max_spawn_points; i++)
	{
		RELEASE_ARRAY(spawn_points[i]);
	}

	RELEASE_ARRAY(spawn_points);
	RELEASE_ARRAY(amount_at_points);
	RELEASE_ARRAY(reached_triggers);

	return true;
}

update_status ModuleEnemies::Update()
{
	//---------------------------------------- GENERATE ENEMIES --------------------------------------------------------------------
	//test enemies spawn
	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		first_trigger_reached = true;
	}
	if (first_trigger_reached)
	{
		first_trigger_reached = false;
		GenerateEnemy(entity_type::GARCIA, { 800, 150 }, App->player->the_player, App->scene_round1->dynamic_entities);
		GenerateEnemy(entity_type::ANTONIO, antonio_prototype->spawn_position, App->player->the_player, App->scene_round1->dynamic_entities);
	}

	//LOG("player x=%d", App->player->the_player->position.x);
	//----------
	
	//Trigger enemies generation
	for (int i = 0; i < max_spawn_points; i++)
	{
		if (App->player->the_player->position.x >= starting_trigger + i * 100 && reached_triggers[i] == 0)
		{
			SpawnEnemies(i, amount_at_points[i], entity_type::GARCIA);
			reached_triggers[i] = 1;
			break;
		}
	}

	if (App->scene_round1->end_of_scene_clear && spawn_boss)
	{
		antonio_prototype->cast_left = { -App->renderer->camera.x * App->renderer->camera_speed / SCREEN_SIZE - antonio_prototype->offset_cast_x_left, antonio_prototype->offset_cast_y };
		antonio_prototype->cast_right = { -App->renderer->camera.x * App->renderer->camera_speed / SCREEN_SIZE + SCREEN_WIDTH - antonio_prototype->offset_cast_x_right, antonio_prototype->offset_cast_y };
		iPoint spawn_position = { -App->renderer->camera.x * App->renderer->camera_speed / SCREEN_SIZE + SCREEN_WIDTH, antonio_prototype->offset_cast_y };
		GenerateEnemy(entity_type::ANTONIO, spawn_position, App->player->the_player, App->scene_round1->dynamic_entities);
		spawn_boss = false;

		//Recalculate boomerang ranges with the position of the camera
		App->particles->boomerang_prototype->max_range_left = { -App->renderer->camera.x * App->renderer->camera_speed / SCREEN_SIZE, App->particles->boomerang_prototype->max_range_y };
		App->particles->boomerang_prototype->max_range_right = { -App->renderer->camera.x * App->renderer->camera_speed / SCREEN_SIZE + SCREEN_WIDTH, App->particles->boomerang_prototype->max_range_y };		
	}

	return UPDATE_CONTINUE;
}

//--------------------------------------- PUT ENEMIES ON THE SCENARIO -------------------------------------

void ModuleEnemies::SpawnEnemies(int spawn_point, int amount, entity_type type)
{
	for (int i = 0; i < amount; i++)
	{	
		//debug test
		iPoint spwn = spawn_points[spawn_point][i];

		GenerateEnemy(type, spawn_points[spawn_point][i], App->player->the_player, App->scene_round1->dynamic_entities);
	}
}

void ModuleEnemies::GenerateEnemy(entity_type type, iPoint position, Player *player, std::list<Entity*> &dynamic_entities)
{
	switch (type)
	{
	case entity_type::GARCIA:
		{
			Garcia *garcia = new Garcia(*garcia_prototype);
			garcia->position = position;
			garcia->depth = position.y;
			garcia->garcia_fsm = new GarciaFSM(garcia);
			garcia->SetPlayer(player);

			LOG("Adding garcia colliders to ModuleCollision");
			garcia->body_collider = App->collision->AddCollider(garcia_prototype->body_rect, garcia, collider_type::ENEMY_BODY);
			garcia->hit_collider = App->collision->AddCollider(garcia_prototype->hit_rect, garcia, collider_type::ENEMY_HIT);
			garcia->body_collider->SetPos(garcia->position.x + garcia_prototype->body_collider_offset_right, garcia->position.y);
			garcia->hit_collider->SetPos(garcia->position.x + garcia_prototype->hit_collider_offset_right, garcia->position.y);

			dynamic_entities.push_back(garcia);			
			break;
		}
	case entity_type::ANTONIO:
		{
			Antonio *antonio = new Antonio(*antonio_prototype);
			antonio->position = position;
			antonio->depth = position.y + antonio->ref_y;
			antonio->antonio_fsm = new AntonioFSM(antonio);
			antonio->SetPlayer(player);

			LOG("Adding antonio colliders to ModuleCollision");
			antonio->body_collider = App->collision->AddCollider(antonio_prototype->body_rect, antonio, collider_type::ENEMY_BODY);
			antonio->hit_collider = App->collision->AddCollider(antonio_prototype->hit_rect, antonio, collider_type::ENEMY_HIT);
			antonio->body_collider->SetPos(antonio->position.x + antonio_prototype->body_collider_offset_left, antonio->position.y + antonio_prototype->body_collider_offset_y);
			antonio->hit_collider->SetPos(antonio->position.x + antonio_prototype->hit_collider_offset_left, antonio->position.y + antonio_prototype->hit_collider_offset_y);

			dynamic_entities.push_back(antonio);			
			break;
		}
	}
}



