#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleSceneRound1.h"
#include "JSONDataLoader.h"
#include "Utilities.h"
#include "ScenarioElement.h"
#include "GUI.h"
#include <algorithm>
#include "Enemy.h"
#include "ModuleParticles.h"

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
	go_sign = new GUI(tx_go_sign, &goSignBlink, "go_sign", entity_type::GUI, { 800, 160 }, 0); //follows the camera
	//---------------------------------------------------------------------------------------
	
	//App->audio->PlayMusic("assets/audio/03_-_Fighting_in_the_Street_stage_1_.ogg", 1.0f);

	return true;
}

update_status ModuleSceneRound1::PreUpdate()
{
	if (dynamic_entities.size() != 0)
	{
		for (std::list<Entity*>::iterator it = dynamic_entities.begin(); it != dynamic_entities.end();)
		{
			entity_erased = false;
			
			if ((*it)->type == entity_type::GARCIA || (*it)->type == entity_type::ANTONIO)
			{
				if (((Enemy*)(*it))->destroy_this)
				{
					RELEASE(*it);
					it = dynamic_entities.erase(it);
					entity_erased = true;
				}			
			}

			if (!entity_erased)
				it++;
		}
	}
	return UPDATE_CONTINUE;
}


// Update: draw background
update_status ModuleSceneRound1::Update()
{
	//----------------------------------------UPDATE ENTITIES FSM ------------------------------------------------------------------
	for (std::list<Entity*>::iterator it = dynamic_entities.begin(); it != dynamic_entities.end(); it++)
	{
		(*it)->UpdateFSM();
	}


	// Draw everything --------------------------------------

	//Sort dynamic entitites according to its depth in ascendant order
	dynamic_entities.sort([](Entity *e1, Entity *e2) {return (e1->depth < e2->depth); });


	//Draw scenario
	for (std::vector<Entity*>::iterator it = scenario_entities.begin(); it != scenario_entities.end(); it++)
	{		
		if((*it)->curr_anim != nullptr)
			App->renderer->Blit((*it)->texture, (*it)->position.x, (*it)->position.y, &((*it)->curr_anim->GetCurrentFrame()));
		else
			App->renderer->Blit((*it)->texture, (*it)->position.x, (*it)->position.y, nullptr);
	}

	//Draw dynamic entities, i.e. : player, enemy, etc
	for (std::list<Entity*>::iterator it = dynamic_entities.begin(); it != dynamic_entities.end(); it++)
	{
		if ((*it)->curr_anim != nullptr)
			App->renderer->Blit((*it)->texture, (*it)->position.x, (*it)->position.y, &((*it)->curr_anim->GetCurrentFrame()));
		else
			App->renderer->Blit((*it)->texture, (*it)->position.x, (*it)->position.y, nullptr);
	}

	//Draw particles
	for (std::list<Particle*>::iterator it = App->particles->active.begin(); it != App->particles->active.end(); it++)
	{
		App->renderer->Blit((*it)->texture, (*it)->position.x, (*it)->position.y, &(*it)->curr_anim->GetCurrentFrame());
	}

	//Draw foreground elements
	App->renderer->Blit(foreground->texture, foreground->position.x, foreground->position.y, nullptr);
	App->renderer->Blit(gui->texture, gui->position.x, gui->position.y, nullptr, true);

	if (show_go)
	{
		App->renderer->Blit(go_sign->texture, go_sign->position.x, go_sign->position.y, &go_sign->curr_anim->GetCurrentFrame(), true);
		go_sign_show_counter++;
		if (go_sign_show_counter == go_sign_show_frames)
		{
			go_sign_show_counter = 0;
			show_go = false;
		}
	}

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

	for (std::list<Entity*>::iterator it = dynamic_entities.begin(); it != dynamic_entities.end(); it++)
	{
		RELEASE(*it);
	}
	dynamic_entities.clear();

	RELEASE(foreground);
	RELEASE(gui);
	RELEASE(go_sign);

	return true;
}

void ModuleSceneRound1::LoadSceneAssets()
{
	//------------------------------------ LOAD SCENE TEXTURES ---------------------------------------------
	//Scenario
	tx_background = App->textures->Load("assets/spritesheets/StreetsOfRage_round1_background_neon_out.png");
	tx_foreground = App->textures->Load("assets/spritesheets/StreetsOfRage_round1_foreground.png");
	tx_neons = App->textures->Load("assets/spritesheets/neones.png");
	tx_gui = App->textures->Load("assets/spritesheets/gui.png");
	tx_go_sign = App->textures->Load("assets/spritesheets/round1_ground_items.png");

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

		JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "goSign", animation_list, goSignBlink);
		goSignBlink.loop = true;
		goSignBlink.speed = 0.1f;
		Utilities::free_list(animation_list);

		JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "goSignTransparent", animation_list, goSignTransparent);
		goSignTransparent.loop = true;
		goSignTransparent.speed = 0.1f;
		Utilities::free_list(animation_list);
	}
	
}