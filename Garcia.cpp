#include "Garcia.h"
#include "JSONDataLoader.h"
#include "Utilities.h"
#include "GarciaFSM.h"
#include "ModuleCollision.h"

Garcia::Garcia(SDL_Texture *texture, 
	Animation *curr_anim, 
	const char *name, 
	entity_type type, 
	iPoint position, 
	int depth) : Entity(texture, curr_anim, name, type, position, depth) 
{
	LoadGarciaAnimations();
	LoadStats();
	LoadColliders();
	
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

	body_rect.x = garcia.body_rect.x;
	body_rect.y = garcia.body_rect.y;
	body_rect.w = garcia.body_rect.w;
	body_rect.h = garcia.body_rect.h;

	hit_rect.x = garcia.hit_rect.x;
	hit_rect.y = garcia.hit_rect.y;
	hit_rect.w = garcia.hit_rect.w;
	hit_rect.h = garcia.hit_rect.h;

	body_collider_offset_right = garcia.body_collider_offset_right;
	hit_collider_offset_right = garcia.hit_collider_offset_right;
	body_collider_offset_left = garcia.body_collider_offset_left;
	hit_collider_offset_left = garcia.hit_collider_offset_left;
}
Garcia::~Garcia() 
{
	RELEASE(garcia_fsm);
}

void Garcia::UpdateFSM()
{
	garcia_fsm->Update();
}

void Garcia::SetPlayer(Player *player)
{
	the_player = player;
}

void Garcia::LoadStats()
{
	life = JSONDataLoader::GetNumber("assets/json/config.json", "garcia", "life");
	speed = JSONDataLoader::GetNumber("assets/json/config.json", "garcia", "speed");
}

void Garcia::LoadColliders()
{
	JSONDataLoader::LoadColliderRect("assets/json/config.json", "garcia", "bodyCollider", body_rect);
	JSONDataLoader::LoadColliderRect("assets/json/config.json", "garcia", "hitCollider", hit_rect);
	body_collider_offset_right = JSONDataLoader::GetNumber("assets/json/config.json", "garcia", "bodyCollider_Offset_Right");
	hit_collider_offset_right = JSONDataLoader::GetNumber("assets/json/config.json", "garcia", "hitCollider_Offset_Right");
	body_collider_offset_left = JSONDataLoader::GetNumber("assets/json/config.json", "garcia", "bodyCollider_Offset_Left");
	hit_collider_offset_left = JSONDataLoader::GetNumber("assets/json/config.json", "garcia", "hitCollider_Offset_Left");
}

void Garcia::OnCollisionEnter(const CollisionInfo &col_info_garcia, const CollisionInfo &col_info_other)
{

}

void Garcia::OnCollisionExit(const CollisionInfo &col_info_garcia, const CollisionInfo &col_info_other)
{

}

void Garcia::LoadGarciaAnimations()
{
	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaIdleRight", animation_list, garcia_idle_right);
	garcia_idle_right.loop = true;
	garcia_idle_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaIdleLeft", animation_list, garcia_idle_left);
	garcia_idle_left.loop = true;
	garcia_idle_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaWalkRight", animation_list, garcia_walk_right);
	garcia_walk_right.loop = true;
	garcia_walk_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaWalkLeft", animation_list, garcia_walk_left);
	garcia_walk_left.loop = true;
	garcia_walk_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaPunchRight1", animation_list, garcia_punch_right1);
	garcia_punch_right1.loop = false;
	garcia_punch_right1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaPunchRight2", animation_list, garcia_punch_right2);
	garcia_punch_right2.loop = false;
	garcia_punch_right2.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaPunchLeft1", animation_list, garcia_punch_left1);
	garcia_punch_left1.loop = false;
	garcia_punch_left1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaPunchLeft2", animation_list, garcia_punch_left2);
	garcia_punch_left2.loop = false;
	garcia_punch_left2.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaDamageReceivedRight", animation_list, garcia_damaged_right);
	garcia_damaged_right.loop = false;
	garcia_damaged_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaDamageReceivedLeft", animation_list, garcia_damage_left);
	garcia_damage_left.loop = false;
	garcia_damage_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaDownRight", animation_list, garcia_down_right);
	garcia_down_right.loop = false;
	garcia_down_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaDownLeft", animation_list, garcia_down_left);
	garcia_down_left.loop = false;
	garcia_down_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaUpRight", animation_list, garcia_up_right);
	garcia_up_right.loop = false;
	garcia_up_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaUpLeft", animation_list, garcia_up_left);
	garcia_up_left.loop = false;
	garcia_up_left.speed = 0.1f;
	Utilities::free_list(animation_list);
}