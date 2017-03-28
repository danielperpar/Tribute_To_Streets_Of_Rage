#include "Player.h"
#include "JSONDataLoader.h"
#include "Utilities.h"


Player::Player(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, name, type, position, depth){
	
	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleRight1", m_animation_list, idle_right1);
	idle_right1.loop = false;
	idle_right1.speed = 0.01f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleRight2", m_animation_list, idle_right2);
	idle_right2.loop = false;
	idle_right2.speed = 0.05f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleRight3", m_animation_list, idle_right3);
	idle_right3.loop = false;
	idle_right3.speed = 0.08f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleLeft1", m_animation_list, idle_left1);
	idle_left1.loop = false;
	idle_left1.speed = 0.01f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleLeft2", m_animation_list, idle_left2);
	idle_left2.loop = false;
	idle_left2.speed = 0.05f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleLeft3", m_animation_list, idle_left3);
	idle_left3.loop = false;
	idle_left3.speed = 0.08f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerWalkRight", m_animation_list, walk_right);
	walk_right.loop = true;
	walk_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerWalkLeft", m_animation_list, walk_left);
	walk_left.loop = true;
	walk_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerJumpRight1", m_animation_list, jump_right1);
	jump_right1.loop = false;
	jump_right1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerJumpRight2", m_animation_list, jump_right2);
	jump_right2.loop = false;
	jump_right2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerJumpLeft1", m_animation_list, jump_left1);
	jump_left1.loop = false;
	jump_left1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerJumpLeft2", m_animation_list, jump_left2);
	jump_left2.loop = false;
	jump_left2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerAirKickRight", m_animation_list, air_kick_right);
	air_kick_right.loop = false;
	air_kick_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerAirKickLeft", m_animation_list, air_kick_left);
	air_kick_left.loop = false;
	air_kick_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboRight1", m_animation_list, punch_combo_right1);
	punch_combo_right1.loop = false;
	punch_combo_right1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboRight2", m_animation_list, punch_combo_right2);
	punch_combo_right2.loop = true;
	punch_combo_right2.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboRight3", m_animation_list, punch_combo_right3);
	punch_combo_right3.loop = true;
	punch_combo_right3.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboLeft1", m_animation_list, punch_combo_left1);
	punch_combo_left1.loop = false;
	punch_combo_left1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboLeft2", m_animation_list, punch_combo_left2);
	punch_combo_left2.loop = false;
	punch_combo_left2.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboLeft3", m_animation_list, punch_combo_left3);
	punch_combo_left3.loop = false;
	punch_combo_left3.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerBackPunchRight1", m_animation_list, back_punch_right1);
	back_punch_right1.loop = false;
	back_punch_right1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerBackPunchRight2", m_animation_list, back_punch_right2);
	back_punch_right2.loop = false;
	back_punch_right2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerBackPunchLeft1", m_animation_list, back_punch_left1);
	back_punch_left1.loop = false;
	back_punch_left1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerBackPunchLeft2", m_animation_list, back_punch_left2);
	back_punch_left2.loop = false;
	back_punch_left2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabRight", m_animation_list, grab_right);
	grab_right.loop = false;
	grab_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabKickHeadRight1", m_animation_list, grab_kick_head_combo_right1);
	grab_kick_head_combo_right1.loop = false;
	grab_kick_head_combo_right1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabKickHeadRight2", m_animation_list, grab_kick_head_combo_right2);
	grab_kick_head_combo_right2.loop = false;
	grab_kick_head_combo_right2.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabLeft", m_animation_list, grab_left);
	grab_left.loop = false;
	grab_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabKickHeadLeft1", m_animation_list, grab_kick_head_combo_left1);
	grab_kick_head_combo_left1.loop = false;
	grab_kick_head_combo_left1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabKickHeadLeft2", m_animation_list, grab_kick_head_combo_left2);
	grab_kick_head_combo_left2.loop = false;
	grab_kick_head_combo_left2.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight1", m_animation_list, grab_air_spin_combo_right1);
	grab_air_spin_combo_right1.loop = false;
	grab_air_spin_combo_right1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight2", m_animation_list, grab_air_spin_combo_right2);
	grab_air_spin_combo_right2.loop = false;
	grab_air_spin_combo_right2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight3", m_animation_list, grab_air_spin_combo_right3);
	grab_air_spin_combo_right3.loop = false;
	grab_air_spin_combo_right3.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight4", m_animation_list, grab_air_spin_combo_right4);
	grab_air_spin_combo_right4.loop = false;
	grab_air_spin_combo_right4.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight5", m_animation_list, grab_air_spin_combo_right5);
	grab_air_spin_combo_right5.loop = false;
	grab_air_spin_combo_right5.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight6", m_animation_list, grab_air_spin_combo_right6);
	grab_air_spin_combo_right6.loop = false;
	grab_air_spin_combo_right6.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight7", m_animation_list, grab_air_spin_combo_right7);
	grab_air_spin_combo_right7.loop = false;
	grab_air_spin_combo_right7.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft1", m_animation_list, grab_air_spin_combo_left1);
	grab_air_spin_combo_left1.loop = false;
	grab_air_spin_combo_left1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft2", m_animation_list, grab_air_spin_combo_left2);
	grab_air_spin_combo_left2.loop = false;
	grab_air_spin_combo_left2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft3", m_animation_list, grab_air_spin_combo_left3);
	grab_air_spin_combo_left3.loop = false;
	grab_air_spin_combo_left3.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft4", m_animation_list, grab_air_spin_combo_left4);
	grab_air_spin_combo_left4.loop = false;
	grab_air_spin_combo_left4.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft5", m_animation_list, grab_air_spin_combo_left5);
	grab_air_spin_combo_left5.loop = false;
	grab_air_spin_combo_left5.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft6", m_animation_list, grab_air_spin_combo_left6);
	grab_air_spin_combo_left6.loop = false;
	grab_air_spin_combo_left6.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft7", m_animation_list, grab_air_spin_combo_left7);
	grab_air_spin_combo_left7.loop = false;
	grab_air_spin_combo_left7.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinFinisherRight1", m_animation_list, grab_air_spin_combo_finisher_right1);
	grab_air_spin_combo_finisher_right1.loop = false;
	grab_air_spin_combo_finisher_right1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinFinisherRight2", m_animation_list, grab_air_spin_combo_finisher_right2);
	grab_air_spin_combo_finisher_right2.loop = false;
	grab_air_spin_combo_finisher_right2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinFinisherRight3", m_animation_list, grab_air_spin_combo_finisher_right3);
	grab_air_spin_combo_finisher_right3.loop = false;
	grab_air_spin_combo_finisher_right3.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinFinisherLeft1", m_animation_list, grab_air_spin_combo_finisher_left1);
	grab_air_spin_combo_finisher_left1.loop = false;
	grab_air_spin_combo_finisher_left1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinFinisherLeft2", m_animation_list, grab_air_spin_combo_finisher_left2);
	grab_air_spin_combo_finisher_left2.loop = false;
	grab_air_spin_combo_finisher_left2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinFinisherLeft3", m_animation_list, grab_air_spin_combo_finisher_left3);
	grab_air_spin_combo_finisher_left3.loop = false;
	grab_air_spin_combo_finisher_left3.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponPipeIdleRight", m_animation_list, weapon_pipe_idle_right);
	weapon_pipe_idle_right.loop = true;
	weapon_pipe_idle_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponPipeIdleLeft", m_animation_list, weapon_pipe_idle_left);
	weapon_pipe_idle_left.loop = true;
	weapon_pipe_idle_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponPipeWalkRight", m_animation_list, weapon_pipe_walk_right);
	weapon_pipe_walk_right.loop = true;
	weapon_pipe_walk_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponPipeWalkLeft", m_animation_list, weapon_pipe_walk_left);
	weapon_pipe_walk_left.loop = true;
	weapon_pipe_walk_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponPipeAttackRight", m_animation_list, weapon_pipe_attack_right);
	weapon_pipe_attack_right.loop = false;
	weapon_pipe_attack_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponPipeAttackLeft", m_animation_list, weapon_pipe_attack_left);
	weapon_pipe_attack_left.loop = false;
	weapon_pipe_attack_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponKnifeIdleRight", m_animation_list, weapon_knife_idle_right);
	weapon_knife_idle_right.loop = true;
	weapon_knife_idle_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponKnifeIdleLeft", m_animation_list, weapon_knife_idle_left);
	weapon_knife_idle_left.loop = true;
	weapon_knife_idle_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponKnifeWalkRight", m_animation_list, weapon_knife_walk_right);
	weapon_knife_walk_right.loop = true;
	weapon_knife_walk_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponKnifeWalkLeft", m_animation_list, weapon_knife_walk_left);
	weapon_knife_walk_left.loop = true;
	weapon_knife_walk_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponKnifeAttackRight", m_animation_list, weapon_knife_attack_right);
	weapon_knife_attack_right.loop = false;
	weapon_knife_attack_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponKnifeAttackLeft", m_animation_list, weapon_knife_attack_left);
	weapon_knife_attack_left.loop = false;
	weapon_knife_attack_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "damageReceivedRight", m_animation_list, damage_received_right);
	damage_received_right.loop = false;
	damage_received_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "damageReceivedLeft", m_animation_list, damage_received_left);
	damage_received_left.loop = false;
	damage_received_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "downRight", m_animation_list, down_right);
	down_right.loop = false;
	down_right.speed = 0.05f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "downLeft", m_animation_list, down_left);
	down_left.loop = false;
	down_left.speed = 0.05f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "upRight", m_animation_list, up_right);
	up_right.loop = false;
	up_right.speed = 0.05f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "upLeft", m_animation_list, up_left);
	up_left.loop = false;
	up_left.speed = 0.05f;
	Utilities::free_list(m_animation_list);


	
}

