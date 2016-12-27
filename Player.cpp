#include "Player.h"
#include "JSONDataLoader.h"
#include "Utilities.h"

Player::Player(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, name, type, position, depth), m_dead(false), m_life(100), m_face_right(true), m_speed(1.0f) {
	
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

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerJumpRight", m_animation_list, m_player_jump_right);
	m_player_jump_right.loop = true;
	m_player_jump_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "playerPunchComboRight", m_animation_list, m_player_punch_combo_right);
	m_player_punch_combo_right.loop = true;
	m_player_punch_combo_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

}