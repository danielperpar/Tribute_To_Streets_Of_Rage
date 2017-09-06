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
#include "ModuleAudio.h"

ModuleSceneRound1::ModuleSceneRound1(bool active) : Module(active){}

ModuleSceneRound1::~ModuleSceneRound1(){}

bool ModuleSceneRound1::Init()
{
	LOG("Loading assets for scene round1");
	LoadConfig();
	LoadSceneAssets();
	LoadAudio();
	return true;
}

bool ModuleSceneRound1::Start()
{
	LOG("Creating scenario entities");
	
	//Order matters, rendered following instantiation order
	Entity *background = new ScenarioElement(tx_background, nullptr, "background", entity_type::SCENARIO, background_pos, zero_depth);
	scenario_entities.push_back(background);

	Entity *pinepot1 = new ScenarioElement(tx_neons, &neon_pinepot, "pinepot1", entity_type::SCENARIO, pinepot1_pos, zero_depth);
	scenario_entities.push_back(pinepot1);

	Entity *pinepot2 = new ScenarioElement(tx_neons, &neon_pinepot, "pinepot2", entity_type::SCENARIO, pinepot2_pos, zero_depth);
	scenario_entities.push_back(pinepot2);

	Entity *breakfastdinner1 = new ScenarioElement(tx_neons, &neon_breakfast_dinner, "breakfastdinner1", entity_type::SCENARIO, breakfastdinner1_pos, zero_depth);
	scenario_entities.push_back(breakfastdinner1);

	Entity *breakfastdinner2 = new ScenarioElement(tx_neons, &neon_breakfast_dinner, "breakfastdinner2", entity_type::SCENARIO, breakfastdinner2_pos, zero_depth);
	scenario_entities.push_back(breakfastdinner2);

	Entity *LDevo1 = new ScenarioElement(tx_neons, &neon_ldevo, "LDevo1", entity_type::SCENARIO, LDevo1_pos, zero_depth);
	scenario_entities.push_back(LDevo1);

	Entity *LDevo2 = new ScenarioElement(tx_neons, &neon_ldevo, "LDevo2", entity_type::SCENARIO, LDevo2_pos, zero_depth);
	scenario_entities.push_back(LDevo2);

	Entity *ranchShop1 = new ScenarioElement(tx_neons, &neon_ranch_shop, "ranchShop1", entity_type::SCENARIO, ranchShop1_pos, zero_depth);
	scenario_entities.push_back(ranchShop1);

	Entity *ranchShop2 = new ScenarioElement(tx_neons, &neon_ranch_shop, "ranchSop2", entity_type::SCENARIO, ranchShop2_pos, zero_depth);
	scenario_entities.push_back(ranchShop2);

	Entity *abcShop1 = new ScenarioElement(tx_neons, &neon_abc_shop, "abcShop1", entity_type::SCENARIO, abcShop1_pos, zero_depth);
	scenario_entities.push_back(abcShop1);

	Entity *abcShop2 = new ScenarioElement(tx_neons, &neon_abc_shop, "abcShop2", entity_type::SCENARIO, abcShop2_pos, zero_depth);
	scenario_entities.push_back(abcShop2);

	Entity *cafeRestaurant1 = new ScenarioElement(tx_neons, &neon_cafe_restaurant, "cafeRestaurant1", entity_type::SCENARIO, cafeRestaurant1_pos, zero_depth);
	scenario_entities.push_back(cafeRestaurant1);

	Entity *cafeRestaurant2 = new ScenarioElement(tx_neons, &neon_cafe_restaurant, "cafeRestaurant2", entity_type::SCENARIO, cafeRestaurant2_pos, zero_depth);
	scenario_entities.push_back(cafeRestaurant2);

	Entity *cafeRestaurant3 = new ScenarioElement(tx_neons, &neon_cafe_restaurant, "cafeRestaurant3", entity_type::SCENARIO, cafeRestaurant3_pos, zero_depth);
	scenario_entities.push_back(cafeRestaurant3);

	Entity *cafeRestaurant4 = new ScenarioElement(tx_neons, &neon_cafe_restaurant, "cafeRestaurant4", entity_type::SCENARIO, cafeRestaurant4_pos, zero_depth);
	scenario_entities.push_back(cafeRestaurant4);

	Entity *cafeRestaurant5 = new ScenarioElement(tx_neons, &neon_cafe_restaurant, "cafeRestaurant5", entity_type::SCENARIO, cafeRestaurant5_pos, zero_depth);
	scenario_entities.push_back(cafeRestaurant5);

	foreground = new ScenarioElement(tx_foreground, nullptr, "foreground", entity_type::SCENARIO, foreground_pos, zero_depth);

	//GUI elements follow camera
	gui = new GUI(tx_gui, &gui_background, "gui", entity_type::GUI, gui_pos, zero_depth);
	go_sign = new GUI(tx_ground_items, &go_sign_blink, "go_sign", entity_type::GUI, go_sign_pos, zero_depth); //follows the camera
	player_HP = new HealthBar(anim_player_HP.GetCurrentFrame().w, tx_gui, &anim_player_HP, "player_health_bar", entity_type::GUI, player_HP_pos, zero_depth);
	boss_HP = new HealthBar(anim_boss_HP.GetCurrentFrame().w, tx_gui, &anim_boss_HP, "antonio_health_bar", entity_type::ANTONIO, boss_HP_pos, zero_depth);
	boss_white_bar = new GUI(tx_gui, &anim_boss_white_bar, "boss_white_bar", entity_type::GUI, boss_HP->position, zero_depth);
	boss_title = new GUI(tx_gui, &anim_boss_title, "boss_title", entity_type::GUI, boss_title_pos, zero_depth);
	help_text = new GUI(tx_gui, &anim_help_text, "help_text", entity_type::GUI, help_text_pos, zero_depth);
	help_panel = new GUI(tx_gui, &anim_help_panel, "help_panel", entity_type::GUI, help_panel_pos, zero_depth);
	god_mode_text = new GUI(tx_gui, &anim_god_mode_text, "god_mode_text", entity_type::GUI, god_mode_text_pos, zero_depth);
	thanks_for_playing = new GUI(tx_gui, &anim_thanks, "thanks_for_playing", entity_type::GUI, thanks_for_playing_pos, zero_depth);

	//-------------------------------- HEALTH CHICKENS ---------------------------------
	health_chicken_prototype = new HealthChicken(tx_ground_items, nullptr, "health_chiken", entity_type::HEALTH_CHICKEN, { 0,0 }, zero_depth);
	GenerateChicken(chicken_first_area, chicken_first_area.y - health_chicken_prototype->depth_offset);
	GenerateChicken(chicken_second_area, chicken_second_area.y - health_chicken_prototype->depth_offset);
	GenerateChicken(chicken_third_area, chicken_third_area.y - health_chicken_prototype->depth_offset);
	
	App->audio->PlayMusic("assets/audio/Fighting in the street_ stage1.ogg", 1.0f);

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
		if (go_sign->curr_anim->GetCurrentFrameCount() == 0 && go_sign_played == false)
		{
			App->audio->PlayFx(audio_fx::GO_ARROW);	
			go_sign_played = true;
		}
		if (go_sign->curr_anim->GetCurrentFrameCount() == 1)
			go_sign_played = false;

		App->renderer->Blit(go_sign->texture, go_sign->position.x, go_sign->position.y, &go_sign->curr_anim->GetCurrentFrame(), true);
		go_sign_show_counter++;
		if (go_sign_show_counter == go_sign_show_frames)
		{
			go_sign_show_counter = 0;
			show_go = false;
			go_sign_played = false;
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
	neon_pinepot.speed = JSONDataLoader::GetFloat("assets/json/config.json", "scene_round1", "neon_anim_speed");//speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonBreakfastDiner", animation_list, neon_breakfast_dinner);
	neon_breakfast_dinner.loop = true;
	neon_breakfast_dinner.speed = neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonLDevo", animation_list, neon_ldevo);
	neon_ldevo.loop = true;
	neon_ldevo.speed = neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonRachShop", animation_list, neon_ranch_shop);
	neon_ranch_shop.loop = true;
	neon_ranch_shop.speed = neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonAbcShop", animation_list, neon_abc_shop);
	neon_abc_shop.loop = true;
	neon_abc_shop.speed = neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "neonCafeRestaurant", animation_list, neon_cafe_restaurant);
	neon_cafe_restaurant.loop = true;
	neon_cafe_restaurant.speed = neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "goSign", animation_list, go_sign_blink);
	go_sign_blink.loop = true;
	go_sign_blink.speed = neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "goSignTransparent", animation_list, go_sign_transparent);
	go_sign_transparent.loop = true;
	go_sign_transparent.speed = 2 * neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "guiBackground", animation_list, gui_background);
	gui_background.loop = true;
	gui_background.speed = 2 * neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerHealthBar", animation_list, anim_player_HP);
	anim_player_HP.loop = true;
	anim_player_HP.speed = 2 * neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "bossHealthBar", animation_list, anim_boss_HP);
	anim_boss_HP.loop = true;
	anim_boss_HP.speed = 2 * neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "bossTitle", animation_list, anim_boss_title);
	anim_boss_title.loop = true;
	anim_boss_title.speed = 2 * neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "bossWhiteBar", animation_list, anim_boss_white_bar);
	anim_boss_white_bar.loop = true;
	anim_boss_white_bar.speed = 2 * neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "helpText", animation_list, anim_help_text);
	anim_help_text.loop = true;
	anim_help_text.speed = 2 * neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "helpPanel", animation_list, anim_help_panel);
	anim_help_panel.loop = true;
	anim_help_panel.speed = 2 * neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "godModeText", animation_list, anim_god_mode_text);
	anim_god_mode_text.loop = true;
	anim_god_mode_text.speed = 2 * neon_pinepot.speed;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "thanksForPlaying", animation_list, anim_thanks);
	anim_thanks.loop = true;
	anim_thanks.speed = 2 * neon_pinepot.speed;
	Utilities::free_list(animation_list);
}

