#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSceneRound1.h"
#include "JSONDataLoader.h"
#include "Utilities.h"


ModuleSceneRound1::ModuleSceneRound1(bool active) : Module(active)
{}

ModuleSceneRound1::~ModuleSceneRound1()
{}

// Load assets
bool ModuleSceneRound1::Start()
{
	LOG("Loading round 1 scene");

	background = App->textures->Load("assets/spritesheets/StreetsOfRage_round1_background_neon_out.png");
	foreground = App->textures->Load("assets/spritesheets/StreetsOfRage_round1_foreground.png");
	shop_neons = App->textures->Load("assets/spritesheets/neones.png");
	gui = App->textures->Load("assets/spritesheets/gui.png");

	JSONDataLoader::Load("assets/json/sprites_data.json", "neonPinEPot", animation_list, neonPinEPot);
	neonPinEPot.loop = true;
	neonPinEPot.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "neonBreakfastDiner", animation_list, neonBreakfastDiner);
	neonBreakfastDiner.loop = true;
	neonBreakfastDiner.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "neonLDevo", animation_list, neonLDevo);
	neonLDevo.loop = true;
	neonLDevo.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "neonRachShop", animation_list, neonRachShop);
	neonRachShop.loop = true;
	neonRachShop.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "neonAbcShop", animation_list, neonAbcShop);
	neonAbcShop.loop = true;
	neonAbcShop.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "neonCafeRestaurant", animation_list, neonCafeRestaurant);
	neonCafeRestaurant.loop = true;
	neonCafeRestaurant.speed = 0.05f;
	Utilities::free_list(animation_list);

	//App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();

	App->audio->PlayMusic("assets/audio/03_-_Fighting_in_the_Street_stage_1_.ogg", 1.0f);

	// TODO 15: create some colliders for the walls
	// solution wall coords: {0, 224, 3930, 16} {1375, 0, 111, 96} {1375, 145, 111, 96}

	/*SDL_Rect colliderRect = SDL_Rect();
	colliderRect.x = 0;
	colliderRect.y = 224;
	colliderRect.w = 3930;
	colliderRect.h = 16;
	App->collision->AddCollider(colliderRect, nullptr, collider_type::WALL);

	colliderRect.x = 1375;
	colliderRect.y = 0;
	colliderRect.w = 111;
	colliderRect.h = 96;
	App->collision->AddCollider(colliderRect, nullptr, collider_type::WALL);

	colliderRect.x = 1375;
	colliderRect.y = 145;
	colliderRect.w = 111;
	colliderRect.h = 96;
	App->collision->AddCollider(colliderRect, nullptr, collider_type::WALL);*/

	return true;
}

// UnLoad assets
bool ModuleSceneRound1::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();
	App->collision->Disable();
	App->particles->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneRound1::Update()
{
	// Move camera forward -----------------------------
	//int scroll_speed = 1;

	//App->player->position.x += 1;
	//App->renderer->camera.x -= 3;

	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 32, NULL);

	App->renderer->Blit(shop_neons, 768, 32, &(neonPinEPot.GetCurrentFrame()));
	App->renderer->Blit(shop_neons, 3605, 32, &(neonPinEPot.GetCurrentFrame()));

	App->renderer->Blit(shop_neons, 1028, 31, &(neonBreakfastDiner.GetCurrentFrame()));
	App->renderer->Blit(shop_neons, 1604, 31, &(neonBreakfastDiner.GetCurrentFrame()));
	
	App->renderer->Blit(shop_neons, 1338, 32, &(neonLDevo.GetCurrentFrame()));
	App->renderer->Blit(shop_neons, 1850, 32, &(neonLDevo.GetCurrentFrame()));
	
	App->renderer->Blit(shop_neons, 0, 32, &(neonRachShop.GetCurrentFrame()));
	App->renderer->Blit(shop_neons, 2053, 32, &(neonRachShop.GetCurrentFrame()));
	
	App->renderer->Blit(shop_neons, 567, 32, &(neonAbcShop.GetCurrentFrame()));
	App->renderer->Blit(shop_neons, 2875, 32, &(neonAbcShop.GetCurrentFrame()));

	App->renderer->Blit(shop_neons, 132, 96, &(neonCafeRestaurant.GetCurrentFrame()));
	App->renderer->Blit(shop_neons, 1864, 96, &(neonCafeRestaurant.GetCurrentFrame()));
	App->renderer->Blit(shop_neons, 2440, 96, &(neonCafeRestaurant.GetCurrentFrame()));
	App->renderer->Blit(shop_neons, 3128, 48, &(neonCafeRestaurant.GetCurrentFrame()));
	App->renderer->Blit(shop_neons, 3224, 48, &(neonCafeRestaurant.GetCurrentFrame()));

	App->renderer->Blit(foreground, 0, 32, NULL);
	App->renderer->Blit(gui, 0, 0, NULL, 0.0f);

	return UPDATE_CONTINUE;
}