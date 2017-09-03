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
#include "HealthBar.h"
#include <algorithm>
#include "Enemy.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "Player.h"
#include "ModuleFadeToBlack.h"
#include "ModuleTitle.h"

ModuleSceneRound1::ModuleSceneRound1(bool active) : Module(active){}

ModuleSceneRound1::~ModuleSceneRound1(){}

bool ModuleSceneRound1::Init()
{
	LOG("Loading assets for scene round1");
	LoadSceneAssets();
	LoadConfigInfo();
	return true;
}

bool ModuleSceneRound1::Start()
{
	LOG("Creating scenario entities");
	
	//Order matters, rendered following instantiation order
	Entity *background = new ScenarioElement(tx_background, nullptr, "background", entity_type::SCENARIO, { 0,32 }, 0);
	scenario_entities.push_back(background);

	Entity *pinepot1 = new ScenarioElement(tx_neons, &neon_pinepot, "pinepot1", entity_type::SCENARIO, { 768, 32 }, 0);
	scenario_entities.push_back(pinepot1);

	Entity *pinepot2 = new ScenarioElement(tx_neons, &neon_pinepot, "pinepot2", entity_type::SCENARIO, { 3605, 32 }, 0);
	scenario_entities.push_back(pinepot2);

	Entity *breakfastdinner1 = new ScenarioElement(tx_neons, &neon_breakfast_dinner, "breakfastdinner1", entity_type::SCENARIO, { 1028, 31 }, 0);
	scenario_entities.push_back(breakfastdinner1);

	Entity *breakfastdinner2 = new ScenarioElement(tx_neons, &neon_breakfast_dinner, "breakfastdinner2", entity_type::SCENARIO, { 1604, 31 }, 0);
	scenario_entities.push_back(breakfastdinner2);

	Entity *LDevo1 = new ScenarioElement(tx_neons, &neon_ldevo, "LDevo1", entity_type::SCENARIO, { 1338, 32 }, 0);
	scenario_entities.push_back(LDevo1);

	Entity *LDevo2 = new ScenarioElement(tx_neons, &neon_ldevo, "LDevo2", entity_type::SCENARIO, { 1850, 32 }, 0);
	scenario_entities.push_back(LDevo2);

	Entity *ranchShop1 = new ScenarioElement(tx_neons, &neon_ranch_shop, "ranchShop1", entity_type::SCENARIO, { 0, 32 }, 0);
	scenario_entities.push_back(ranchShop1);

	Entity *ranchShop2 = new ScenarioElement(tx_neons, &neon_ranch_shop, "ranchSop2", entity_type::SCENARIO, { 2053, 32 }, 0);
	scenario_entities.push_back(ranchShop2);

	Entity *abcShop1 = new ScenarioElement(tx_neons, &neon_abc_shop, "abcShop1", entity_type::SCENARIO, { 567, 32 }, 0);
	scenario_entities.push_back(abcShop1);

	Entity *abcShop2 = new ScenarioElement(tx_neons, &neon_abc_shop, "abcShop2", entity_type::SCENARIO, { 2875, 32 }, 0);
	scenario_entities.push_back(abcShop2);

	Entity *cafeRestaurant1 = new ScenarioElement(tx_neons, &neon_cafe_restaurant, "cafeRestaurant1", entity_type::SCENARIO, { 132, 96 }, 0);
	scenario_entities.push_back(cafeRestaurant1);

	Entity *cafeRestaurant2 = new ScenarioElement(tx_neons, &neon_cafe_restaurant, "cafeRestaurant2", entity_type::SCENARIO, { 1864, 96 }, 0);
	scenario_entities.push_back(cafeRestaurant2);

	Entity *cafeRestaurant3 = new ScenarioElement(tx_neons, &neon_cafe_restaurant, "cafeRestaurant3", entity_type::SCENARIO, { 2440, 96 }, 0);
	scenario_entities.push_back(cafeRestaurant3);

	Entity *cafeRestaurant4 = new ScenarioElement(tx_neons, &neon_cafe_restaurant, "cafeRestaurant4", entity_type::SCENARIO, { 3128, 48 }, 0);
	scenario_entities.push_back(cafeRestaurant4);

	Entity *cafeRestaurant5 = new ScenarioElement(tx_neons, &neon_cafe_restaurant, "cafeRestaurant5", entity_type::SCENARIO, { 3224, 48 }, 0);
	scenario_entities.push_back(cafeRestaurant5);


	//--------------------------------- FOREGROUND ELEMENTS ---------------------------------
	
	foreground = new ScenarioElement(tx_foreground, nullptr, "foreground", entity_type::SCENARIO, { 0,32 }, 0);

	//GUI elements follow camera
	gui = new GUI(tx_gui, &gui_background, "gui", entity_type::GUI, { 0, 0 }, 0); 
	go_sign = new GUI(tx_ground_items, &go_sign_blink, "go_sign", entity_type::GUI, { 800, 160 }, 0); //follows the camera
	player_HP = new HealthBar(anim_player_HP.GetCurrentFrame().w, tx_gui, &anim_player_HP, "player_health_bar", entity_type::GUI, { 24, 51 }, 0);
	boss_HP = new HealthBar(anim_boss_HP.GetCurrentFrame().w, tx_gui, &anim_boss_HP, "antonio_health_bar", entity_type::ANTONIO, { 575, 51 }, 0);
	boss_white_bar = new GUI(tx_gui, &anim_boss_white_bar, "boss_white_bar", entity_type::GUI, boss_HP->position, 0);
	boss_title = new GUI(tx_gui, &anim_boss_title, "boss_title", entity_type::GUI, { 575, 24 }, 0);
	help_text = new GUI(tx_gui, &anim_help_text, "help_text", entity_type::GUI, {266, 20}, 0);
	help_panel = new GUI(tx_gui, &anim_help_panel, "help_panel", entity_type::GUI, {250, 100}, 0);
	god_mode_text = new GUI(tx_gui, &anim_god_mode_text, "god_mode_text", entity_type::GUI, {24,69}, 0);
	thanks_for_playing = new GUI(tx_gui, &anim_thanks, "thanks_for_playing", entity_type::GUI, { 290, 200 }, 0);

	//-------------------------------- HEALTH CHICKENS ---------------------------------
	health_chicken_prototype = new HealthChicken(tx_ground_items, nullptr, "health_chiken", entity_type::HEALTH_CHICKEN, { 0,0 }, 0);
	GenerateChicken(chicken_first_area, chicken_first_area.y - health_chicken_prototype->depth_offset);
	GenerateChicken(chicken_second_area, chicken_second_area.y - health_chicken_prototype->depth_offset);
	GenerateChicken(chicken_third_area, chicken_third_area.y - health_chicken_prototype->depth_offset);
	
	//App->audio->PlayMusic("assets/audio/03_-_Fighting_in_the_Street_stage_1_.ogg", 1.0f);

	return true;
}


