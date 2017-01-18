#include "Enemy.h"
#include "JSONDataLoader.h"
#include "Utilities.h"


Enemy::Enemy(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, name, type, position, depth), m_dead(false), m_life(100){}

Enemy::Enemy(const Enemy &enemy)
{
	m_state = enemy.m_state;
	m_face_right = enemy.m_face_right;
	m_speed = enemy.m_speed;
	m_timer_count = enemy.m_timer_count;
	m_timer_speed = enemy.m_timer_speed;
	m_restart_animation = enemy.m_restart_animation;
	m_allow_attack = enemy.m_allow_attack;

	m_floating_attack = enemy.m_floating_attack;

	m_enemy_grab_collider = enemy.m_enemy_grab_collider;
	m_enemy_hit_collider = enemy.m_enemy_hit_collider;
	m_enemy_ranged_attack_collider = enemy.m_enemy_ranged_attack_collider;

	m_counter = enemy.m_counter;

	m_life = enemy.m_life;
	m_dead = enemy.m_dead;

	m_enemy_to_hit = enemy.m_enemy_to_hit;
	m_enemy_to_grab = enemy.m_enemy_to_grab;

	m_ai_walk = enemy.m_ai_walk;
	m_ai_attack = enemy.m_ai_attack;

	m_x_ref = enemy.m_x_ref;
	m_y_ref = enemy.m_y_ref;
}

