#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Animation.h"
#include <list>
#include "Entity.h"
#include "Point.h"

enum class enemy_state
{
	IDLE,
	WALKING,
	PUNCH1,
	PUNCH2,
	KNIFE_ATTACK,
	GROUND_ATTACK,
	WHIP_ATTACK,
	KICK,
	THROW_BOOMERANG,
	RECOVER_BOOMERANG,
	DAMAGED,
	DAMAGED_FLOATING,
	UP,
	DEAD
	
};


class Particle;
struct Collider;
struct SDL_Texture;
class Animation;
class Enemy : public Entity {

public:
	Enemy(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	Enemy(const Enemy &enemy);

public:
	
	enemy_state m_state;
	bool m_face_right = true;
	float m_speed = 1.0f;
	size_t m_timer_count = 0;
	size_t m_timer_speed = 0;
	bool m_restart_animation = true;
	bool m_allow_attack = true;
	bool m_floating_attack = false;

	Animation *m_current_animation = nullptr;

	Collider *m_enemy_grab_collider = nullptr;
	Collider *m_enemy_hit_collider = nullptr;
	Collider *m_enemy_ranged_attack_collider = nullptr;

	//counter to allow next attack
	size_t m_counter = 0;

	//updated by the colision module
	int m_life = 100;
	bool m_dead = false;
	
	bool m_enemy_to_hit = false;
	bool m_enemy_to_grab = false;

	//AI signals
	bool m_ai_walk = true;
	bool m_ai_attack = false;

	//AIController m_ai_controller;
	
	//Axis X origin taken from the upper left vertex related to the rectangle containing the enemy sprite to the enemy's back neck position
	size_t m_x_ref = 70;

	//Axis Y height diference between player and boss
	size_t m_y_ref = 51;



private:
	std::list<int*> m_animation_list;

};

#endif // !__ENEMY_H__


