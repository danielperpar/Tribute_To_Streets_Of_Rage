#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleSceneRound1.h"
#include "JSONDataLoader.h"
#include "Utilities.h"
#include "ModuleInput.h"
#include "ScenarioElement.h"
#include "GUI.h"
#include <algorithm>
#include "PlayerFSM.h"
#include "Garcia.h"
#include "GarciaFSM.h"

ModuleSceneRound1::ModuleSceneRound1(bool active) : Module(active){}

ModuleSceneRound1::~ModuleSceneRound1(){}

bool ModuleSceneRound1::Init()
{
	LOG("Loading assets for scene round1");
	LoadSceneAssets();
	return true;
}

bool ModuleSceneRound1::Start()
{
	LOG("Creating scenario entities");
	
	//Order matters, rendered following instantiation order
	Entity *background = new ScenarioElement(tx_background, nullptr, "background", entity_type::SCENARIO, { 0,32 }, 0);
	scenario_entities.push_back(background);

	Entity *pinepot1 = new ScenarioElement(tx_neons, &neonPinEPot, "pinepot1", entity_type::SCENARIO, { 768, 32 }, 0);
	scenario_entities.push_back(pinepot1);

	Entity *pinepot2 = new ScenarioElement(tx_neons, &neonPinEPot, "pinepot2", entity_type::SCENARIO, { 3605, 32 }, 0);
	scenario_entities.push_back(pinepot2);

	Entity *breakfastdinner1 = new ScenarioElement(tx_neons, &neonBreakfastDiner, "breakfastdinner1", entity_type::SCENARIO, { 1028, 31 }, 0);
	scenario_entities.push_back(breakfastdinner1);

	Entity *breakfastdinner2 = new ScenarioElement(tx_neons, &neonBreakfastDiner, "breakfastdinner2", entity_type::SCENARIO, { 1604, 31 }, 0);
	scenario_entities.push_back(breakfastdinner2);

	Entity *LDevo1 = new ScenarioElement(tx_neons, &neonLDevo, "LDevo1", entity_type::SCENARIO, { 1338, 32 }, 0);
	scenario_entities.push_back(LDevo1);

	Entity *LDevo2 = new ScenarioElement(tx_neons, &neonLDevo, "LDevo2", entity_type::SCENARIO, { 1850, 32 }, 0);
	scenario_entities.push_back(LDevo2);

	Entity *ranchShop1 = new ScenarioElement(tx_neons, &neonRachShop, "ranchShop1", entity_type::SCENARIO, { 0, 32 }, 0);
	scenario_entities.push_back(ranchShop1);

	Entity *ranchShop2 = new ScenarioElement(tx_neons, &neonRachShop, "ranchSop2", entity_type::SCENARIO, { 2053, 32 }, 0);
	scenario_entities.push_back(ranchShop2);

	Entity *abcShop1 = new ScenarioElement(tx_neons, &neonAbcShop, "abcShop1", entity_type::SCENARIO, { 567, 32 }, 0);
	scenario_entities.push_back(abcShop1);

	Entity *abcShop2 = new ScenarioElement(tx_neons, &neonAbcShop, "abcShop2", entity_type::SCENARIO, { 2875, 32 }, 0);
	scenario_entities.push_back(abcShop2);

	Entity *cafeRestaurant1 = new ScenarioElement(tx_neons, &neonCafeRestaurant, "cafeRestaurant1", entity_type::SCENARIO, { 132, 96 }, 0);
	scenario_entities.push_back(cafeRestaurant1);

	Entity *cafeRestaurant2 = new ScenarioElement(tx_neons, &neonCafeRestaurant, "cafeRestaurant2", entity_type::SCENARIO, { 1864, 96 }, 0);
	scenario_entities.push_back(cafeRestaurant2);

	Entity *cafeRestaurant3 = new ScenarioElement(tx_neons, &neonCafeRestaurant, "cafeRestaurant3", entity_type::SCENARIO, { 2440, 96 }, 0);
	scenario_entities.push_back(cafeRestaurant3);

	Entity *cafeRestaurant4 = new ScenarioElement(tx_neons, &neonCafeRestaurant, "cafeRestaurant4", entity_type::SCENARIO, { 3128, 48 }, 0);
	scenario_entities.push_back(cafeRestaurant4);

	Entity *cafeRestaurant5 = new ScenarioElement(tx_neons, &neonCafeRestaurant, "cafeRestaurant5", entity_type::SCENARIO, { 3224, 48 }, 0);
	scenario_entities.push_back(cafeRestaurant5);


	//--------------------------------- FOREGROUND ELEMENTS ---------------------------------
	
	foreground = new ScenarioElement(tx_foreground, nullptr, "foreground", entity_type::SCENARIO, { 0,32 }, 0);
	gui = new GUI(tx_gui, nullptr, "gui", entity_type::GUI, { 0, 0 }, 0); //GUI follows the camera
	
	//---------------------------------------------------------------------------------------

	LOG("Creating the player");
	the_player = new Player(tx_player, nullptr, "player", entity_type::PLAYER, { 800, 150 }, 150);
	
	LOG("Adding the player colliders to ModuleCollision");	
	the_player->body_collider = App->collision->AddCollider(the_player->body_rect, the_player, collider_type::PLAYER_BODY);
	the_player->hit_collider= App->collision->AddCollider(the_player->hit_rect, the_player, collider_type::PLAYER_HIT);
	the_player->body_collider->SetPos(the_player->position.x + the_player->body_collider_offset_right, the_player->position.y);
	the_player->hit_collider->SetPos(the_player->position.x + the_player->hit_collider_offset_right, the_player->position.y);
	
	dynamic_entities.push_back(the_player);

	LOG("Creating enemy prototypes");
	garcia_prototype = new Garcia(tx_garcia, nullptr, "garcia", entity_type::GARCIA, {0, 0}, 0);
	
	//App->audio->PlayMusic("assets/audio/03_-_Fighting_in_the_Street_stage_1_.ogg", 1.0f);

	return true;
}


