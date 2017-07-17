#include "Antonio.h"
#include "JSONDataLoader.h"
#include "Utilities.h"
#include "ModuleCollision.h"
#include "Player.h"
#include "AntonioFSM.h"

Antonio::Antonio(SDL_Texture *texture, 
	Animation *curr_anim, 
	const char *name, 
	entity_type type, 
	iPoint position, 
	int depth) : Enemy(texture, curr_anim, name, type, position, depth) 
{
	LoadAntonioAnimations();
	LoadStats();
}

Antonio::~Antonio() 
{
	RELEASE(antonio_fsm);
}

void Antonio::UpdateFSM()
{
	
}

void Antonio::SetPlayer(Player *player)
{
	the_player = player;
}

void Antonio::ApplyDamage(int damage)
{
	life -= damage;
}

void Antonio::LoadStats()
{
	life = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "life");
	speed = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "speed");
	speed_vect.x = speed;
	speed_vect.y = speed;
}

void Antonio::OnCollision(const CollisionInfo &col_info_antonio, const CollisionInfo &col_info_other)
{
	//LOG("Inside Antonio::OnCollision");

	if (col_info_other.collider->type == collider_type::PLAYER_BODY)
	{
		OnCollisionEnter(col_info_antonio, col_info_other);
		if (depth == col_info_other.collider->entity->depth && the_player->landed && !the_player->knocked_down)
		{
			kick = true;
		}
		else
		{
			kick = false;
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
	kick = false;
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
}