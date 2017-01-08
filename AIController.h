#ifndef __AICONTROLLER_H__
#define __AICONTROLLER_H__

#include "Point.h"

class Enemy;
class Player;
class AIController
{
private:
	
	iPoint m_vector = { 0, 0 };
	bool m_look_each_other = false;
	int m_sign_x = 0;
	int m_sign_y = 0;

public:

	Enemy *m_enemy = nullptr;
	Player *m_player = nullptr;
	bool m_continue = true;
	AIController();
	~AIController();

	void UpdateBehaviour();
};


#endif