void ModuleSceneRound1::LoadConfig()
{
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "background_pos", background_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "pinepot1_pos", pinepot1_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "pinepot2_pos", pinepot2_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "breakfastdinner1_pos", breakfastdinner1_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "breakfastdinner2_pos", breakfastdinner2_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "LDevo1_pos", LDevo1_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "LDevo2_pos", LDevo2_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "ranchShop1_pos", ranchShop1_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "ranchShop2_pos", ranchShop2_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "abcShop1_pos", abcShop1_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "abcShop2_pos", abcShop2_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "cafeRestaurant1_pos", cafeRestaurant1_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "cafeRestaurant2_pos", cafeRestaurant2_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "cafeRestaurant3_pos", cafeRestaurant3_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "cafeRestaurant4_pos", cafeRestaurant4_pos);
	JSONDataLoader::GetPoint("assets/json/config.json", "scene_round1", "cafeRestaurant5_pos", cafeRestaurant5_pos);

	chicken_first_area.x = JSONDataLoader::GetInt("assets/json/config.json", "health_chicken", "chicken_first_area_x");
	chicken_first_area.y = JSONDataLoader::GetInt("assets/json/config.json", "health_chicken", "chicken_first_area_y");
	chicken_second_area.x = JSONDataLoader::GetInt("assets/json/config.json", "health_chicken", "chicken_second_area_x");
	chicken_second_area.y = JSONDataLoader::GetInt("assets/json/config.json", "health_chicken", "chicken_second_area_y");
	chicken_third_area.x = JSONDataLoader::GetInt("assets/json/config.json", "health_chicken", "chicken_third_area_x");
	chicken_third_area.y = JSONDataLoader::GetInt("assets/json/config.json", "health_chicken", "chicken_third_area_y");
	upper_limit = JSONDataLoader::GetInt("assets/json/config.json", "scene_round1", "upper_limit");
	lower_limit = JSONDataLoader::GetInt("assets/json/config.json", "scene_round1", "lower_limit");
	right_limit = JSONDataLoader::GetInt("assets/json/config.json", "scene_round1", "right_limit");
	first_stop_x = JSONDataLoader::GetInt("assets/json/config.json", "scene_round1", "first_stop_x");
	second_stop_x = JSONDataLoader::GetInt("assets/json/config.json", "scene_round1", "second_stop_x");
	third_stop_x = JSONDataLoader::GetInt("assets/json/config.json", "scene_round1", "third_stop_x");
	go_sign_show_frames = JSONDataLoader::GetInt("assets/json/config.json", "scene_round1", "go_sign_show_frames");
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

