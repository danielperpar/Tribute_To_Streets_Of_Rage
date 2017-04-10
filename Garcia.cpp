#include "Garcia.h"
#include "JSONDataLoader.h"
#include "Utilities.h"
#include "GarciaFSM.h"

Garcia::Garcia(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, curr_anim, name, type, position, depth) {


	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaIdleRight", animation_list, garcia_idle_right);
	garcia_idle_right.loop = true;
	garcia_idle_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaIdleLeft", animation_list, garcia_idle_left);
	garcia_idle_left.loop = true;
	garcia_idle_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaWalkRight", animation_list, garcia_walk_right);
	garcia_walk_right.loop = true;
	garcia_walk_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaWalkLeft", animation_list, garcia_walk_left);
	garcia_walk_left.loop = true;
	garcia_walk_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaPunchRight1", animation_list, garcia_punch_right1);
	garcia_punch_right1.loop = false;
	garcia_punch_right1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaPunchRight2", animation_list, garcia_punch_right2);
	garcia_punch_right2.loop = false;
	garcia_punch_right2.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaPunchLeft1", animation_list, garcia_punch_left1);
	garcia_punch_left1.loop = false;
	garcia_punch_left1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaPunchLeft2", animation_list, garcia_punch_left2);
	garcia_punch_left2.loop = false;
	garcia_punch_left2.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaDamageReceivedRight", animation_list, garcia_damaged_right);
	garcia_damaged_right.loop = false;
	garcia_damaged_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaDamageReceivedLeft", animation_list, garcia_damage_left);
	garcia_damage_left.loop = false;
	garcia_damage_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaDownRight", animation_list, garcia_down_right);
	garcia_down_right.loop = false;
	garcia_down_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaDownLeft", animation_list, garcia_down_left);
	garcia_down_left.loop = false;
	garcia_down_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaUpRight", animation_list, garcia_up_right);
	garcia_up_right.loop = false;
	garcia_up_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaUpLeft", animation_list, garcia_up_left);
	garcia_up_left.loop = false;
	garcia_up_left.speed = 0.1f;
	Utilities::free_list(animation_list);

}

Garcia::Garcia(const Garcia &garcia) : Entity(garcia.texture, garcia.curr_anim, garcia.name, garcia.type, garcia.position, garcia.depth)
{
	
	garcia_idle_right = garcia.garcia_idle_right;
	garcia_idle_left = garcia.garcia_idle_left;

	garcia_walk_right = garcia.garcia_walk_right;
	garcia_walk_left = garcia.garcia_walk_left;

	garcia_punch_right1 = garcia.garcia_punch_right1;
	garcia_punch_right2 = garcia.garcia_punch_right2;

	garcia_punch_left1 = garcia.garcia_punch_left1;
	garcia_punch_left2 = garcia.garcia_punch_left2;

	garcia_damaged_right = garcia.garcia_damaged_right;
	garcia_damage_left = garcia.garcia_damage_left;

	garcia_down_right = garcia.garcia_down_right;
	garcia_down_left = garcia.garcia_down_left;

	garcia_up_right = garcia.garcia_up_right;
	garcia_up_left = garcia.garcia_up_left;
}
Garcia::~Garcia() 
{
	RELEASE(garcia_fsm);
}

void Garcia::UpdateFSM()
{
	garcia_fsm->Update();
}