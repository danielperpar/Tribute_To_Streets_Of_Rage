#include "Nora.h"
#include "JSONDataLoader.h"
#include "Utilities.h"

Nora::Nora(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth) : Enemy(texture, curr_anim, name, type, position, depth) 
{
	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcNoraIdleRight", m_animation_list, m_npc_nora_idle_right);
	m_npc_nora_idle_right.loop = false;
	m_npc_nora_idle_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcNoraIdleLeft", m_animation_list, m_npc_nora_idle_left);
	m_npc_nora_idle_left.loop = false;
	m_npc_nora_idle_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcNoraWalkRight", m_animation_list, m_npc_nora_walk_right);
	m_npc_nora_walk_right.loop = true;
	m_npc_nora_walk_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcNoraWalkLeft", m_animation_list, m_npc_nora_walk_left);
	m_npc_nora_walk_left.loop = true;
	m_npc_nora_walk_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcNoraAttackRight1", m_animation_list, m_npc_nora_attack_right1);
	m_npc_nora_attack_right1.loop = false;
	m_npc_nora_attack_right1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcNoraAttackRight2", m_animation_list, m_npc_nora_attack_right2);
	m_npc_nora_attack_right2.loop = false;
	m_npc_nora_attack_right2.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcNoraAttackLeft1", m_animation_list, m_npc_nora_attack_left1);
	m_npc_nora_attack_left1.loop = false;
	m_npc_nora_attack_left1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcNoraAttackLeft2", m_animation_list, m_npc_nora_attack_left2);
	m_npc_nora_attack_left2.loop = false;
	m_npc_nora_attack_left2.speed = 0.1f;
	Utilities::free_list(m_animation_list);
}

Nora::Nora(const Nora &nora) : Enemy(nora)
{
	m_npc_nora_idle_right = nora.m_npc_nora_idle_right;
	m_npc_nora_idle_left = nora.m_npc_nora_idle_left;

	m_npc_nora_walk_right = nora.m_npc_nora_walk_right;
	m_npc_nora_walk_left = nora.m_npc_nora_walk_left;

	m_npc_nora_attack_right1 = nora.m_npc_nora_attack_right1;
	m_npc_nora_attack_right2 = nora.m_npc_nora_attack_right2;
	m_npc_nora_attack_left1 = nora.m_npc_nora_attack_left1;
	m_npc_nora_attack_left2 = nora.m_npc_nora_attack_left2;
}

Nora::~Nora() {}