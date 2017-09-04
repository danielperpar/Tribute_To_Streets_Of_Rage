#include "Antonio.h"
#include "JSONDataLoader.h"
#include "Utilities.h"
#include "ModuleCollision.h"
#include "Player.h"
#include "AntonioFSM.h"
#include "Application.h"
#include "ModuleSceneRound1.h"
#include "HealthBar.h"

Antonio::Antonio(SDL_Texture *texture, 
	Animation *curr_anim, 
	const char *name, 
	entity_type type, 
	iPoint position, 
	int depth) : Enemy(texture, curr_anim, name, type, position, depth) 
{
	LoadAntonioAnimations();
	LoadOffsets();
	LoadDamage();
	LoadConfig();
}

Antonio::Antonio(const Antonio &antonio) : Enemy(antonio)
{	
	kick_damage = antonio.kick_damage;

	antonio_boomerang_idle_right = antonio.antonio_boomerang_idle_right;
	antonio_boomerang_idle_left = antonio.antonio_boomerang_idle_left;

	antonio_idle_right = antonio.antonio_idle_right;
	antonio_idle_left = antonio.antonio_idle_left;

	antonio_boomerang_walk_right = antonio.antonio_boomerang_walk_right;
	antonio_boomerang_walk_left = antonio.antonio_boomerang_walk_left;

	antonio_walk_right = antonio.antonio_walk_right;
	antonio_walk_left = antonio.antonio_walk_left;

	antonio_kick_right = antonio.antonio_kick_right;
	antonio_kick_left = antonio.antonio_kick_left;
	
	antonio_throw_boomerang_right = antonio.antonio_throw_boomerang_right;
	antonio_throw_boomerang_left = antonio.antonio_throw_boomerang_left;
	
	antonio_recover_boomerang_right = antonio.antonio_recover_boomerang_right;
	antonio_recover_boomerang_left = antonio.antonio_recover_boomerang_left;

	antonio_grabbed_right = antonio.antonio_grabbed_right;
	antonio_grabbed_left = antonio.antonio_grabbed_left;

	antonio_grabbed_finisher_right = antonio.antonio_grabbed_finisher_right;
	antonio_grabbed_finisher_left = antonio.antonio_grabbed_finisher_left;

	antonio_grabbed_finisher_vert_right = antonio.antonio_grabbed_finisher_vert_right;
	antonio_grabbed_finisher_vert_left = antonio.antonio_grabbed_finisher_vert_left;

	antonio_grabbed_finisher_horiz_right = antonio.antonio_grabbed_finisher_horiz_right;
	antonio_grabbed_finisher_horiz_left = antonio.antonio_grabbed_finisher_horiz_left;

	antonio_down_right1 = antonio.antonio_down_right1;
	antonio_down_right2 = antonio.antonio_down_right2;
	antonio_down_left1 = antonio.antonio_down_left1;
	antonio_down_left2 = antonio.antonio_down_left2;

	antonio_up_right = antonio.antonio_up_right;
	antonio_up_left = antonio.antonio_up_left;

	antonio_dead_blink_effect = antonio.antonio_dead_blink_effect;	

	antonio_damaged_right = antonio.antonio_damaged_right;
	antonio_damaged_left = antonio.antonio_damaged_left;

	cast_left = antonio.cast_left;
	cast_right = antonio.cast_right;

	spawn_position = antonio.spawn_position;
}

Antonio::~Antonio() 
{
	RELEASE(antonio_fsm);
}

void Antonio::UpdateFSM()
{
	antonio_fsm->Update();
}

void Antonio::SetPlayer(Player *player)
{
	the_player = player;
}

void Antonio::ApplyDamage(int damage)
{
	life -= damage;
	App->scene_round1->boss_HP->ScaleHPBar(life, max_life);
}

void Antonio::LoadOffsets()
{
	ref_y = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "ref_y");
	body_collider_offset_y = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "body_collider_offset_y");
	hit_collider_offset_y = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "hit_collider_offset_y");
}

void Antonio::LoadDamage()
{
	kick_damage = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "kick_damage");
}

