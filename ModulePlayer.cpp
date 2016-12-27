#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "EntityManager.h"
#include "Entity.h"


ModulePlayer::ModulePlayer(bool active) : Module(active)
{
	//// idle animation (just the ship)
	//idle.frames.push_back({66, 1, 32, 14});

	//// move upwards
	//up.frames.push_back({100, 1, 32, 14});
	//up.frames.push_back({132, 0, 32, 14});
	//up.loop = false;
	//up.speed = 0.1f;

	//// Move down
	//down.frames.push_back({33, 1, 32, 14});
	//down.frames.push_back({0, 1, 32, 14});
	//down.loop = false;
	//down.speed = 0.1f;
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("rtype/ship.png");
	
	//Debug test
	player = (Player*)EntityManager::CreateEntity(graphics, "axel", entity_type::PLAYER, {771, 100}, 0);
	EntityManager::DestroyEntity(player);
	

	/*SDL_Rect colliderRect = SDL_Rect();
	colliderRect.x = 0;
	colliderRect.y = 0;
	colliderRect.w = 32;
	colliderRect.h = 14;
	playerCollider = App->collision->AddCollider(colliderRect, nullptr, collider_type::PLAYER);
	playerCollider->SetPos(position.x, position.y);*/

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		//position.x -= speed;
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		//position.x += speed;
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		//position.y += speed;
		//if(current_animation != &down)
		//{
		//	down.Reset();
		//	current_animation = &down;
		//}
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		//position.y -= speed;
		//if(current_animation != &up)
		//{
		//	up.Reset();
		//	current_animation = &up;
		//}
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		// TODO 6: Shoot a laser using the particle system

 		//App->particles->AddParticle(*(App->particles->laserParticle), App->player->position.x + 30, App->player->position.y, collider_type::LASER);
		//App->audio->PlayFx(App->particles->fxLaser, 0);
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE)
	{
	}//&& App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE)
		//current_animation = &idle;


	//playerCollider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
	
		//App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
		
	

	return UPDATE_CONTINUE;
}

// TODO 13: Make so is the laser collides, it is removed and create an explosion particle at its position

// TODO 14: Make so if the player collides, it is removed and create few explosions at its positions
// then fade away back to the first screen (use the "destroyed" bool already created 
// You will need to create, update and destroy the collider with the player

void ModulePlayer::OnCollision(Collider* collider1, Collider* collider2)
{
	/*Collider* laserCollider = nullptr;
	Collider* playerCollider = nullptr;
	Collider* wallCollider = nullptr;

	switch (collider1->c_type)
	{
	case collider_type::LASER:
		laserCollider = collider1;
		break;
	case collider_type::PLAYER:
		playerCollider = collider1;
		break;
	case collider_type::WALL:
		wallCollider = collider1;
		break;
	}

	switch (collider2->c_type)
	{
	case collider_type::LASER:
		laserCollider = collider2;
		break;
	case collider_type::PLAYER:
		playerCollider = collider2;
		break;
	case collider_type::WALL:
		wallCollider = collider2;
		break;
	}
	
	if (laserCollider != nullptr)
	{
		laserCollider->particle->to_delete = true;
		laserCollider->to_delete = true;
		App->particles->AddParticle(*(App->particles->explosionParticle), laserCollider->rect.x, laserCollider->rect.y, collider_type::EXPLOSION);
	}

	if (playerCollider != nullptr)
	{
		destroyed = true;
		playerCollider->to_delete = true;
		App->particles->AddParticle(*(App->particles->explosionParticle), playerCollider->rect.x, playerCollider->rect.y, collider_type::EXPLOSION);

		App->fade->FadeToBlack((Module*)App->scene_intro, (Module*)App->scene_space);
	}*/
}
