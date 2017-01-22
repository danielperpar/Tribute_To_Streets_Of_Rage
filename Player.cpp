#include "Player.h"
#include "JSONDataLoader.h"
#include "Utilities.h"


Player::Player(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, name, type, position, depth){
	
	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleRight1", m_animation_list, m_idle_right1);
	m_idle_right1.loop = false;
	m_idle_right1.speed = 0.01f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleRight2", m_animation_list, m_idle_right2);
	m_idle_right2.loop = false;
	m_idle_right2.speed = 0.05f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleRight3", m_animation_list, m_idle_right3);
	m_idle_right3.loop = false;
	m_idle_right3.speed = 0.08f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleLeft1", m_animation_list, m_idle_left1);
	m_idle_left1.loop = false;
	m_idle_left1.speed = 0.01f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleLeft2", m_animation_list, m_idle_left2);
	m_idle_left2.loop = false;
	m_idle_left2.speed = 0.05f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleLeft3", m_animation_list, m_idle_left3);
	m_idle_left3.loop = false;
	m_idle_left3.speed = 0.08f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerWalkRight", m_animation_list, m_walk_right);
	m_walk_right.loop = true;
	m_walk_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerWalkLeft", m_animation_list, m_walk_left);
	m_walk_left.loop = true;
	m_walk_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerJumpRight1", m_animation_list, m_jump_right1);
	m_jump_right1.loop = false;
	m_jump_right1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerJumpRight2", m_animation_list, m_jump_right2);
	m_jump_right2.loop = false;
	m_jump_right2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerJumpLeft1", m_animation_list, m_jump_left1);
	m_jump_left1.loop = false;
	m_jump_left1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerJumpLeft2", m_animation_list, m_jump_left2);
	m_jump_left2.loop = false;
	m_jump_left2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerAirKickRight", m_animation_list, m_air_kick_right);
	m_air_kick_right.loop = false;
	m_air_kick_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerAirKickLeft", m_animation_list, m_air_kick_left);
	m_air_kick_left.loop = false;
	m_air_kick_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboRight1", m_animation_list, m_punch_combo_right1);
	m_punch_combo_right1.loop = false;
	m_punch_combo_right1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboRight2", m_animation_list, m_punch_combo_right2);
	m_punch_combo_right2.loop = true;
	m_punch_combo_right2.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboRight3", m_animation_list, m_punch_combo_right3);
	m_punch_combo_right3.loop = true;
	m_punch_combo_right3.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboLeft1", m_animation_list, m_punch_combo_left1);
	m_punch_combo_left1.loop = false;
	m_punch_combo_left1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboLeft2", m_animation_list, m_punch_combo_left2);
	m_punch_combo_left2.loop = false;
	m_punch_combo_left2.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboLeft3", m_animation_list, m_punch_combo_left3);
	m_punch_combo_left3.loop = false;
	m_punch_combo_left3.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerBackPunchRight1", m_animation_list, m_back_punch_right1);
	m_back_punch_right1.loop = false;
	m_back_punch_right1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerBackPunchRight2", m_animation_list, m_back_punch_right2);
	m_back_punch_right2.loop = false;
	m_back_punch_right2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerBackPunchLeft1", m_animation_list, m_back_punch_left1);
	m_back_punch_left1.loop = false;
	m_back_punch_left1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerBackPunchLeft2", m_animation_list, m_back_punch_left2);
	m_back_punch_left2.loop = false;
	m_back_punch_left2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabRight", m_animation_list, m_grab_right);
	m_grab_right.loop = false;
	m_grab_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabKickHeadRight1", m_animation_list, m_grab_kick_head_combo_right1);
	m_grab_kick_head_combo_right1.loop = false;
	m_grab_kick_head_combo_right1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabKickHeadRight2", m_animation_list, m_grab_kick_head_combo_right2);
	m_grab_kick_head_combo_right2.loop = false;
	m_grab_kick_head_combo_right2.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabLeft", m_animation_list, m_grab_left);
	m_grab_left.loop = false;
	m_grab_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabKickHeadLeft1", m_animation_list, m_grab_kick_head_combo_left1);
	m_grab_kick_head_combo_left1.loop = false;
	m_grab_kick_head_combo_left1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabKickHeadLeft2", m_animation_list, m_grab_kick_head_combo_left2);
	m_grab_kick_head_combo_left2.loop = false;
	m_grab_kick_head_combo_left2.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight1", m_animation_list, m_grab_air_spin_combo_right1);
	m_grab_air_spin_combo_right1.loop = false;
	m_grab_air_spin_combo_right1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight2", m_animation_list, m_grab_air_spin_combo_right2);
	m_grab_air_spin_combo_right2.loop = false;
	m_grab_air_spin_combo_right2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight3", m_animation_list, m_grab_air_spin_combo_right3);
	m_grab_air_spin_combo_right3.loop = false;
	m_grab_air_spin_combo_right3.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight4", m_animation_list, m_grab_air_spin_combo_right4);
	m_grab_air_spin_combo_right4.loop = false;
	m_grab_air_spin_combo_right4.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight5", m_animation_list, m_grab_air_spin_combo_right5);
	m_grab_air_spin_combo_right5.loop = false;
	m_grab_air_spin_combo_right5.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight6", m_animation_list, m_grab_air_spin_combo_right6);
	m_grab_air_spin_combo_right6.loop = false;
	m_grab_air_spin_combo_right6.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinRight7", m_animation_list, m_grab_air_spin_combo_right7);
	m_grab_air_spin_combo_right7.loop = false;
	m_grab_air_spin_combo_right7.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft1", m_animation_list, m_grab_air_spin_combo_left1);
	m_grab_air_spin_combo_left1.loop = false;
	m_grab_air_spin_combo_left1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft2", m_animation_list, m_grab_air_spin_combo_left2);
	m_grab_air_spin_combo_left2.loop = false;
	m_grab_air_spin_combo_left2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft3", m_animation_list, m_grab_air_spin_combo_left3);
	m_grab_air_spin_combo_left3.loop = false;
	m_grab_air_spin_combo_left3.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft4", m_animation_list, m_grab_air_spin_combo_left4);
	m_grab_air_spin_combo_left4.loop = false;
	m_grab_air_spin_combo_left4.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft5", m_animation_list, m_grab_air_spin_combo_left5);
	m_grab_air_spin_combo_left5.loop = false;
	m_grab_air_spin_combo_left5.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft6", m_animation_list, m_grab_air_spin_combo_left6);
	m_grab_air_spin_combo_left6.loop = false;
	m_grab_air_spin_combo_left6.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinLeft7", m_animation_list, m_grab_air_spin_combo_left7);
	m_grab_air_spin_combo_left7.loop = false;
	m_grab_air_spin_combo_left7.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinFinisherRight1", m_animation_list, m_grab_air_spin_combo_finisher_right1);
	m_grab_air_spin_combo_finisher_right1.loop = false;
	m_grab_air_spin_combo_finisher_right1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinFinisherRight2", m_animation_list, m_grab_air_spin_combo_finisher_right2);
	m_grab_air_spin_combo_finisher_right2.loop = false;
	m_grab_air_spin_combo_finisher_right2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinFinisherRight3", m_animation_list, m_grab_air_spin_combo_finisher_right3);
	m_grab_air_spin_combo_finisher_right3.loop = false;
	m_grab_air_spin_combo_finisher_right3.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinFinisherLeft1", m_animation_list, m_grab_air_spin_combo_finisher_left1);
	m_grab_air_spin_combo_finisher_left1.loop = false;
	m_grab_air_spin_combo_finisher_left1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinFinisherLeft2", m_animation_list, m_grab_air_spin_combo_finisher_left2);
	m_grab_air_spin_combo_finisher_left2.loop = false;
	m_grab_air_spin_combo_finisher_left2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "grabAirSpinFinisherLeft3", m_animation_list, m_grab_air_spin_combo_finisher_left3);
	m_grab_air_spin_combo_finisher_left3.loop = false;
	m_grab_air_spin_combo_finisher_left3.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponPipeIdleRight", m_animation_list, m_weapon_pipe_idle_right);
	m_weapon_pipe_idle_right.loop = true;
	m_weapon_pipe_idle_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponPipeIdleLeft", m_animation_list, m_weapon_pipe_idle_left);
	m_weapon_pipe_idle_left.loop = true;
	m_weapon_pipe_idle_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponPipeWalkRight", m_animation_list, m_weapon_pipe_walk_right);
	m_weapon_pipe_walk_right.loop = true;
	m_weapon_pipe_walk_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponPipeWalkLeft", m_animation_list, m_weapon_pipe_walk_left);
	m_weapon_pipe_walk_left.loop = true;
	m_weapon_pipe_walk_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponPipeAttackRight", m_animation_list, m_weapon_pipe_attack_right);
	m_weapon_pipe_attack_right.loop = false;
	m_weapon_pipe_attack_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponPipeAttackLeft", m_animation_list, m_weapon_pipe_attack_left);
	m_weapon_pipe_attack_left.loop = false;
	m_weapon_pipe_attack_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponKnifeIdleRight", m_animation_list, m_weapon_knife_idle_right);
	m_weapon_knife_idle_right.loop = true;
	m_weapon_knife_idle_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponKnifeIdleLeft", m_animation_list, m_weapon_knife_idle_left);
	m_weapon_knife_idle_left.loop = true;
	m_weapon_knife_idle_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponKnifeWalkRight", m_animation_list, m_weapon_knife_walk_right);
	m_weapon_knife_walk_right.loop = true;
	m_weapon_knife_walk_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponKnifeWalkLeft", m_animation_list, m_weapon_knife_walk_left);
	m_weapon_knife_walk_left.loop = true;
	m_weapon_knife_walk_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponKnifeAttackRight", m_animation_list, m_weapon_knife_attack_right);
	m_weapon_knife_attack_right.loop = false;
	m_weapon_knife_attack_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "weaponKnifeAttackLeft", m_animation_list, m_weapon_knife_attack_left);
	m_weapon_knife_attack_left.loop = false;
	m_weapon_knife_attack_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "damageReceivedRight", m_animation_list, m_damage_received_right);
	m_damage_received_right.loop = false;
	m_damage_received_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "damageReceivedLeft", m_animation_list, m_damage_received_left);
	m_damage_received_left.loop = false;
	m_damage_received_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "downRight", m_animation_list, m_down_right);
	m_down_right.loop = false;
	m_down_right.speed = 0.05f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "downLeft", m_animation_list, m_down_left);
	m_down_left.loop = false;
	m_down_left.speed = 0.05f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "upRight", m_animation_list, m_up_right);
	m_up_right.loop = false;
	m_up_right.speed = 0.05f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "upLeft", m_animation_list, m_up_left);
	m_up_left.loop = false;
	m_up_left.speed = 0.05f;
	Utilities::free_list(m_animation_list);


	
}