void Antonio::LoadConfig()
{
	bouncing_frames = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "bouncing_frames");
	bouncing_inflection = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "bouncing_inflection");
	blink_wait_frames = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "blink_wait_frames");
	blink_max_times = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "blink_max_times");
	down_frames = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "down_frames");
	down_inflection = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "down_inflection");
	body_collider_wide = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "body_collider_wide");
	body_collider_original = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "body_collider_original");
	body_collider_adjusted_x = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "body_collider_adjusted_x");
	JSONDataLoader::GetPoint("assets/json/config.json", "antonio", "offset_right_1", offset_right_1);
	JSONDataLoader::GetPoint("assets/json/config.json", "antonio", "offset_right_2", offset_right_2);
	JSONDataLoader::GetPoint("assets/json/config.json", "antonio", "offset_right_3", offset_right_3);
	JSONDataLoader::GetPoint("assets/json/config.json", "antonio", "offset_right_4", offset_right_4);
	JSONDataLoader::GetPoint("assets/json/config.json", "antonio", "offset_right_5", offset_right_5);
	JSONDataLoader::GetPoint("assets/json/config.json", "antonio", "offset_right_6", offset_right_6);
	JSONDataLoader::GetPoint("assets/json/config.json", "antonio", "offset_right_7", offset_right_7);
	JSONDataLoader::GetPoint("assets/json/config.json", "antonio", "offset_left_1", offset_left_1);
	JSONDataLoader::GetPoint("assets/json/config.json", "antonio", "offset_left_2", offset_left_2);
	JSONDataLoader::GetPoint("assets/json/config.json", "antonio", "offset_left_3", offset_left_3);
	JSONDataLoader::GetPoint("assets/json/config.json", "antonio", "offset_left_4", offset_left_4);
	JSONDataLoader::GetPoint("assets/json/config.json", "antonio", "offset_left_5", offset_left_5);
	JSONDataLoader::GetPoint("assets/json/config.json", "antonio", "offset_left_6", offset_left_6);
	offset_cast_y = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "offset_cast_y");
	offset_cast_x_left = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "offset_cast_x_left");
	offset_cast_x_right = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "offset_cast_x_right");
	boomerang_offset_left_x = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "boomerang_offset_left_x");
	boomerang_offset_left_y = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "boomerang_offset_left_y");
	boomerang_offset_right_x = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "boomerang_offset_right_x");
	boomerang_offset_right_y = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "boomerang_offset_right_y");
	chase_time_out = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "chase_time_out");
	num_frames = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "num_frames");
	prekick_frames = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "prekick_frames");
}

void Antonio::OnCollision(const CollisionInfo &col_info_antonio, const CollisionInfo &col_info_other)
{
	//LOG("Inside Antonio::OnCollision");

	if (col_info_other.collider->type == collider_type::PLAYER_BODY)
	{
		OnCollisionEnter(col_info_antonio, col_info_other);
		int player_depth = col_info_other.collider->entity->depth;
		bool depth_condition = depth >= player_depth - depth_margin && depth < player_depth;
		if (depth_condition && !the_player->jump && !the_player->knocked_down) 
		{
			prekick = true;
		}
		else
		{
			prekick = false;
		}
	}

}

void Antonio::OnCollisionEnter(const CollisionInfo &col_info_antonio, const CollisionInfo &col_info_other)
{
	//LOG("Inside Antonio::OnCollisionEnter");
	hit_collider_status = col_info_other;

}

void Antonio::OnCollisionExit(const CollisionInfo &col_info_other)
{
	prekick = false;
}

