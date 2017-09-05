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
#include "HealthChicken.h"
#include "Application.h"
#include "ModuleSceneRound1.h"
#include "HealthBar.h"
#include "ModuleAudio.h"

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
		LoadConfig();
	}

Player::~Player() {

	RELEASE(player_fsm);
}

void Player::UpdateFSM()
{
	player_fsm->Update();	
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

	if (col_info_other.collider->type == collider_type::HEALTH_CHICKEN && col_info_player.collider->type == collider_type::PLAYER_BODY)
	{
		HealthChicken* chicken = (HealthChicken*)(col_info_other.collider->entity);
		if (chicken->depth >= depth - chicken->depth_margin && chicken->depth <= depth + chicken->depth_margin)
		{
			pickable_chicken = chicken;
			pick_up = true;
		}
	}
	
}


void Player::OnCollisionEnter(const CollisionInfo &col_info_player, const CollisionInfo &col_info_other)
{
	//LOG("Inside player::OnCollisionEnter");

	std::pair<CollisionInfo, CollisionInfo> collision_pair = std::make_pair(col_info_player, col_info_other);
	player_collision_status.push_back(collision_pair);

	if (grabbed_enemy == nullptr && col_info_player.collider->type == collider_type::PLAYER_BODY && col_info_other.collider->type == collider_type::ENEMY_BODY)
	{
		Enemy *enemy = (Enemy*)(col_info_other.collider->entity);
		allow_grab = true;

		if (enemy->life <= 0)
			allow_grab = false;

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
		App->audio->PlayFx(audio_fx::PLAYER_ATTACK_HIT_HARD);
		if (god_mode == false)
		{
			life -= ((Boomerang*)(((Particle*)(col_info_other.collider->entity))))->boomerang_damage;
			App->scene_round1->player_HP->ScaleHPBar(life, max_life);
		}
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

	if (col_info_pair.first.collider->type == PLAYER_BODY && col_info_pair.second.collider->type == HEALTH_CHICKEN)
	{
		pickable_chicken = nullptr;
		pick_up = false;
	}
	
}

void Player::LoadStats()
{
	max_life = JSONDataLoader::GetInt("assets/json/config.json", "player", "max_life");
	life = max_life;
	speed = JSONDataLoader::GetInt("assets/json/config.json", "player", "speed");
	jump_speed = JSONDataLoader::GetInt("assets/json/config.json", "player", "jump_speed");
	max_jump_height = JSONDataLoader::GetInt("assets/json/config.json", "player", "max_jump_height");
}

void Player::LoadColliders()
{
	JSONDataLoader::LoadColliderRect("assets/json/config.json", "player", "body_collider", body_rect);
	JSONDataLoader::LoadColliderRect("assets/json/config.json", "player", "hit_collider", hit_rect);
	body_collider_offset_right = JSONDataLoader::GetInt("assets/json/config.json", "player", "body_collider_offset_right");
	hit_collider_offset_right = JSONDataLoader::GetInt("assets/json/config.json", "player", "hit_collider_offset_right");
	body_collider_offset_left = JSONDataLoader::GetInt("assets/json/config.json", "player", "body_collider_offset_left");
	hit_collider_offset_left = JSONDataLoader::GetInt("assets/json/config.json", "player", "hit_collider_offset_left");
}

void Player::LoadConfig()
{
	ref_x = JSONDataLoader::GetInt("assets/json/config.json", "player", "ref_x");
	combo_max_frames = JSONDataLoader::GetInt("assets/json/config.json", "player", "combo_max_frames");
	max_grab_kick = JSONDataLoader::GetInt("assets/json/config.json", "player", "max_grab_kick");
	down_frames = JSONDataLoader::GetInt("assets/json/config.json", "player", "down_frames");
	down_inflection = JSONDataLoader::GetInt("assets/json/config.json", "player", "down_inflection");
	simple_damage = JSONDataLoader::GetInt("assets/json/config.json", "player", "simple_damage");
	air_finisher_damage = JSONDataLoader::GetInt("assets/json/config.json", "player", "air_finisher_damage");
	dead_max_times = JSONDataLoader::GetInt("assets/json/config.json", "player", "dead_max_times");
	release_grab_offset = JSONDataLoader::GetInt("assets/json/config.json", "player", "release_grab_offset");
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_right_1", offset_right_1);
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_right_2", offset_right_2);
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_right_3", offset_right_3);
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_right_4", offset_right_4);
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_right_5", offset_right_5);
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_right_6", offset_right_6);
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_right_7", offset_right_7);
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_left_1", offset_left_1);
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_left_2", offset_left_2);
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_left_3", offset_left_3);
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_left_4", offset_left_4);
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_left_5", offset_left_5);
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_left_6", offset_left_6);
	JSONDataLoader::GetPoint("assets/json/config.json", "player", "offset_left_7", offset_left_7);
}

void Player::LoadPlayerAnimations()
{
	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerIdleRight1", animation_list, anim_idle_right1);
	anim_idle_right1.loop = false;
	anim_idle_right1.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_idle_1_speed"); //speed = 0.01
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerIdleRight2", animation_list, anim_idle_right2);
	anim_idle_right2.loop = false;
	anim_idle_right2.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_idle_2_speed");//speed = 0.05f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerIdleRight3", animation_list, anim_idle_right3);
	anim_idle_right3.loop = false;
	anim_idle_right3.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_idle_3_speed");//speed = 0.08f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerIdleLeft1", animation_list, anim_idle_left1);
	anim_idle_left1.loop = false;
	anim_idle_left1.speed = anim_idle_right1.speed; //speed = 0.01
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerIdleLeft2", animation_list, anim_idle_left2);
	anim_idle_left2.loop = false;
	anim_idle_left2.speed = anim_idle_right2.speed;//speed = 0.05f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerIdleLeft3", animation_list, anim_idle_left3);
	anim_idle_left3.loop = false;
	anim_idle_left3.speed = anim_idle_right3.speed;//speed = 0.08f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerWalkRight", animation_list, anim_walk_right);
	anim_walk_right.loop = true;
	anim_walk_right.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_walk_speed");//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerWalkLeft", animation_list, anim_walk_left);
	anim_walk_left.loop = true;
	anim_walk_left.speed = anim_walk_right.speed;//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerJumpRight1", animation_list, anim_jump_right1);
	anim_jump_right1.loop = false;
	anim_jump_right1.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_jump_1_speed");//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerJumpRight2", animation_list, anim_jump_right2);
	anim_jump_right2.loop = false;
	anim_jump_right2.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_jump_2_speed");//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerJumpLeft1", animation_list, anim_jump_left1);
	anim_jump_left1.loop = false;
	anim_jump_left1.speed = anim_jump_right1.speed;//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerJumpLeft2", animation_list, anim_jump_left2);
	anim_jump_left2.loop = false;
	anim_jump_left2.speed = anim_jump_right2.speed;//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerAirKickRight", animation_list, anim_air_kick_right);
	anim_air_kick_right.loop = false;
	anim_air_kick_right.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_air_kick_speed");//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerAirKickLeft", animation_list, anim_air_kick_left);
	anim_air_kick_left.loop = false;
	anim_air_kick_left.speed = anim_air_kick_right.speed;//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerPunchComboRight1", animation_list, anim_punch_combo_right1);
	anim_punch_combo_right1.loop = false;
	anim_punch_combo_right1.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_punch_combo_1_speed");//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerPunchComboRight2", animation_list, anim_punch_combo_right2);
	anim_punch_combo_right2.loop = true;
	anim_punch_combo_right2.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_punch_combo_2_speed");//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerPunchComboRight3", animation_list, anim_punch_combo_right3);
	anim_punch_combo_right3.loop = true;
	anim_punch_combo_right3.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_punch_combo_3_speed");//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerPunchComboLeft1", animation_list, anim_punch_combo_left1);
	anim_punch_combo_left1.loop = false;
	anim_punch_combo_left1.speed = anim_punch_combo_right1.speed;//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerPunchComboLeft2", animation_list, anim_punch_combo_left2);
	anim_punch_combo_left2.loop = false;
	anim_punch_combo_left2.speed = anim_punch_combo_right2.speed;//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerPunchComboLeft3", animation_list, anim_punch_combo_left3);
	anim_punch_combo_left3.loop = false;
	anim_punch_combo_left3.speed = anim_punch_combo_right3.speed;//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabRight", animation_list, anim_grab_right);
	anim_grab_right.loop = false;
	anim_grab_right.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_speed");//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabLeft", animation_list, anim_grab_left);
	anim_grab_left.loop = false;
	anim_grab_left.speed = anim_grab_right.speed;//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabKickHeadRight1", animation_list, anim_grab_kick_head_combo_right1);
	anim_grab_kick_head_combo_right1.loop = false;
	anim_grab_kick_head_combo_right1.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_kick_head_1_speed");//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabKickHeadRight2", animation_list, anim_grab_kick_head_combo_right2);
	anim_grab_kick_head_combo_right2.loop = false;
	anim_grab_kick_head_combo_right2.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_kick_head_2_speed");//speed = 0.07f
	Utilities::free_list(animation_list);

	
	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabKickHeadLeft1", animation_list, anim_grab_kick_head_combo_left1);
	anim_grab_kick_head_combo_left1.loop = false;
	anim_grab_kick_head_combo_left1.speed = anim_grab_kick_head_combo_right1.speed;//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabKickHeadLeft2", animation_list, anim_grab_kick_head_combo_left2);
	anim_grab_kick_head_combo_left2.loop = false;
	anim_grab_kick_head_combo_left2.speed = anim_grab_kick_head_combo_right2.speed;//speed = 0.07f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight1", animation_list, anim_grab_air_spin_combo_right1);
	anim_grab_air_spin_combo_right1.loop = false;
	anim_grab_air_spin_combo_right1.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_air_spin_1_speed");//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight2", animation_list, anim_grab_air_spin_combo_right2);
	anim_grab_air_spin_combo_right2.loop = false;
	anim_grab_air_spin_combo_right2.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_air_spin_2_speed");//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight3", animation_list, anim_grab_air_spin_combo_right3);
	anim_grab_air_spin_combo_right3.loop = false;
	anim_grab_air_spin_combo_right3.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_air_spin_3_speed");//speed = 0.15f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight4", animation_list, anim_grab_air_spin_combo_right4);
	anim_grab_air_spin_combo_right4.loop = false;
	anim_grab_air_spin_combo_right4.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_air_spin_4_speed");//speed = 0.15f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight5", animation_list, anim_grab_air_spin_combo_right5);
	anim_grab_air_spin_combo_right5.loop = false;
	anim_grab_air_spin_combo_right5.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_air_spin_5_speed");//speed = 0.15f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight6", animation_list, anim_grab_air_spin_combo_right6);
	anim_grab_air_spin_combo_right6.loop = false;
	anim_grab_air_spin_combo_right6.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_air_spin_6_speed");//speed = 0.15f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinRight7", animation_list, anim_grab_air_spin_combo_right7);
	anim_grab_air_spin_combo_right7.loop = false;
	anim_grab_air_spin_combo_right7.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_air_spin_7_speed");//speed = 0.15f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft1", animation_list, anim_grab_air_spin_combo_left1);
	anim_grab_air_spin_combo_left1.loop = false;
	anim_grab_air_spin_combo_left1.speed = anim_grab_air_spin_combo_right1.speed;//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft2", animation_list, anim_grab_air_spin_combo_left2);
	anim_grab_air_spin_combo_left2.loop = false;
	anim_grab_air_spin_combo_left2.speed = anim_grab_air_spin_combo_right2.speed;//speed = 0.1f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft3", animation_list, anim_grab_air_spin_combo_left3);
	anim_grab_air_spin_combo_left3.loop = false;
	anim_grab_air_spin_combo_left3.speed = anim_grab_air_spin_combo_right3.speed;//speed = 0.15f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft4", animation_list, anim_grab_air_spin_combo_left4);
	anim_grab_air_spin_combo_left4.loop = false;
	anim_grab_air_spin_combo_left4.speed = anim_grab_air_spin_combo_right4.speed;//speed = 0.15f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft5", animation_list, anim_grab_air_spin_combo_left5);
	anim_grab_air_spin_combo_left5.loop = false;
	anim_grab_air_spin_combo_left5.speed = anim_grab_air_spin_combo_right5.speed;//speed = 0.15f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft6", animation_list, anim_grab_air_spin_combo_left6);
	anim_grab_air_spin_combo_left6.loop = false;
	anim_grab_air_spin_combo_left6.speed = anim_grab_air_spin_combo_right6.speed;//speed = 0.15f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinLeft7", animation_list, anim_grab_air_spin_combo_left7);
	anim_grab_air_spin_combo_left7.loop = false;
	anim_grab_air_spin_combo_left7.speed = anim_grab_air_spin_combo_right7.speed;//speed = 0.15f
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherRight1", animation_list, anim_grab_air_spin_combo_finisher_right1);
	anim_grab_air_spin_combo_finisher_right1.loop = false;
	anim_grab_air_spin_combo_finisher_right1.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_air_finisher_1_speed");//speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherRight2", animation_list, anim_grab_air_spin_combo_finisher_right2);
	anim_grab_air_spin_combo_finisher_right2.loop = false;
	anim_grab_air_spin_combo_finisher_right2.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_air_finisher_2_speed");//speed = 0.12f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherRight3", animation_list, anim_grab_air_spin_combo_finisher_right3);
	anim_grab_air_spin_combo_finisher_right3.loop = false;
	anim_grab_air_spin_combo_finisher_right3.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_air_finisher_3_speed");//speed = 0.12f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherRight4", animation_list, anim_grab_air_spin_combo_finisher_right4);
	anim_grab_air_spin_combo_finisher_right4.loop = false;
	anim_grab_air_spin_combo_finisher_right4.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_air_finisher_4_speed");//speed = 0.15f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherRight5", animation_list, anim_grab_air_spin_combo_finisher_right5);
	anim_grab_air_spin_combo_finisher_right5.loop = false;
	anim_grab_air_spin_combo_finisher_right5.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_air_finisher_5_speed");//speed = 0.15f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherRight6", animation_list, anim_grab_air_spin_combo_finisher_right6);
	anim_grab_air_spin_combo_finisher_right6.loop = false;
	anim_grab_air_spin_combo_finisher_right6.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_grab_air_finisher_6_speed");//speed = 0.15f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherLeft1", animation_list, anim_grab_air_spin_combo_finisher_left1);
	anim_grab_air_spin_combo_finisher_left1.loop = false;
	anim_grab_air_spin_combo_finisher_left1.speed = anim_grab_air_spin_combo_finisher_right1.speed;//speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherLeft2", animation_list, anim_grab_air_spin_combo_finisher_left2);
	anim_grab_air_spin_combo_finisher_left2.loop = false;
	anim_grab_air_spin_combo_finisher_left2.speed = anim_grab_air_spin_combo_finisher_right2.speed;//speed = 0.12f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherLeft3", animation_list, anim_grab_air_spin_combo_finisher_left3);
	anim_grab_air_spin_combo_finisher_left3.loop = false;
	anim_grab_air_spin_combo_finisher_left3.speed = anim_grab_air_spin_combo_finisher_right3.speed;//speed = 0.12f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherLeft4", animation_list, anim_grab_air_spin_combo_finisher_left4);
	anim_grab_air_spin_combo_finisher_left4.loop = false;
	anim_grab_air_spin_combo_finisher_left4.speed = anim_grab_air_spin_combo_finisher_right4.speed;//speed = 0.15f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherLeft5", animation_list, anim_grab_air_spin_combo_finisher_left5);
	anim_grab_air_spin_combo_finisher_left5.loop = false;
	anim_grab_air_spin_combo_finisher_left5.speed = anim_grab_air_spin_combo_finisher_right5.speed;//speed = 0.15f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "grabAirSpinFinisherLeft6", animation_list, anim_grab_air_spin_combo_finisher_left6);
	anim_grab_air_spin_combo_finisher_left6.loop = false;
	anim_grab_air_spin_combo_finisher_left6.speed = anim_grab_air_spin_combo_finisher_right6.speed;//speed = 0.15f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "damageReceivedRight", animation_list, anim_damage_received_right);
	anim_damage_received_right.loop = false;
	anim_damage_received_right.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_damage_received_speed");//speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "damageReceivedLeft", animation_list, anim_damage_received_left);
	anim_damage_received_left.loop = false;
	anim_damage_received_left.speed = anim_damage_received_right.speed;//speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "downRight", animation_list, anim_down_right);
	anim_down_right.loop = true;
	anim_down_right.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_down_speed");//speed = 0.2f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "downLeft", animation_list, anim_down_left);
	anim_down_left.loop = true;
	anim_down_left.speed = anim_down_right.speed;//speed = 0.2f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "groundRight1", animation_list, anim_ground_right1);
	anim_ground_right1.loop = false;
	anim_ground_right1.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_ground_1_speed");//speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "groundRight2", animation_list, anim_ground_right2);
	anim_ground_right2.loop = false;
	anim_ground_right2.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_ground_2_speed");//speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "groundLeft1", animation_list, anim_ground_left1);
	anim_ground_left1.loop = false;
	anim_ground_left1.speed = anim_ground_right1.speed;//speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "groundLeft2", animation_list, anim_ground_left2);
	anim_ground_left2.loop = false;
	anim_ground_left2.speed = anim_ground_right2.speed;//speed = 0.05f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "upRight", animation_list, anim_up_right);
	anim_up_right.loop = false;
	anim_up_right.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_up_speed");//speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "upLeft", animation_list, anim_up_left);
	anim_up_left.loop = false;
	anim_up_left.speed = anim_up_right.speed;//speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "deadBlinkEffectRight", animation_list, anim_deadBlink_right);
	anim_deadBlink_right.loop = true;
	anim_deadBlink_right.speed = JSONDataLoader::GetFloat("assets/json/config.json", "player", "anim_dead_blink");//speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "deadBlinkEffectLeft", animation_list, anim_deadBlink_left);
	anim_deadBlink_left.loop = true;
	anim_deadBlink_left.speed = anim_deadBlink_right.speed;//speed = 0.1f;
	Utilities::free_list(animation_list);
}