// Update: draw background
update_status ModuleSceneRound1::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		show_help = !show_help;
	}

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
	App->renderer->Blit(gui->texture, gui->position.x, gui->position.y, &gui_background.GetCurrentFrame(), true);
	App->renderer->Blit(gui->texture, player_HP->position.x, player_HP->position.y, &anim_player_HP.GetCurrentFrame(), true);
	App->renderer->Blit(gui->texture, help_text->position.x, help_text->position.y, &anim_help_text.GetCurrentFrame(), true);

	if (App->player->the_player->god_mode)
	{
		App->renderer->Blit(gui->texture, god_mode_text->position.x, god_mode_text->position.y, &anim_god_mode_text.GetCurrentFrame(), true);
	}

	if (show_boss_health_bar)
	{
		App->renderer->Blit(gui->texture, boss_white_bar->position.x, boss_white_bar->position.y, &anim_boss_white_bar.GetCurrentFrame(), true);
		App->renderer->Blit(gui->texture, boss_HP->position.x, boss_HP->position.y, &anim_boss_HP.GetCurrentFrame(), true);
		App->renderer->Blit(gui->texture, boss_title->position.x, boss_title->position.y, &anim_boss_title.GetCurrentFrame(), true);
	}

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
	if (show_help)
	{
		App->renderer->Blit(gui->texture, help_panel->position.x, help_panel->position.y, &anim_help_panel.GetCurrentFrame(), true);
	}
	if (show_thanks)
	{
		App->renderer->Blit(thanks_for_playing->texture, thanks_for_playing->position.x, thanks_for_playing->position.y, &thanks_for_playing->curr_anim->GetCurrentFrame(), true);
	}
	return UPDATE_CONTINUE;
}


