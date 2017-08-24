#include "Player.h"
#include "JSONDataLoader.h"
#include "Utilities.h"
#include "PlayerFSM.h"
#include "Garcia.h"
#include "GarciaFSM.h"
#include "Antonio.h"
#include "AntonioFSM.h"
#include "Enemy.h"
#include "ModuleParticles.h"

Player::Player(
	SDL_Texture *texture, 
	Animation *curr_anim, 
	const char *name, 
	entity_type type, 
	iPoint position, 
	int depth) : Entity(texture, curr_anim, name, type, position, depth)
	{
		player_fsm = new PlayerFSM(this);
		LoadPlayerAnimations();
		LoadStats();
		LoadColliders();
		LoadOtherParameters();
	}

Player::~Player() {

	RELEASE(player_fsm);
}

void Player::LoadStats()
{
	life = JSONDataLoader::GetNumber("assets/json/config.json", "player", "life");
	speed = JSONDataLoader::GetNumber("assets/json/config.json", "player", "speed");
	jump_speed = JSONDataLoader::GetNumber("assets/json/config.json", "player", "jump_speed");
}

void Player::UpdateFSM()
{
	player_fsm->Update();	
}

void Player::LoadColliders()
{
	JSONDataLoader::LoadColliderRect("assets/json/config.json", "player", "body_collider", body_rect);
	JSONDataLoader::LoadColliderRect("assets/json/config.json", "player", "hit_collider", hit_rect);
	body_collider_offset_right = JSONDataLoader::GetNumber("assets/json/config.json", "player", "body_collider_offset_right");
	hit_collider_offset_right = JSONDataLoader::GetNumber("assets/json/config.json", "player", "hit_collider_offset_right");
	body_collider_offset_left = JSONDataLoader::GetNumber("assets/json/config.json", "player", "body_collider_offset_left");
	hit_collider_offset_left = JSONDataLoader::GetNumber("assets/json/config.json", "player", "hit_collider_offset_left");
}

void Player::LoadOtherParameters()
{
	release_grab_offset = JSONDataLoader::GetNumber("assets/json/config.json", "player", "release_grab_offset");
}

void Player::OnCollision(const CollisionInfo &col_info_player, const CollisionInfo &col_info_other)
{
	//LOG("Inside Player::OnCollision");
	bool found = false;

	for (std::list<std::pair<CollisionInfo, CollisionInfo>>::iterator it = player_collision_status.begin(); it != player_collision_status.end() && !found; it++)
	{
		if ((*it).first.collider == col_info_player.collider)
		{
			if ((*it).second.collider == col_info_other.collider)
				found = true;
		}
	}

	if (!found)
		OnCollisionEnter(col_info_player, col_info_other);
	
}


void Player::OnCollisionEnter(const CollisionInfo &col_info_player, const CollisionInfo &col_info_other)
{
	//LOG("Inside player::OnCollisionEnter");

	std::pair<CollisionInfo, CollisionInfo> collision_pair = std::make_pair(col_info_player, col_info_other);
	player_collision_status.push_back(collision_pair);

	if (grabbed_enemy == nullptr && col_info_player.collider->type == collider_type::PLAYER_BODY && col_info_other.collider->type == collider_type::ENEMY_BODY)
	{
		Enemy *enemy = ((Enemy*)(col_info_other.collider->entity));
		allow_grab = true;

		//Don't allow grab when enemy is knocked down
		if (enemy->knocked_down)
			allow_grab = false;

		//Check whether looking each other
		if (enemy->facing_right == facing_right)
			allow_grab = false;
		
		//Check player right state to grab
		if (player_fsm->GetCurrState() != PlayerFSM::State::IDLE && player_fsm->GetCurrState() != PlayerFSM::State::WALK)
		{
			allow_grab = false;
		}

		bool right_depth = false;
		if(enemy->depth <= depth && enemy->depth >= depth - enemy->depth_margin)
			right_depth = true;
		
		if (right_depth && allow_grab)
		{
			enemy_to_grab = true;
			if (enemy->type == entity_type::GARCIA)
			{
				grabbed_enemy = enemy;
				enemy->grabbed = true;
				((Garcia*)enemy)->garcia_fsm->grab_stage = GarciaFSM::GrabStage::FIRST_STAGE;
			}
			else if (enemy->type == entity_type::ANTONIO)
			{
				grabbed_enemy = enemy;
				enemy->grabbed = true;
				((Antonio*)enemy)->antonio_fsm->grab_stage = AntonioFSM::GrabStage::FIRST_STAGE;
			}

			if (col_info_player.contact_direction_x == contact_direction::RIGHT)
				right_blocked = true;
			if (col_info_player.contact_direction_x == contact_direction::LEFT)
				left_blocked = true;
			
		}
	}

	if (col_info_player.collider->type == collider_type::PLAYER_BODY && col_info_other.collider->type == collider_type::BOOMERANG)
	{
		knocked_down = true;
		life -= ((Boomerang*)(((Particle*)(col_info_other.collider->entity))))->boomerang_damage;
	}

}

