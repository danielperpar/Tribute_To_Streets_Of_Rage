#include "Player.h"
#include "JSONDataLoader.h"
#include "Utilities.h"


Player::Player(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, name, type, position, depth){
	
	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleRight1", m_animation_list, m_player_idle_right1);
	m_player_idle_right1.loop = false;
	m_player_idle_right1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleRight2", m_animation_list, m_player_idle_right2);
	m_player_idle_right2.loop = false;
	m_player_idle_right2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleRight3", m_animation_list, m_player_idle_right3);
	m_player_idle_right3.loop = false;
	m_player_idle_right3.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleLeft1", m_animation_list, m_player_idle_left1);
	m_player_idle_left1.loop = false;
	m_player_idle_left1.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleLeft2", m_animation_list, m_player_idle_left2);
	m_player_idle_left2.loop = false;
	m_player_idle_left2.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleLeft3", m_animation_list, m_player_idle_left3);
	m_player_idle_left3.loop = false;
	m_player_idle_left3.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerWalkRight", m_animation_list, m_player_walk_right);
	m_player_walk_right.loop = true;
	m_player_walk_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerWalkLeft", m_animation_list, m_player_walk_left);
	m_player_walk_left.loop = true;
	m_player_walk_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerJumpRight1", m_animation_list, m_player_jump_right1);
	m_player_jump_right1.loop = true;
	m_player_jump_right1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerJumpRight2", m_animation_list, m_player_jump_right2);
	m_player_jump_right2.loop = true;
	m_player_jump_right2.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerJumpLeft1", m_animation_list, m_player_jump_left1);
	m_player_jump_left1.loop = true;
	m_player_jump_left1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerJumpLeft2", m_animation_list, m_player_jump_left2);
	m_player_jump_left2.loop = true;
	m_player_jump_left2.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerAirKickRight", m_animation_list, m_player_air_kick_right);
	m_player_air_kick_right.loop = true;
	m_player_air_kick_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerAirKickLeft", m_animation_list, m_player_air_kick_left);
	m_player_air_kick_left.loop = true;
	m_player_air_kick_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboRight1", m_animation_list, m_player_punch_combo_right1);
	m_player_punch_combo_right1.loop = true;
	m_player_punch_combo_right1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboRight2", m_animation_list, m_player_punch_combo_right2);
	m_player_punch_combo_right2.loop = true;
	m_player_punch_combo_right2.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboRight3", m_animation_list, m_player_punch_combo_right3);
	m_player_punch_combo_right3.loop = true;
	m_player_punch_combo_right3.speed = 0.1f;
	Utilities::free_list(m_animation_list);

}

void Player::AdvanceAnimation(Animation *initial_anim_sprite, size_t initial_sprite_duration, Animation *next_anim_sprite, bool restart_animation)
{
	m_timer_count += m_timer_speed;
				
	if (m_timer_count >=  initial_sprite_duration)
	{
		m_current_animation = next_anim_sprite;
		m_refresh_now1 = true;
		m_restart_animation = restart_animation;
		m_timer_count = 0.0f;
	}
}