// Update: draw background
update_status ModuleSceneRound1::Update()
{
	// ------------------------------------------------  RECEIVE PLAYER INPUT -----------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		the_player->walk_left = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE)
	{
		the_player->walk_left = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		the_player->walk_right = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE)
	{
		the_player->walk_right = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		the_player->walk_up = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE)
	{
		the_player->walk_up = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		the_player->walk_down = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE)
	{
		the_player->walk_down = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN && (the_player->player_fsm->GetCurrState() == PlayerFSM::State::WALK || 
		the_player->player_fsm->GetCurrState() == PlayerFSM::State::IDLE || 
		the_player->player_fsm->GetCurrState() == PlayerFSM::State::GRAB ||
		the_player->player_fsm->GetCurrState() == PlayerFSM::State::POST_AIR_ATTACK))
	{
		the_player->jump = true;
		the_player->landed = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
	{
		the_player->jump = false;		
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		the_player->hit_hold = true;
		the_player->hit_down = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE)
	{
		the_player->hit_hold = false;
		the_player->hit_down = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{
		the_player->hit_down = true;
	}
	
	//test damaged
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{
		the_player->damaged = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
	{
		the_player->knocked_down = true;
	}

	//---------------------------------------- GENERATE ENEMIES --------------------------------------------------------------------
	//test enemies spawn
	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		first_trigger_reached = true;
	}

	if (first_trigger_reached)
	{
		first_trigger_reached = false;
		Garcia* garcia = (Garcia*)GenerateEnemy(entity_type::GARCIA, { 800, 150 }, the_player, dynamic_entities);

		LOG("Adding garcia colliders to ModuleCollision");
		garcia->body_collider = App->collision->AddCollider(garcia->body_rect, garcia, collider_type::ENEMY_BODY);
		garcia->hit_collider = App->collision->AddCollider(garcia->hit_rect, garcia, collider_type::ENEMY_HIT);
		garcia->body_collider->SetPos(garcia->position.x + garcia->body_collider_offset_right, garcia->position.y);
		garcia->hit_collider->SetPos(garcia->position.x + garcia->hit_collider_offset_right, garcia->position.y);
		
		//GenerateEnemy(entity_type::GARCIA, { 950, 150 }, the_player, dynamic_entities);										 
	}

	//----------------------------------------UPDATE ENTITIES FSM ------------------------------------------------------------------
	for (std::vector<Entity*>::iterator it = dynamic_entities.begin(); it != dynamic_entities.end(); it++)
	{
		(*it)->UpdateFSM();
	}


	// Draw everything --------------------------------------

	//Sort dynamic entitites according to its depth in ascendant order
	std::sort(dynamic_entities.begin(), dynamic_entities.end(), [](Entity *e1, Entity *e2) {return (e1->depth < e2->depth); });

	//Draw scenario
	for (std::vector<Entity*>::iterator it = scenario_entities.begin(); it != scenario_entities.end(); it++)
	{		
		if((*it)->curr_anim != nullptr)
			App->renderer->Blit((*it)->texture, (*it)->position.x, (*it)->position.y, &((*it)->curr_anim->GetCurrentFrame()));
		else
			App->renderer->Blit((*it)->texture, (*it)->position.x, (*it)->position.y, nullptr);
	}

	//Draw dynamic entities, i.e. : player, enemy, etc
	for (std::vector<Entity*>::iterator it = dynamic_entities.begin(); it != dynamic_entities.end(); it++)
	{
		if ((*it)->curr_anim != nullptr)
			App->renderer->Blit((*it)->texture, (*it)->position.x, (*it)->position.y, &((*it)->curr_anim->GetCurrentFrame()));
		else
			App->renderer->Blit((*it)->texture, (*it)->position.x, (*it)->position.y, nullptr);
	}

	//Draw foreground elements
	App->renderer->Blit(foreground->texture, foreground->position.x, foreground->position.y, nullptr);
	App->renderer->Blit(gui->texture, gui->position.x, gui->position.y, nullptr, true);

	return UPDATE_CONTINUE;
}


// UnLoad assets
bool ModuleSceneRound1::CleanUp()
{
	LOG("Unloading scene");

	//release scene entities
	for (std::vector<Entity*>::iterator it = scenario_entities.begin(); it != scenario_entities.end(); it++)
	{
		RELEASE(*it);
	}
	scenario_entities.clear();

	for (std::vector<Entity*>::iterator it = dynamic_entities.begin(); it != dynamic_entities.end(); it++)
	{
		RELEASE(*it);
	}
	dynamic_entities.clear();

	RELEASE(foreground);
	RELEASE(gui);

	RELEASE(garcia_prototype);

	App->textures->Unload(tx_background);
	App->textures->Unload(tx_foreground);
	App->textures->Unload(tx_neons);
	App->textures->Unload(tx_gui);
	App->player->Disable();
	App->enemies->Disable();
	App->collision->Disable();
	App->particles->Disable();

	return true;
}
//--------------------------------------- PUT ENEMIES ON THE SCENARIO -------------------------------------

Entity* ModuleSceneRound1::GenerateEnemy(entity_type type, iPoint position, Player *player, std::vector<Entity*> &dynamic_entities)
{
	Entity *enemy = nullptr;
	switch (type) 
	{
		case entity_type::GARCIA:
			Garcia *garcia = new Garcia(*garcia_prototype);
			garcia->position = position;
			garcia->depth = position.y;
			garcia->garcia_fsm = new GarciaFSM(garcia);
			garcia->SetPlayer(player);
			dynamic_entities.push_back(garcia);
			enemy = garcia;
		break;
	}

	return enemy;
}

void ModuleSceneRound1::LoadSceneAssets()
{
	//------------------------------------ LOAD SCENE TEXTURES ---------------------------------------------
	//Scenario
	tx_background = App->textures->Load("assets/spritesheets/StreetsOfRage_round1_background_neon_out.png");
	tx_foreground = App->textures->Load("assets/spritesheets/StreetsOfRage_round1_foreground.png");
	tx_neons = App->textures->Load("assets/spritesheets/neones.png");
	tx_gui = App->textures->Load("assets/spritesheets/gui.png");

	//Player
	tx_player = App->textures->Load("assets/spritesheets/axel.png");

	//Enemies
	tx_garcia = App->textures->Load("assets/spritesheets/enemies.png");
	//Scenario items

	//------------------------------------ LOAD SCENE ANIMATIONS ----------------------------------------------
	//Scenario 
	{
		JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonPinEPot", animation_list, neonPinEPot);
		neonPinEPot.loop = true;
		neonPinEPot.speed = 0.05f;
		Utilities::free_list(animation_list);

		JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonBreakfastDiner", animation_list, neonBreakfastDiner);
		neonBreakfastDiner.loop = true;
		neonBreakfastDiner.speed = 0.05f;
		Utilities::free_list(animation_list);

		JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonLDevo", animation_list, neonLDevo);
		neonLDevo.loop = true;
		neonLDevo.speed = 0.05f;
		Utilities::free_list(animation_list);

		JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonRachShop", animation_list, neonRachShop);
		neonRachShop.loop = true;
		neonRachShop.speed = 0.05f;
		Utilities::free_list(animation_list);

		JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonAbcShop", animation_list, neonAbcShop);
		neonAbcShop.loop = true;
		neonAbcShop.speed = 0.05f;
		Utilities::free_list(animation_list);

		JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonCafeRestaurant", animation_list, neonCafeRestaurant);
		neonCafeRestaurant.loop = true;
		neonCafeRestaurant.speed = 0.05f;
		Utilities::free_list(animation_list);
	}
	
}