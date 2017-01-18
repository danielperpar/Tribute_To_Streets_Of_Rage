#include "Antonio.h"
#include "JSONDataLoader.h"
#include "Utilities.h"

Antonio::Antonio(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Enemy(texture, name, type, position, depth) 
{
	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioBoomerangIdleRight", m_animation_list, m_npc_antonio_boomerang_idle_right);
	m_npc_antonio_boomerang_idle_right.loop = false;
	m_npc_antonio_boomerang_idle_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioIdleRight", m_animation_list, m_npc_antonio_idle_right);
	m_npc_antonio_boomerang_idle_right.loop = false;
	m_npc_antonio_boomerang_idle_right.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioBoomerangIdleLeft", m_animation_list, m_npc_antonio_boomerang_idle_left);
	m_npc_antonio_boomerang_idle_left.loop = false;
	m_npc_antonio_boomerang_idle_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioIdleLeft", m_animation_list, m_npc_antonio_idle_left);
	m_npc_antonio_idle_left.loop = false;
	m_npc_antonio_idle_left.speed = 1.0f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioBoomerangWalkRight", m_animation_list, m_npc_antonio_boomerang_walk_right);
	m_npc_antonio_boomerang_walk_right.loop = true;
	m_npc_antonio_boomerang_walk_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioWalkRight", m_animation_list, m_npc_antonio_walk_right);
	m_npc_antonio_walk_right.loop = true;
	m_npc_antonio_walk_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioBoomerangWalkLeft", m_animation_list, m_npc_antonio_boomerang_walk_left);
	m_npc_antonio_boomerang_walk_left.loop = true;
	m_npc_antonio_boomerang_walk_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioWalkLeft", m_animation_list, m_npc_antonio_walk_left);
	m_npc_antonio_walk_left.loop = true;
	m_npc_antonio_walk_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioKickRight", m_animation_list, m_npc_antonio_kick_right);
	m_npc_antonio_kick_right.loop = false;
	m_npc_antonio_kick_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioKickLeft", m_animation_list, m_npc_antonio_kick_left);
	m_npc_antonio_kick_left.loop = false;
	m_npc_antonio_kick_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioThrowBoomerangRight", m_animation_list, m_npc_antonio_throw_boomerang_right);
	m_npc_antonio_throw_boomerang_right.loop = false;
	m_npc_antonio_throw_boomerang_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioThrowBoomerangLeft", m_animation_list, m_npc_antonio_throw_boomerang_left);
	m_npc_antonio_throw_boomerang_left.loop = false;
	m_npc_antonio_throw_boomerang_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioRecoverBoomerangRight", m_animation_list, m_npc_antonio_recover_boomerang_right);
	m_npc_antonio_recover_boomerang_right.loop = false;
	m_npc_antonio_recover_boomerang_right.speed = 0.1f;
	Utilities::free_list(m_animation_list);

	JSONDataLoader::Load("assets/json/sprites_data.json", "npcAntonioRecoverBoomerangLeft", m_animation_list, m_npc_antonio_recover_boomerang_left);
	m_npc_antonio_recover_boomerang_left.loop = false;
	m_npc_antonio_recover_boomerang_left.speed = 0.1f;
	Utilities::free_list(m_animation_list);
}

Antonio::Antonio(const Antonio &antonio) : Enemy(antonio)
{
	m_carrying_boomerang = antonio.m_carrying_boomerang;
	m_ai_throw_boomerang = antonio.m_ai_throw_boomerang;

	m_boomerang = antonio.m_boomerang;

	m_current_animation = antonio.m_current_animation;

	m_ai_controller = antonio.m_ai_controller;

	m_npc_antonio_boomerang_idle_right = antonio.m_npc_antonio_boomerang_idle_right;
	m_npc_antonio_boomerang_idle_left = antonio.m_npc_antonio_boomerang_idle_left;

	m_npc_antonio_idle_right = antonio.m_npc_antonio_idle_right;
	m_npc_antonio_idle_left = antonio.m_npc_antonio_idle_left;

	m_npc_antonio_boomerang_walk_right = antonio.m_npc_antonio_boomerang_walk_right;
	m_npc_antonio_boomerang_walk_left = antonio.m_npc_antonio_boomerang_walk_left;

	m_npc_antonio_walk_right = antonio.m_npc_antonio_walk_right;
	m_npc_antonio_walk_left = antonio.m_npc_antonio_walk_left;

	m_npc_antonio_kick_right = antonio.m_npc_antonio_kick_right;
	m_npc_antonio_kick_left = antonio.m_npc_antonio_kick_left;

	m_npc_antonio_throw_boomerang_right = antonio.m_npc_antonio_throw_boomerang_left;
	m_npc_antonio_throw_boomerang_left = antonio.m_npc_antonio_throw_boomerang_left;

	m_npc_antonio_recover_boomerang_right = antonio.m_npc_antonio_recover_boomerang_right;
	m_npc_antonio_recover_boomerang_left = antonio.m_npc_antonio_recover_boomerang_left;
}

Antonio::~Antonio() {}