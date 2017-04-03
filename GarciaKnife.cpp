#include "GarciaKnife.h"
#include "JSONDataLoader.h"
#include "Utilities.h"

GarciaKnife::GarciaKnife(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth) : Enemy(texture, curr_anim, name, type, position, depth) {
	
	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaKnifeIdleRight", m_animation_list, m_npc_garcia_knife_idle_right);
	m_npc_garcia_knife_idle_right.loop = false;
	m_npc_garcia_knife_idle_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaKnifeIdleLeft", m_animation_list, m_npc_garcia_knife_idle_left);
	m_npc_garcia_knife_idle_left.loop = false;
	m_npc_garcia_knife_idle_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaKnifeWalkRight", m_animation_list, m_npc_garcia_knife_walk_right);
	m_npc_garcia_knife_walk_right.loop = true;
	m_npc_garcia_knife_walk_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaKnifeWalkLeft", m_animation_list, m_npc_garcia_knife_walk_left);
	m_npc_garcia_knife_walk_left.loop = true;
	m_npc_garcia_knife_walk_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);


	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaKnifeAttackRight", m_animation_list, m_npc_garcia_knife_attack_right);
	m_npc_garcia_knife_attack_right.loop = false;
	m_npc_garcia_knife_attack_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaKnifeAttackLeft", m_animation_list, m_npc_garcia_knife_attack_left);
	m_npc_garcia_knife_attack_left.loop = false;
	m_npc_garcia_knife_attack_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

}

GarciaKnife::GarciaKnife(const GarciaKnife &garcia_knife) : Enemy(garcia_knife)
{
	m_npc_garcia_knife_idle_right = garcia_knife.m_npc_garcia_knife_idle_right;
	m_npc_garcia_knife_idle_left = garcia_knife.m_npc_garcia_knife_idle_left;
	m_npc_garcia_knife_walk_right = garcia_knife.m_npc_garcia_knife_walk_right;
	m_npc_garcia_knife_walk_left  = garcia_knife.m_npc_garcia_knife_walk_left;
	m_npc_garcia_knife_attack_right = garcia_knife.m_npc_garcia_knife_attack_right;
	m_npc_garcia_knife_attack_left = garcia_knife.m_npc_garcia_knife_attack_left;

}

GarciaKnife::~GarciaKnife() {}