#include "Enemy.h"
#include "JSONDataLoader.h"
#include "Utilities.h"

Enemy::Enemy(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, name, type, position, depth), m_dead(false), m_life(100) {
	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleRight", m_animation_list, m_player_idle_right);
	m_player_idle_right.loop = false;
	m_player_idle_right.speed = 0.05f;
	Utilities::free_list(m_animation_list);
}