void ModuleSceneRound1::LoadAudio()
{
	/* Loading order

	PLAYER_JUMP,
	PLAYER_LAND,
	PLAYER_ATTACK_MISS,
	PLAYER_ATTACK_HIT,
	PLAYER_ATTACK_HIT_HARD,
	PLAYER_VOICE_AXEL,
	PLAYER_DEAD,
	ENEMY_ATTACK,
	ENEMY_DEAD,
	HEALTH_ITEM,
	GO_ARROW,
	GROUND_HIT
	*/

	App->audio->LoadFx("assets/audio/fx_jump.wav");
	App->audio->LoadFx("assets/audio/fx_land.wav");
	App->audio->LoadFx("assets/audio/fx_attack_miss.wav");
	App->audio->LoadFx("assets/audio/fx_attack_hit.wav");
	App->audio->LoadFx("assets/audio/fx_attack_hit_hard.wav");
	App->audio->LoadFx("assets/audio/fx_voice_axel.wav");
	App->audio->LoadFx("assets/audio/fx_voice_axel_death.wav");
	App->audio->LoadFx("assets/audio/fx_attack_hit_enemy.wav");
	App->audio->LoadFx("assets/audio/fx_voice_garcia.wav");
	App->audio->LoadFx("assets/audio/fx_health_item.wav");
	App->audio->LoadFx("assets/audio/fx_go_arrow.wav");
	App->audio->LoadFx("assets/audio/fx_ground_hit.wav");

}