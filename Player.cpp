#include "Player.h"
#include "JSONDataLoader.h"
#include "Utilities.h"

Player::Player(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, name, type, position, depth){
	
	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleRight", m_animation_list, m_player_idle_right);
	m_player_idle_right.loop = true;
	m_player_idle_right.speed = 0.01f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleLeft", m_animation_list, m_player_idle_left);
	m_player_idle_left.loop = true;
	m_player_idle_left.speed = 0.01f;
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

}