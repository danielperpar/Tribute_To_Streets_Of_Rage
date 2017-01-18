#include "Garcia.h"
#include "JSONDataLoader.h"
#include "Utilities.h"

Garcia::Garcia(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Enemy(texture, name, type, position, depth) {


	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaIdleRight", m_animation_list, m_npc_garcia_idle_right);
	m_npc_garcia_idle_right.loop = false;
	m_npc_garcia_idle_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaIdleLeft", m_animation_list, m_npc_garcia_idle_left);
	m_npc_garcia_idle_left.loop = false;
	m_npc_garcia_idle_left.speed = 0.1f;
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

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaDamageReceivedRight", m_animation_list, m_npc_garcia_damage_received_right);
	m_npc_garcia_damage_received_right.loop = false;
	m_npc_garcia_damage_received_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaDamageReceivedLeft", m_animation_list, m_npc_garcia_damage_received_left);
	m_npc_garcia_damage_received_left.loop = false;
	m_npc_garcia_damage_received_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaDownRight", m_animation_list, m_npc_garcia_down_right);
	m_npc_garcia_down_right.loop = false;
	m_npc_garcia_down_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaDownLeft", m_animation_list, m_npc_garcia_down_left);
	m_npc_garcia_down_left.loop = false;
	m_npc_garcia_down_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaUpRight", m_animation_list, m_npc_garcia_up_right);
	m_npc_garcia_up_right.loop = false;
	m_npc_garcia_up_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcGarciaUpLeft", m_animation_list, m_npc_garcia_up_left);
	m_npc_garcia_up_left.loop = false;
	m_npc_garcia_up_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

}
Garcia::Garcia(const Garcia &garcia) : Enemy(garcia)
{
	m_punch_hits = garcia.m_punch_hits;

	m_ai_controller = garcia.m_ai_controller;

	m_current_animation = garcia.m_current_animation;

	m_npc_garcia_idle_right = garcia.m_npc_garcia_idle_right;
	m_npc_garcia_idle_left = garcia.m_npc_garcia_idle_left;

	m_npc_garcia_walk_right = garcia.m_npc_garcia_walk_right;
	m_npc_garcia_walk_left = garcia.m_npc_garcia_walk_left;

	m_npc_garcia_punch_right1 = garcia.m_npc_garcia_punch_right1;
	m_npc_garcia_punch_right2 = garcia.m_npc_garcia_punch_right2;

	m_npc_garcia_punch_left1 = garcia.m_npc_garcia_punch_left1;
	m_npc_garcia_punch_left2 = garcia.m_npc_garcia_punch_left2;

	m_npc_garcia_damage_received_right = garcia.m_npc_garcia_damage_received_right;
	m_npc_garcia_damage_received_left = garcia.m_npc_garcia_damage_received_left;

	m_npc_garcia_down_right = garcia.m_npc_garcia_down_right;
	m_npc_garcia_down_left = garcia.m_npc_garcia_down_left;

	m_npc_garcia_up_right = garcia.m_npc_garcia_up_right;
	m_npc_garcia_up_left = garcia.m_npc_garcia_up_left;

}
Garcia::~Garcia() {}