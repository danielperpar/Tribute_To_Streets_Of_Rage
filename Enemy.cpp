#include "Enemy.h"
#include "JSONDataLoader.h"
#include "Utilities.h"

Enemy::Enemy(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, name, type, position, depth), m_dead(false), m_life(100) 
{

	if (!strcmp(name, "garcia"))
	{

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

		JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaPunchRight1", m_animation_list, m_npc_garcia_punch_right1);
		m_npc_garcia_punch_right1.loop = false;
		m_npc_garcia_punch_right1.speed = 0.1f;
		Utilities::free_list(m_animation_list);

		JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaPunchRight2", m_animation_list, m_npc_garcia_punch_right2);
		m_npc_garcia_punch_right2.loop = false;
		m_npc_garcia_punch_right2.speed = 0.1f;
		Utilities::free_list(m_animation_list);

		JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaPunchLeft1", m_animation_list, m_npc_garcia_punch_left1);
		m_npc_garcia_punch_left1.loop = false;
		m_npc_garcia_punch_left1.speed = 0.1f;
		Utilities::free_list(m_animation_list);

		JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaPunchLeft2", m_animation_list, m_npc_garcia_punch_left2);
		m_npc_garcia_punch_left2.loop = false;
		m_npc_garcia_punch_left2.speed = 0.1f;
		Utilities::free_list(m_animation_list);
	}


}

void Enemy::AdvanceAnimation(size_t initial_sprite_duration, Animation *next_anim_sprite, bool restart_animation)
{
	m_timer_count += m_timer_speed;

	if (m_timer_count >= initial_sprite_duration)
	{
		m_current_animation = next_anim_sprite;
		m_restart_animation = restart_animation;
		m_timer_count = 0;
	}
}