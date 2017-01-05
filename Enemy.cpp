#include "Enemy.h"
#include "JSONDataLoader.h"
#include "Utilities.h"

Enemy::Enemy(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, name, type, position, depth), m_dead(false), m_life(100) {
	
	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaIdleRight", m_animation_list, m_npc_garcia_idle_right);
	m_npc_garcia_idle_right.loop = false;
	m_npc_garcia_idle_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaIdleLeft", m_animation_list, m_npc_garcia_idle_left);
	m_npc_garcia_idle_left.loop = false;
	m_npc_garcia_idle_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaWalkRight", m_animation_list, m_npc_garcia_walk_right);
	m_npc_garcia_walk_right.loop = true;
	m_npc_garcia_walk_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaWalkLeft", m_animation_list, m_npc_garcia_walk_left);
	m_npc_garcia_walk_left.loop = true;
	m_npc_garcia_walk_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);






}