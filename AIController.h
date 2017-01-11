#ifndef __AICONTROLLER_H__
#define __AICONTROLLER_H__

#include "Point.h"

class Entity;
class Enemy;
class Player;
class Particle;
class AIController
{
private:
	
	iPoint m_vector_enemy_to_player = { 0, 0 };
	iPoint m_vector_boomerang_to_boss = { 0, 0 };
	bool m_look_each_other = false;
	int m_sign_x = 0;
	int m_sign_y = 0;
	float m_t_acum = 0.0f;
	float m_speed_y = 0.5f;
	float m_boomerang_speed_y = 1.0;

	//references for width and height 
	int m_x_ref = 70;
	int m_y_ref = 59;

public:

	Enemy *m_ai_owner_enemy = nullptr;
	Player *m_player = nullptr;
	bool m_continue_attack = true;
	bool m_collision = true;
	AIController();
	AIController(Enemy *owner);
	~AIController();

	void UpdateBehaviour();
	void UpdateBehaviour(Particle *particle, Entity *owner);
};


#endif
