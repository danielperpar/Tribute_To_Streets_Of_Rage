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


ModuleSceneRound1::ModuleSceneRound1(bool active) : Module(active)
{}

ModuleSceneRound1::~ModuleSceneRound1()
{}

// Load assets
bool ModuleSceneRound1::Start()
{
	LOG("Loading space scene");

	background = App->textures->Load("assets/spritesheets/StreetsOfRage_round1_background_neon_out.png");
	foreground = App->textures->Load("assets/spritesheets/StreetsOfRage_round1_foreground.png");
	shop_neons = App->textures->Load("assets/spritesheets/neones.png");

	JSONDataLoader::Load("assets/json/sprites_data.json", "neonPinEPot", animation_list);
	for (std::list<int*>::iterator it = animation_list.begin(); it != animation_list.end(); it++)
	{
		int x = **it;
		int y = *(*it + 1);
		int w = *(*it + 2);
		int h = *(*it + 3);
		neonPinEPot.frames.push_back({x, y, w, h});
	}
	neonPinEPot.loop = true;
	neonPinEPot.speed = 0.1f;

	//App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();

	App->audio->PlayMusic("rtype/stage1.ogg", 1.0f);

	// TODO 15: create some colliders for the walls
	// solution wall coords: {0, 224, 3930, 16} {1375, 0, 111, 96} {1375, 145, 111, 96}

	SDL_Rect colliderRect = SDL_Rect();
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
	App->collision->AddCollider(colliderRect, nullptr, collider_type::WALL);

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
	App->renderer->Blit(background, 0, 0, NULL);
	App->renderer->Blit(shop_neons, 768, 0, &(neonPinEPot.GetCurrentFrame()));
	App->renderer->Blit(foreground, 0, 0, NULL);

	return UPDATE_CONTINUE;
}