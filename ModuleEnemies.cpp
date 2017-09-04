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
	
	//Initialize array of amount of enemies at each spawn point
	amount_at_points = new int[max_spawn_points];

	for (int i = 0; i < max_spawn_points; i++)
	{		
		amount_at_points[i] = (i % 2) + 1;
	}

	//Initialize spawnpoints array
	spawn_points = new iPoint*[max_spawn_points];

	for (int i = 0; i < max_spawn_points; i++)
	{
		spawn_points[i] = new iPoint[amount_at_points[i]];
	}

	for (int i = 0; i < max_spawn_points; i++)
	{
		for (int j = 0; j < amount_at_points[i]; j++)
		{
			int offset;
			i % 2 == 0 ? offset = offset_spawn_right : offset = -offset_spawn_left;
			//spawn points each 100 + offset units in axis 0X and 100,200,300 units in axis 0Y 
			spawn_points[i][j] = iPoint(starting_trigger + i * 100 + j * 100 + offset, ((i % 3) + 1) * 100 + ((i % 3) + 1) * 30);

			//LOG("spawn point[%d][%d] = (%d,%d)", i, j, spawn_points[i][j].x, spawn_points[i][j].y);
		}
	}

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
	/*if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		GenerateEnemy(entity_type::GARCIA, { 800, 150 }, App->player->the_player, App->scene_round1->dynamic_entities);
		GenerateEnemy(entity_type::ANTONIO, antonio_prototype->spawn_position, App->player->the_player, App->scene_round1->dynamic_entities);
	}*/

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
	
		App->scene_round1->show_boss_health_bar = true;
	
	}

	return UPDATE_CONTINUE;
}

//--------------------------------------- PUT ENEMIES ON THE SCENARIO -------------------------------------

void ModuleEnemies::SpawnEnemies(int spawn_point, int amount, entity_type type)
{
	for (int i = 0; i < amount; i++)
	{	
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



