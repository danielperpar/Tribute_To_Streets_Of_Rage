#include "Garcia.h"
#include "JSONDataLoader.h"
#include "Utilities.h"
#include "GarciaFSM.h"
#include "ModuleCollision.h"
#include "Player.h"

Garcia::Garcia(SDL_Texture *texture,
	Animation *curr_anim, 
	const char *name, 
	entity_type type, 
	iPoint position, 
	int depth) : Enemy(texture, curr_anim, name, type, position, depth) 
{
	LoadGarciaAnimations();
	LoadStats();
}

Garcia::Garcia(const Garcia &garcia) : Enemy(garcia)
{
	life = garcia.life;
	speed = garcia.speed;
	speed_vect = garcia.speed_vect;

	garcia_idle_right = garcia.garcia_idle_right;
	garcia_idle_left = garcia.garcia_idle_left;

	garcia_walk_right = garcia.garcia_walk_right;
	garcia_walk_left = garcia.garcia_walk_left;

	garcia_punch_right1 = garcia.garcia_punch_right1;
	garcia_punch_right2 = garcia.garcia_punch_right2;

	garcia_punch_left1 = garcia.garcia_punch_left1;
	garcia_punch_left2 = garcia.garcia_punch_left2;

	garcia_damaged_right = garcia.garcia_damaged_right;
	garcia_damaged_left = garcia.garcia_damaged_left;

	garcia_down_right1 = garcia.garcia_down_right1;
	garcia_down_right2 = garcia.garcia_down_right2;
	garcia_down_left1 = garcia.garcia_down_left1;
	garcia_down_left2 = garcia.garcia_down_left2;

	garcia_up_right = garcia.garcia_up_right;
	garcia_up_left = garcia.garcia_up_left;

	garcia_grabbed_right = garcia.garcia_grabbed_right;
	garcia_grabbed_left = garcia.garcia_grabbed_left;

	garcia_grabbed_finisher_right = garcia.garcia_grabbed_finisher_right;
	garcia_grabbed_finisher_left = garcia.garcia_grabbed_finisher_left;

	garcia_grabbed_finisher_horiz_right = garcia.garcia_grabbed_finisher_horiz_right;
	garcia_grabbed_finisher_horiz_left = garcia.garcia_grabbed_finisher_horiz_left;

	garcia_grabbed_finisher_vert_right = garcia.garcia_grabbed_finisher_vert_right;
	garcia_grabbed_finisher_vert_left = garcia.garcia_grabbed_finisher_vert_left;

	garcia_dead_blink_effect = garcia.garcia_dead_blink_effect;
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

void Garcia::ApplyDamage(int damage)
{
	life -= damage;
}

void Garcia::LoadStats()
{
	life = JSONDataLoader::GetNumber("assets/json/config.json", "garcia", "life");
	speed = JSONDataLoader::GetNumber("assets/json/config.json", "garcia", "speed");
	speed_vect.x = speed;
	speed_vect.y = speed;
}

void Garcia::OnCollision(const CollisionInfo &col_info_garcia, const CollisionInfo &col_info_other)
{
	//LOG("Inside Garcia::OnCollision");

	if (col_info_other.collider->type == collider_type::PLAYER_BODY)
	{		
		OnCollisionEnter(col_info_garcia, col_info_other);
		if (depth == col_info_other.collider->entity->depth && !the_player->jump && !the_player->knocked_down)
		{
			attack = true;
		}
		else
		{
			attack = false;
		}
	}
	
}

void Garcia::OnCollisionEnter(const CollisionInfo &col_info_garcia, const CollisionInfo &col_info_other)
{
	//LOG("Inside Garcia::OnCollisionEnter");
	hit_collider_status = col_info_other;
	
}

void Garcia::OnCollisionExit(const CollisionInfo &col_info_other)
{
	attack = false;
}

void Garcia::LoadGarciaAnimations()
{
	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaIdleRight", animation_list, garcia_idle_right);
	garcia_idle_right.loop = true;
	garcia_idle_right.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaIdleLeft", animation_list, garcia_idle_left);
	garcia_idle_left.loop = true;
	garcia_idle_left.speed = 0.05f;
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

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaDamageReceivedLeft", animation_list, garcia_damaged_left);
	garcia_damaged_left.loop = false;
	garcia_damaged_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaDownRight1", animation_list, garcia_down_right1);
	garcia_down_right1.loop = false;
	garcia_down_right1.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaDownRight2", animation_list, garcia_down_right2);
	garcia_down_right2.loop = false;
	garcia_down_right2.speed = 0.03f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaDownLeft1", animation_list, garcia_down_left1);
	garcia_down_left1.loop = false;
	garcia_down_left1.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaDownLeft2", animation_list, garcia_down_left2);
	garcia_down_left2.loop = false;
	garcia_down_left2.speed = 0.03f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaUpRight", animation_list, garcia_up_right);
	garcia_up_right.loop = false;
	garcia_up_right.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaUpLeft", animation_list, garcia_up_left);
	garcia_up_left.loop = false;
	garcia_up_left.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaGrabbedRight", animation_list, garcia_grabbed_right);
	garcia_grabbed_right.loop = false;
	garcia_grabbed_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaGrabbedLeft", animation_list, garcia_grabbed_left);
	garcia_grabbed_left.loop = false;
	garcia_grabbed_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaGrabbedFinisherRight", animation_list, garcia_grabbed_finisher_right);
	garcia_grabbed_finisher_right.loop = false;
	garcia_grabbed_finisher_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaGrabbedFinisherLeft", animation_list, garcia_grabbed_finisher_left);
	garcia_grabbed_finisher_left.loop = false;
	garcia_grabbed_finisher_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaGrabbedFinisherHorizRight", animation_list, garcia_grabbed_finisher_horiz_right);
	garcia_grabbed_finisher_horiz_right.loop = false;
	garcia_grabbed_finisher_horiz_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaGrabbedFinisherHorizLeft", animation_list, garcia_grabbed_finisher_horiz_left);
	garcia_grabbed_finisher_horiz_left.loop = false;
	garcia_grabbed_finisher_horiz_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaGrabbedFinisherVertRight", animation_list, garcia_grabbed_finisher_vert_right);
	garcia_grabbed_finisher_vert_right.loop = false;
	garcia_grabbed_finisher_vert_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcGarciaGrabbedFinisherVertLeft", animation_list, garcia_grabbed_finisher_vert_left);
	garcia_grabbed_finisher_vert_left.loop = false;
	garcia_grabbed_finisher_vert_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "deadBlinkEffect", animation_list, garcia_dead_blink_effect);
	garcia_dead_blink_effect.loop = false;
	garcia_dead_blink_effect.speed = 0.1f;
	Utilities::free_list(animation_list);

}