void Player:: OnCollisionExit(const std::pair<CollisionInfo, CollisionInfo> &col_info_pair)
{
	//LOG("Inside Player::OnCollisionExit");
	if(col_info_pair.first.collider->type == PLAYER_BODY && col_info_pair.second.collider->type == ENEMY_BODY)
	{
		if (grabbed_enemy == col_info_pair.second.collider->entity)
		{
			enemy_to_grab = false;			
			((Garcia*)(grabbed_enemy))->grabbed = false;
			grabbed_enemy = nullptr;
			
			if (col_info_pair.first.contact_direction_x == contact_direction::RIGHT)
				right_blocked = false;
			if (col_info_pair.first.contact_direction_x == contact_direction::LEFT)
				left_blocked = false;
			
		}
		
	}
	
}

void Player::LoadPlayerAnimations()
{
	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerIdleRight1", animation_list, anim_idle_right1);
	anim_idle_right1.loop = false;
	anim_idle_right1.speed = 0.01f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerIdleRight2", animation_list, anim_idle_right2);
	anim_idle_right2.loop = false;
	anim_idle_right2.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerIdleRight3", animation_list, anim_idle_right3);
	anim_idle_right3.loop = false;
	anim_idle_right3.speed = 0.08f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerIdleLeft1", animation_list, anim_idle_left1);
	anim_idle_left1.loop = false;
	anim_idle_left1.speed = 0.01f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerIdleLeft2", animation_list, anim_idle_left2);
	anim_idle_left2.loop = false;
	anim_idle_left2.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerIdleLeft3", animation_list, anim_idle_left3);
	anim_idle_left3.loop = false;
	anim_idle_left3.speed = 0.08f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerWalkRight", animation_list, anim_walk_right);
	anim_walk_right.loop = true;
	anim_walk_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerWalkLeft", animation_list, anim_walk_left);
	anim_walk_left.loop = true;
	anim_walk_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerJumpRight1", animation_list, anim_jump_right1);
	anim_jump_right1.loop = false;
	anim_jump_right1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerJumpRight2", animation_list, anim_jump_right2);
	anim_jump_right2.loop = false;
	anim_jump_right2.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerJumpLeft1", animation_list, anim_jump_left1);
	anim_jump_left1.loop = false;
	anim_jump_left1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerJumpLeft2", animation_list, anim_jump_left2);
	anim_jump_left2.loop = false;
	anim_jump_left2.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerAirKickRight", animation_list, anim_air_kick_right);
	anim_air_kick_right.loop = false;
	anim_air_kick_right.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerAirKickLeft", animation_list, anim_air_kick_left);
	anim_air_kick_left.loop = false;
	anim_air_kick_left.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerPunchComboRight1", animation_list, anim_punch_combo_right1);
	anim_punch_combo_right1.loop = false;
	anim_punch_combo_right1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerPunchComboRight2", animation_list, anim_punch_combo_right2);
	anim_punch_combo_right2.loop = true;
	anim_punch_combo_right2.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerPunchComboRight3", animation_list, anim_punch_combo_right3);
	anim_punch_combo_right3.loop = true;
	anim_punch_combo_right3.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerPunchComboLeft1", animation_list, anim_punch_combo_left1);
	anim_punch_combo_left1.loop = false;
	anim_punch_combo_left1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerPunchComboLeft2", animation_list, anim_punch_combo_left2);
	anim_punch_combo_left2.loop = false;
	anim_punch_combo_left2.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerPunchComboLeft3", animation_list, anim_punch_combo_left3);
	anim_punch_combo_left3.loop = false;
	anim_punch_combo_left3.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerBackPunchRight1", animation_list, anim_back_punch_right1);
	anim_back_punch_right1.loop = false;
	anim_back_punch_right1.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerBackPunchRight2", animation_list, anim_back_punch_right2);
	anim_back_punch_right2.loop = false;
	anim_back_punch_right2.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerBackPunchLeft1", animation_list, anim_back_punch_left1);
	anim_back_punch_left1.loop = false;
	anim_back_punch_left1.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerBackPunchLeft2", animation_list, anim_back_punch_left2);
	anim_back_punch_left2.loop = false;
	anim_back_punch_left2.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabRight", animation_list, anim_grab_right);
	anim_grab_right.loop = false;
	anim_grab_right.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabKickHeadRight1", animation_list, anim_grab_kick_head_combo_right1);
	anim_grab_kick_head_combo_right1.loop = false;
	anim_grab_kick_head_combo_right1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabKickHeadRight2", animation_list, anim_grab_kick_head_combo_right2);
	anim_grab_kick_head_combo_right2.loop = false;
	anim_grab_kick_head_combo_right2.speed = 0.07f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabLeft", animation_list, anim_grab_left);
	anim_grab_left.loop = false;
	anim_grab_left.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabKickHeadLeft1", animation_list, anim_grab_kick_head_combo_left1);
	anim_grab_kick_head_combo_left1.loop = false;
	anim_grab_kick_head_combo_left1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabKickHeadLeft2", animation_list, anim_grab_kick_head_combo_left2);
	anim_grab_kick_head_combo_left2.loop = false;
	anim_grab_kick_head_combo_left2.speed = 0.07f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight1", animation_list, anim_grab_air_spin_combo_right1);
	anim_grab_air_spin_combo_right1.loop = false;
	anim_grab_air_spin_combo_right1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight2", animation_list, anim_grab_air_spin_combo_right2);
	anim_grab_air_spin_combo_right2.loop = false;
	anim_grab_air_spin_combo_right2.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight3", animation_list, anim_grab_air_spin_combo_right3);
	anim_grab_air_spin_combo_right3.loop = false;
	anim_grab_air_spin_combo_right3.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight4", animation_list, anim_grab_air_spin_combo_right4);
	anim_grab_air_spin_combo_right4.loop = false;
	anim_grab_air_spin_combo_right4.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight5", animation_list, anim_grab_air_spin_combo_right5);
	anim_grab_air_spin_combo_right5.loop = false;
	anim_grab_air_spin_combo_right5.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight6", animation_list, anim_grab_air_spin_combo_right6);
	anim_grab_air_spin_combo_right6.loop = false;
	anim_grab_air_spin_combo_right6.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight7", animation_list, anim_grab_air_spin_combo_right7);
	anim_grab_air_spin_combo_right7.loop = false;
	anim_grab_air_spin_combo_right7.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft1", animation_list, anim_grab_air_spin_combo_left1);
	anim_grab_air_spin_combo_left1.loop = false;
	anim_grab_air_spin_combo_left1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft2", animation_list, anim_grab_air_spin_combo_left2);
	anim_grab_air_spin_combo_left2.loop = false;
	anim_grab_air_spin_combo_left2.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft3", animation_list, anim_grab_air_spin_combo_left3);
	anim_grab_air_spin_combo_left3.loop = false;
	anim_grab_air_spin_combo_left3.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft4", animation_list, anim_grab_air_spin_combo_left4);
	anim_grab_air_spin_combo_left4.loop = false;
	anim_grab_air_spin_combo_left4.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft5", animation_list, anim_grab_air_spin_combo_left5);
	anim_grab_air_spin_combo_left5.loop = false;
	anim_grab_air_spin_combo_left5.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft6", animation_list, anim_grab_air_spin_combo_left6);
	anim_grab_air_spin_combo_left6.loop = false;
	anim_grab_air_spin_combo_left6.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft7", animation_list, anim_grab_air_spin_combo_left7);
	anim_grab_air_spin_combo_left7.loop = false;
	anim_grab_air_spin_combo_left7.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherRight1", animation_list, anim_grab_air_spin_combo_finisher_right1);
	anim_grab_air_spin_combo_finisher_right1.loop = false;
	anim_grab_air_spin_combo_finisher_right1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherRight2", animation_list, anim_grab_air_spin_combo_finisher_right2);
	anim_grab_air_spin_combo_finisher_right2.loop = false;
	anim_grab_air_spin_combo_finisher_right2.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherRight3", animation_list, anim_grab_air_spin_combo_finisher_right3);
	anim_grab_air_spin_combo_finisher_right3.loop = false;
	anim_grab_air_spin_combo_finisher_right3.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherRight4", animation_list, anim_grab_air_spin_combo_finisher_right4);
	anim_grab_air_spin_combo_finisher_right4.loop = false;
	anim_grab_air_spin_combo_finisher_right4.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherRight5", animation_list, anim_grab_air_spin_combo_finisher_right5);
	anim_grab_air_spin_combo_finisher_right5.loop = false;
	anim_grab_air_spin_combo_finisher_right5.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherRight6", animation_list, anim_grab_air_spin_combo_finisher_right6);
	anim_grab_air_spin_combo_finisher_right6.loop = false;
	anim_grab_air_spin_combo_finisher_right6.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherLeft1", animation_list, anim_grab_air_spin_combo_finisher_left1);
	anim_grab_air_spin_combo_finisher_left1.loop = false;
	anim_grab_air_spin_combo_finisher_left1.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherLeft2", animation_list, anim_grab_air_spin_combo_finisher_left2);
	anim_grab_air_spin_combo_finisher_left2.loop = false;
	anim_grab_air_spin_combo_finisher_left2.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherLeft3", animation_list, anim_grab_air_spin_combo_finisher_left3);
	anim_grab_air_spin_combo_finisher_left3.loop = false;
	anim_grab_air_spin_combo_finisher_left3.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherLeft4", animation_list, anim_grab_air_spin_combo_finisher_left4);
	anim_grab_air_spin_combo_finisher_left4.loop = false;
	anim_grab_air_spin_combo_finisher_left4.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherLeft5", animation_list, anim_grab_air_spin_combo_finisher_left5);
	anim_grab_air_spin_combo_finisher_left5.loop = false;
	anim_grab_air_spin_combo_finisher_left5.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherLeft6", animation_list, anim_grab_air_spin_combo_finisher_left6);
	anim_grab_air_spin_combo_finisher_left6.loop = false;
	anim_grab_air_spin_combo_finisher_left6.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "weaponPipeIdleRight", animation_list, anim_weapon_pipe_idle_right);
	anim_weapon_pipe_idle_right.loop = true;
	anim_weapon_pipe_idle_right.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "weaponPipeIdleLeft", animation_list, anim_weapon_pipe_idle_left);
	anim_weapon_pipe_idle_left.loop = true;
	anim_weapon_pipe_idle_left.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "weaponPipeWalkRight", animation_list, anim_weapon_pipe_walk_right);
	anim_weapon_pipe_walk_right.loop = true;
	anim_weapon_pipe_walk_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "weaponPipeWalkLeft", animation_list, anim_weapon_pipe_walk_left);
	anim_weapon_pipe_walk_left.loop = true;
	anim_weapon_pipe_walk_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "weaponPipeAttackRight", animation_list, anim_weapon_pipe_attack_right);
	anim_weapon_pipe_attack_right.loop = false;
	anim_weapon_pipe_attack_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "weaponPipeAttackLeft", animation_list, anim_weapon_pipe_attack_left);
	anim_weapon_pipe_attack_left.loop = false;
	anim_weapon_pipe_attack_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "weaponKnifeIdleRight", animation_list, anim_weapon_knife_idle_right);
	anim_weapon_knife_idle_right.loop = true;
	anim_weapon_knife_idle_right.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "weaponKnifeIdleLeft", animation_list, anim_weapon_knife_idle_left);
	anim_weapon_knife_idle_left.loop = true;
	anim_weapon_knife_idle_left.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "weaponKnifeWalkRight", animation_list, anim_weapon_knife_walk_right);
	anim_weapon_knife_walk_right.loop = true;
	anim_weapon_knife_walk_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "weaponKnifeWalkLeft", animation_list, anim_weapon_knife_walk_left);
	anim_weapon_knife_walk_left.loop = true;
	anim_weapon_knife_walk_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "weaponKnifeAttackRight", animation_list, anim_weapon_knife_attack_right);
	anim_weapon_knife_attack_right.loop = false;
	anim_weapon_knife_attack_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "weaponKnifeAttackLeft", animation_list, anim_weapon_knife_attack_left);
	anim_weapon_knife_attack_left.loop = false;
	anim_weapon_knife_attack_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "damageReceivedRight", animation_list, anim_damage_received_right);
	anim_damage_received_right.loop = false;
	anim_damage_received_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "damageReceivedLeft", animation_list, anim_damage_received_left);
	anim_damage_received_left.loop = false;
	anim_damage_received_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "downRight", animation_list, anim_down_right);
	anim_down_right.loop = true;
	anim_down_right.speed = 0.2f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "downLeft", animation_list, anim_down_left);
	anim_down_left.loop = true;
	anim_down_left.speed = 0.2f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "groundRight1", animation_list, anim_ground_right1);
	anim_ground_right1.loop = false;
	anim_ground_right1.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "groundRight2", animation_list, anim_ground_right2);
	anim_ground_right2.loop = false;
	anim_ground_right2.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "groundLeft1", animation_list, anim_ground_left1);
	anim_ground_left1.loop = false;
	anim_ground_left1.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "groundLeft2", animation_list, anim_ground_left2);
	anim_ground_left2.loop = false;
	anim_ground_left2.speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "upRight", animation_list, anim_up_right);
	anim_up_right.loop = false;
	anim_up_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "upLeft", animation_list, anim_up_left);
	anim_up_left.loop = false;
	anim_up_left.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "deadBlinkEffectRight", animation_list, anim_deadBlink_right);
	anim_deadBlink_right.loop = true;
	anim_deadBlink_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "deadBlinkEffectLeft", animation_list, anim_deadBlink_left);
	anim_deadBlink_left.loop = true;
	anim_deadBlink_left.speed = 0.1f;
	Utilities::free_list(animation_list);
}



