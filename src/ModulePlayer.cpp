#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "Player.h"
#include "PlayerFSM.h"
#include "ModuleSceneRound1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "JSONDataLoader.h"

ModulePlayer::ModulePlayer(bool active) : Module(active) {}

ModulePlayer::~ModulePlayer(){}

bool ModulePlayer::Init()
{
	LoadConfig();
	return true;
}

bool ModulePlayer::Start()
{
	LOG("Loading player spritesheet");
	tx_player = App->textures->Load("assets/spritesheets/axel.png");

	LOG("Creating the player");
	the_player = new Player(tx_player, nullptr, "player", entity_type::PLAYER, {0, 0}, 0); //depth = position.y
	the_player->respawn_position = { -App->renderer->camera.x * App->renderer->camera_speed / SCREEN_SIZE - start_offset_x, -start_offset_y };
	the_player->position = the_player->respawn_position;
	the_player->depth = the_player->position.y;

	LOG("Adding the player colliders to ModuleCollision");
	the_player->body_collider = App->collision->AddCollider(the_player->body_rect, the_player, collider_type::PLAYER_BODY);
	the_player->hit_collider = App->collision->AddCollider(the_player->hit_rect, the_player, collider_type::PLAYER_HIT);
	the_player->body_collider->SetPos(the_player->position.x + the_player->body_collider_offset_right, the_player->position.y);
	the_player->hit_collider->SetPos(the_player->position.x + the_player->hit_collider_offset_right, the_player->position.y);

	App->scene_round1->dynamic_entities.push_back(the_player);

	return true;
}

update_status ModulePlayer::Update()
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

	//god mode
	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
	{
		the_player->god_mode = !the_player->god_mode;
	}

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	for (std::list<Entity*>::iterator it = App->scene_round1->dynamic_entities.begin(); it != App->scene_round1->dynamic_entities.end(); it++)
	{
		RELEASE(*it);
	}
	App->scene_round1->dynamic_entities.clear();
	return true;
}

void ModulePlayer::LoadConfig()
{
	start_offset_x = JSONDataLoader::GetInt("assets/json/config.json", "module_player", "start_offset_x");
	start_offset_y = JSONDataLoader::GetInt("assets/json/config.json", "module_player", "start_offset_y");
}



