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
#include "Entity.h"
#include "ModuleEnemies.h"
#include "PlayerFSM.h"


ModulePlayer::ModulePlayer(bool active) : Module(active) {}


ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("assets/spritesheets/axel.png");

	//player = (Player*)EntityManager::CreateEntity(graphics, "axel", entity_type::PLAYER, { 800, 150 }, 150);
	
	SDL_Rect collider;
	collider.x = 0;
	collider.y = 0;
	collider.w = 36;
	collider.h = 63;

	m_player_collider = App->collision->AddCollider(collider, player, collider_type::PLAYER);
	m_player_collider->SetPos(player->position.x + player->m_x_ref - collider.w/2, player->depth);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	//EntityManager::DestroyEntity(player);
	player = nullptr;

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	
// ------------------------------------------------  RECEIVE PLAYER INPUT -----------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		walk_left = true;
	}
	
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		walk_right = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		walk_up = true;
	}

	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		walk_down = true;
	}

//----------------------------------------------------------------------------------------------------------

	player_fsm->Update();



	// Draw everything --------------------------------------

	App->renderer->Blit(player->texture, player->position.x, player->position.y, &(player->curr_anim->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}


void ModulePlayer::UpdateColliderPosition()
{
	m_player_collider->SetPos(player->position.x + player->m_x_ref - m_player_collider->m_rect.w / 2, player->depth);
}

bool ModulePlayer::LookingEachOther(Enemy *enemy)
{
	bool ret = false;
	/*int vector_x = enemy->position.x - player->position.x;
	
	if (vector_x > 0 && player->facing_right)
		ret = true;

	if (vector_x < 0 && player->facing_right == false)
		ret = true;*/


	return ret;
}

