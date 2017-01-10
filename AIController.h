#ifndef __AICONTROLLER_H__
#define __AICONTROLLER_H__

#include "Point.h"

class Enemy;
class Player;
class AIController
{
private:
	
	iPoint m_vector_enemy_to_player = { 0, 0 };
	bool m_look_each_other = false;
	int m_sign_x = 0;
	int m_sign_y = 0;
	float m_t_acum = 0.0f;
	float m_speed_y = 0.5;

public:

	Enemy *m_enemy = nullptr;
	Player *m_player = nullptr;
	bool m_continue_attack = true;
	bool m_collision = true;
	AIController();
	~AIController();

	void UpdateBehaviour();
};


#endif
