#include "Enemy.h"
#include "JSONDataLoader.h"
#include "Utilities.h"


Enemy::Enemy(SDL_Texture *texture, 
	Animation *curr_anim, 
	const char *name, 
	entity_type type, 
	iPoint position, 
	int depth) : Entity(texture, curr_anim, name, type, position, depth), m_dead(false), m_life(100){}

Enemy::Enemy(const Enemy &enemy)
{
	m_enemy_grab_collider = enemy.m_enemy_grab_collider;
	m_enemy_hit_collider = enemy.m_enemy_hit_collider;
	m_enemy_ranged_attack_collider = enemy.m_enemy_ranged_attack_collider;
}