void Antonio::LoadAntonioAnimations()
{
	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioBoomerangIdleRight", animation_list, antonio_boomerang_idle_right);
	antonio_boomerang_idle_right.loop = false;
	antonio_boomerang_idle_right.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioIdleRight", animation_list, antonio_idle_right);
	antonio_boomerang_idle_right.loop = false;
	antonio_boomerang_idle_right.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioBoomerangIdleLeft", animation_list, antonio_boomerang_idle_left);
	antonio_boomerang_idle_left.loop = false;
	antonio_boomerang_idle_left.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioIdleLeft", animation_list, antonio_idle_left);
	antonio_idle_left.loop = false;
	antonio_idle_left.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioBoomerangWalkRight", animation_list, antonio_boomerang_walk_right);
	antonio_boomerang_walk_right.loop = true;
	antonio_boomerang_walk_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioWalkRight", animation_list, antonio_walk_right);
	antonio_walk_right.loop = true;
	antonio_walk_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioBoomerangWalkLeft", animation_list, antonio_boomerang_walk_left);
	antonio_boomerang_walk_left.loop = true;
	antonio_boomerang_walk_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioWalkLeft", animation_list, antonio_walk_left);
	antonio_walk_left.loop = true;
	antonio_walk_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioKickRight", animation_list, antonio_kick_right);
	antonio_kick_right.loop = false;
	antonio_kick_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioKickLeft", animation_list, antonio_kick_left);
	antonio_kick_left.loop = false;
	antonio_kick_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioThrowBoomerangRight", animation_list, antonio_throw_boomerang_right);
	antonio_throw_boomerang_right.loop = false;
	antonio_throw_boomerang_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioThrowBoomerangLeft", animation_list, antonio_throw_boomerang_left);
	antonio_throw_boomerang_left.loop = false;
	antonio_throw_boomerang_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioRecoverBoomerangRight", animation_list, antonio_recover_boomerang_right);
	antonio_recover_boomerang_right.loop = false;
	antonio_recover_boomerang_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioRecoverBoomerangLeft", animation_list, antonio_recover_boomerang_left);
	antonio_recover_boomerang_left.loop = false;
	antonio_recover_boomerang_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioGrabbedRight", animation_list, antonio_grabbed_right);
	antonio_grabbed_right.loop = false;
	antonio_grabbed_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioGrabbedLeft", animation_list, antonio_grabbed_left);
	antonio_grabbed_left.loop = false;
	antonio_grabbed_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioGrabbedFinisherRight", animation_list, antonio_grabbed_finisher_right);
	antonio_grabbed_finisher_right.loop = false;
	antonio_grabbed_finisher_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioGrabbedFinisherLeft", animation_list, antonio_grabbed_finisher_left);
	antonio_grabbed_finisher_left.loop = false;
	antonio_grabbed_finisher_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioGrabbedFinisherHorizRight", animation_list, antonio_grabbed_finisher_horiz_right);
	antonio_grabbed_finisher_horiz_right.loop = false;
	antonio_grabbed_finisher_horiz_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioGrabbedFinisherHorizLeft", animation_list, antonio_grabbed_finisher_horiz_left);
	antonio_grabbed_finisher_horiz_left.loop = false;
	antonio_grabbed_finisher_horiz_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioGrabbedFinisherVertRight", animation_list, antonio_grabbed_finisher_vert_right);
	antonio_grabbed_finisher_vert_right.loop = false;
	antonio_grabbed_finisher_vert_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioGrabbedFinisherVertLeft", animation_list, antonio_grabbed_finisher_vert_left);
	antonio_grabbed_finisher_vert_left.loop = false;
	antonio_grabbed_finisher_vert_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioDownRight1", animation_list, antonio_down_right1);
	antonio_down_right1.loop = false;
	antonio_down_right1.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioDownRight2", animation_list, antonio_down_right2);
	antonio_down_right2.loop = false;
	antonio_down_right2.speed = 0.07f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioDownLeft1", animation_list, antonio_down_left1);
	antonio_down_left1.loop = false;
	antonio_down_left1.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioDownLeft2", animation_list, antonio_down_left2);
	antonio_down_left2.loop = false;
	antonio_down_left2.speed = 0.07f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioUpRight", animation_list, antonio_up_right);
	antonio_up_right.loop = false;
	antonio_up_right.speed = 0.07f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioUpLeft", animation_list, antonio_up_left);
	antonio_up_left.loop = false;
	antonio_up_left.speed = 0.07f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "deadBlinkEffect", animation_list, antonio_dead_blink_effect);
	antonio_dead_blink_effect.loop = false;
	antonio_dead_blink_effect.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioDamageReceivedRight", animation_list, antonio_damaged_right);
	antonio_damaged_right.loop = false;
	antonio_damaged_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcAntonioDamageReceivedLeft", animation_list, antonio_damaged_left);
	antonio_damaged_left.loop = false;
	antonio_damaged_left.speed = 0.1f;
	Utilities::free_list(animation_list);
}