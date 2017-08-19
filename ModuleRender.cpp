#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Player.h"
#include "ModuleSceneRound1.h"

ModuleRender::ModuleRender()
{
	camera.x = -CAMERA_STARTING_POS_X * SCREEN_SIZE;
	camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	//Camera moves forward only when player is beyond the middle of the screen
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if ((App->player->the_player->position.x + App->player->the_player->ref_x) * SCREEN_SIZE + camera.x >= (SCREEN_SIZE * SCREEN_WIDTH) / 2)
		{
			if(allow_camera_movement)
				camera.x -= SCREEN_SIZE * camera_speed;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		left_limit = -camera.x / SCREEN_SIZE;
	}
	
	//Checking scene stop points
	if (-camera.x + SCREEN_WIDTH * SCREEN_SIZE >= App->scene_round1->first_stop_x * SCREEN_SIZE && !App->scene_round1->first_stop_reached)
	{
		allow_camera_movement = false;
		App->scene_round1->first_stop_reached = true;
		right_limit = App->scene_round1->first_stop_x;
	}

	else if (-camera.x + SCREEN_WIDTH * SCREEN_SIZE >= App->scene_round1->second_stop_x * SCREEN_SIZE && !App->scene_round1->second_stop_reached)
	{
		allow_camera_movement = false;
		App->scene_round1->second_stop_reached = true;
		right_limit = App->scene_round1->second_stop_x;
	}

	else if (-camera.x + SCREEN_WIDTH * SCREEN_SIZE >= App->scene_round1->third_stop_x * SCREEN_SIZE && !App->scene_round1->third_stop_reached)
	{
		allow_camera_movement = false;
		App->scene_round1->third_stop_reached = true;
		right_limit = App->scene_round1->third_stop_x;
	}
	else if (-camera.x + SCREEN_WIDTH * SCREEN_SIZE >= App->scene_round1->right_limit * SCREEN_SIZE)
	{
		allow_camera_movement = false;
		right_limit = App->scene_round1->right_limit;
	}

	//Release the camera when the area is free of enemies
	if (App->scene_round1->first_stop_reached && !App->scene_round1->first_area_clear)
	{
		if (App->scene_round1->dynamic_entities.size() == 1)
		{
			App->scene_round1->first_area_clear = true;
			App->scene_round1->show_go = true;
			allow_camera_movement = true;
			right_limit = App->scene_round1->right_limit;//scene right limit
		}
	}

	else if (App->scene_round1->second_stop_reached && !App->scene_round1->second_area_clear)
	{
		if (App->scene_round1->dynamic_entities.size() == 1)
		{
			App->scene_round1->second_area_clear = true;
			App->scene_round1->show_go = true;
			allow_camera_movement = true;
			right_limit = App->scene_round1->right_limit;//scene right limit
		}
	}

	else if (App->scene_round1->third_stop_reached && !App->scene_round1->third_area_clear)
	{
		if (App->scene_round1->dynamic_entities.size() == 1)
		{
			App->scene_round1->third_area_clear = true;
			App->scene_round1->show_go = true;
			allow_camera_movement = true;
			right_limit = App->scene_round1->right_limit;//scene right limit
		}
	}

	//Debug - release camera 
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT)
	{
		allow_camera_movement = true;
		right_limit = App->scene_round1->right_limit;//scene right limit
	}

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, bool followCamera, float speed)
{
	bool ret = true;
	SDL_Rect rect;
	if (!followCamera)
	{
		rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
		rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE;
	}
	else
	{
		rect.x = x;
		rect.y = y;
	}

	if(section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	//debug test
	//LOG("recX = %d", rect.x);

	if(SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * SCREEN_SIZE);
		rec.y = (int)(camera.y + rect.y * SCREEN_SIZE);
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}