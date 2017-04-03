#include "Punky.h"
#include "Utilities.h"
#include "JSONDataLoader.h"

Punky::Punky(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth) : Enemy(texture, curr_anim, name, type, position, depth)
{
	JSONDataLoader::Load("assets/json/sprites_data.json", "npcPunkyIdleRight", m_animation_list, m_npc_punky_idle_right);
	m_npc_punky_idle_right.loop = false;
	m_npc_punky_idle_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcPunkyIdleLeft", m_animation_list, m_npc_punky_idle_left);
	m_npc_punky_idle_left.loop = false;
	m_npc_punky_idle_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcPunkyWalkRight", m_animation_list, m_npc_punky_walk_right);
	m_npc_punky_walk_right.loop = true;
	m_npc_punky_walk_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcPunkyWalkLeft", m_animation_list, m_npc_punky_walk_left);
	m_npc_punky_walk_left.loop = true;
	m_npc_punky_walk_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcPunkyGroundAttackRight1", m_animation_list, m_npc_punky_ground_attack_right1);
	m_npc_punky_ground_attack_right1.loop = false;
	m_npc_punky_ground_attack_right1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcPunkyGroundAttackRight2", m_animation_list, m_npc_punky_ground_attack_right2);
	m_npc_punky_ground_attack_right2.loop = false;
	m_npc_punky_ground_attack_right2.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcPunkyGroundAttackLeft1", m_animation_list, m_npc_punky_ground_attack_left1);
	m_npc_punky_ground_attack_left1.loop = false;
	m_npc_punky_ground_attack_left1.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcPunkyGroundAttackLeft2", m_animation_list, m_npc_punky_ground_attack_left2);
	m_npc_punky_ground_attack_left2.loop = false;
	m_npc_punky_ground_attack_left2.speed = 0.1f;
	Utilities::free_list(m_animation_list);
}

Punky::Punky(const Punky &punky) : Enemy(punky)
{
	m_npc_punky_idle_right = punky.m_npc_punky_idle_right;
	m_npc_punky_idle_left = punky.m_npc_punky_idle_left;

	m_npc_punky_walk_right = punky.m_npc_punky_walk_right;
	m_npc_punky_walk_left = punky.m_npc_punky_walk_left;

	m_npc_punky_ground_attack_right1 = punky.m_npc_punky_ground_attack_right1;
	m_npc_punky_ground_attack_right2 = punky.m_npc_punky_ground_attack_right2;
	m_npc_punky_ground_attack_left1 = punky.m_npc_punky_ground_attack_left1;
	m_npc_punky_ground_attack_left2 = punky.m_npc_punky_ground_attack_left2;
}

Punky::~Punky() {}