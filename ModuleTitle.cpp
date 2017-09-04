#include "ModuleTitle.h"
#include "JSONDataLoader.h"
#include "Utilities.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Globals.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneRound1.h"

ModuleTitle::ModuleTitle(bool active) : Module(active) {}

ModuleTitle::~ModuleTitle() {}

bool ModuleTitle::Init()
{
	LOG("Loading assets for the title");
	LoadSceneAssets();
	
	return true;
}

bool ModuleTitle::Start()
{
	title_screen = new GUI(tx_title_screen, &anim_title_screen, "title_screen", entity_type::GUI, { 0,0 }, 0);
	press_enter = new GUI(tx_title_screen, &anim_press_enter, "press_enter", entity_type::GUI, { 260, 500 }, 0);

	return true;
}

update_status ModuleTitle::Update()
{

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_round1, App->title, 3.0f);
	}


	App->renderer->Blit(title_screen->texture, title_screen->position.x, title_screen->position.y, &title_screen->curr_anim->GetCurrentFrame(), true);
	App->renderer->Blit(press_enter->texture, press_enter->position.x, press_enter->position.y, &press_enter->curr_anim->GetCurrentFrame(), true);

	return UPDATE_CONTINUE;
}

bool ModuleTitle::CleanUp()
{
	RELEASE(title_screen);
	RELEASE(press_enter);

	return true;
}

void ModuleTitle::LoadSceneAssets()
{
	tx_title_screen = App->textures->Load("assets/spritesheets/title_screen.png");

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "titleScreen", animation_list, anim_title_screen);
	anim_title_screen.loop = true;
	anim_title_screen.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "pressEnterToPlay", animation_list, anim_press_enter);
	anim_press_enter.loop = true;
	anim_press_enter.speed = 0.05f;
	Utilities::free_list(animation_list);
}