update_status ModuleSceneRound1::PostUpdate()
{
	if (dynamic_entities.size() != 0)
	{
		for (std::list<Entity*>::iterator it = dynamic_entities.begin(); it != dynamic_entities.end();)
		{
			entity_erased = false;

			if ((*it)->destroy_this)
			{
				RELEASE(*it);
				it = dynamic_entities.erase(it);
				entity_erased = true;
			}

			if (!entity_erased)
				it++;
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
	RELEASE(health_chicken_prototype);
	RELEASE(player_HP);
	RELEASE(boss_HP);
	RELEASE(boss_title);
	RELEASE(boss_white_bar);
	RELEASE(help_text);
	RELEASE(help_panel);
	RELEASE(god_mode_text);
	RELEASE(thanks_for_playing);

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
	tx_ground_items = App->textures->Load("assets/spritesheets/round1_ground_items.png");

	//------------------------------------ LOAD SCENE ANIMATIONS ----------------------------------------------
	//Scenario 
	
	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonPinEPot", animation_list, neon_pinepot);
	neon_pinepot.loop = true;
	neon_pinepot.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonBreakfastDiner", animation_list, neon_breakfast_dinner);
	neon_breakfast_dinner.loop = true;
	neon_breakfast_dinner.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonLDevo", animation_list, neon_ldevo);
	neon_ldevo.loop = true;
	neon_ldevo.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonRachShop", animation_list, neon_ranch_shop);
	neon_ranch_shop.loop = true;
	neon_ranch_shop.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonAbcShop", animation_list, neon_abc_shop);
	neon_abc_shop.loop = true;
	neon_abc_shop.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonCafeRestaurant", animation_list, neon_cafe_restaurant);
	neon_cafe_restaurant.loop = true;
	neon_cafe_restaurant.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "goSign", animation_list, go_sign_blink);
	go_sign_blink.loop = true;
	go_sign_blink.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "goSignTransparent", animation_list, go_sign_transparent);
	go_sign_transparent.loop = true;
	go_sign_transparent.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "guiBackground", animation_list, gui_background);
	gui_background.loop = true;
	gui_background.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerHealthBar", animation_list, anim_player_HP);
	anim_player_HP.loop = true;
	anim_player_HP.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "bossHealthBar", animation_list, anim_boss_HP);
	anim_boss_HP.loop = true;
	anim_boss_HP.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "bossTitle", animation_list, anim_boss_title);
	anim_boss_title.loop = true;
	anim_boss_title.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "bossWhiteBar", animation_list, anim_boss_white_bar);
	anim_boss_white_bar.loop = true;
	anim_boss_white_bar.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "helpText", animation_list, anim_help_text);
	anim_help_text.loop = true;
	anim_help_text.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "helpPanel", animation_list, anim_help_panel);
	anim_help_panel.loop = true;
	anim_help_panel.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "godModeText", animation_list, anim_god_mode_text);
	anim_god_mode_text.loop = true;
	anim_god_mode_text.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "thanksForPlaying", animation_list, anim_thanks);
	anim_thanks.loop = true;
	anim_thanks.speed = 0.1f;
	Utilities::free_list(animation_list);

}

void ModuleSceneRound1::LoadConfigInfo()
{
	chicken_first_area.x = JSONDataLoader::GetNumber("assets/json/config.json", "health_chicken", "chicken_first_area_x");
	chicken_first_area.y = JSONDataLoader::GetNumber("assets/json/config.json", "health_chicken", "chicken_first_area_y");
	chicken_second_area.x = JSONDataLoader::GetNumber("assets/json/config.json", "health_chicken", "chicken_second_area_x");
	chicken_second_area.y = JSONDataLoader::GetNumber("assets/json/config.json", "health_chicken", "chicken_second_area_y");
	chicken_third_area.x = JSONDataLoader::GetNumber("assets/json/config.json", "health_chicken", "chicken_third_area_x");
	chicken_third_area.y = JSONDataLoader::GetNumber("assets/json/config.json", "health_chicken", "chicken_third_area_y");
}

void ModuleSceneRound1::GenerateChicken(iPoint position, int depth)
{
	HealthChicken *chicken = new HealthChicken(*health_chicken_prototype);
	chicken->position = position;
	chicken->depth = depth;
	chicken->curr_anim = &chicken->chicken_animation;

	LOG("Adding chicken collider to ModuleCollision");
	chicken->chicken_collider = App->collision->AddCollider(health_chicken_prototype->chicken_collider_rect, chicken, collider_type::HEALTH_CHICKEN);
	chicken->chicken_collider->SetPos(position.x, position.y);
	dynamic_entities.push_back(chicken);
}