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

	return true;
}

// Unload assets
bool ModuleEnemies::CleanUp()
{
	LOG("Unloading enemies");
	RELEASE(garcia_prototype);
	RELEASE(antonio_prototype);
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
		/*Garcia* garcia = (Garcia*)GenerateEnemy(entity_type::GARCIA, { 800, 150 }, App->player->the_player, App->scene_round1->dynamic_entities);		
		
		LOG("Adding garcia colliders to ModuleCollision");
		garcia->body_collider = App->collision->AddCollider(garcia->body_rect, garcia, collider_type::ENEMY_BODY);
		garcia->hit_collider = App->collision->AddCollider(garcia->hit_rect, garcia, collider_type::ENEMY_HIT);
		garcia->body_collider->SetPos(garcia->position.x + garcia->body_collider_offset_right, garcia->position.y);
		garcia->hit_collider->SetPos(garcia->position.x + garcia->hit_collider_offset_right, garcia->position.y);*/

		Antonio* antonio = (Antonio*)GenerateEnemy(entity_type::ANTONIO, { 850, 80 }, App->player->the_player, App->scene_round1->dynamic_entities);
		
		LOG("Adding antonio colliders to ModuleCollision");
		antonio->body_collider = App->collision->AddCollider(antonio->body_rect, antonio, collider_type::ENEMY_BODY);
		antonio->hit_collider = App->collision->AddCollider(antonio->hit_rect, antonio, collider_type::ENEMY_HIT);
		antonio->body_collider->SetPos(antonio->position.x + antonio->body_collider_offset_left, antonio->position.y + antonio->body_collider_offset_y);
		antonio->hit_collider->SetPos(antonio->position.x + antonio->hit_collider_offset_left, antonio->position.y + antonio->hit_collider_offset_y);

	}
	return UPDATE_CONTINUE;
}

//--------------------------------------- PUT ENEMIES ON THE SCENARIO -------------------------------------

Entity* ModuleEnemies::GenerateEnemy(entity_type type, iPoint position, Player *player, std::list<Entity*> &dynamic_entities)
{
	Entity *enemy = nullptr;
	switch (type)
	{
	case entity_type::GARCIA:
		{
			Garcia *garcia = new Garcia(*garcia_prototype);
			garcia->position = position;
			garcia->depth = position.y;
			garcia->garcia_fsm = new GarciaFSM(garcia);
			garcia->SetPlayer(player);
			dynamic_entities.push_back(garcia);
			enemy = garcia;
			break;
		}
	case entity_type::ANTONIO:
		{
			Antonio *antonio = new Antonio(*antonio_prototype);
			antonio->position = position;
			antonio->depth = position.y + antonio->ref_y;
			antonio->antonio_fsm = new AntonioFSM(antonio);
			antonio->SetPlayer(player);
			dynamic_entities.push_back(antonio);
			enemy = antonio;
			break;
		}
	}

	return enemy;
}



