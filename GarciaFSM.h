#ifndef __GARCIAFSM_H__
#define __GARCIAFSM_H__

class Enemy;
class GarciaFSM
{
private:
	enum class State
	{
		START,
		IDLE,
		CHASE,
		FAST_CHASE,
		ATTACK,
		EVASIVE
	};

	State curr_state = State::START;
	State prev_state = State::START;

	Enemy *garcia = nullptr;

public:
	GarciaFSM(Enemy *enemy);
	~GarciaFSM();
	
	void Update();

	//-----------------------------  ACTIONS TO PERFORM IN EACH STATE ------------------------------------
	void Idle();
	void Chase();
	void FastChase();
	void Attack();
	void Evasive();

	State GetCurrState()  const;
	void SetCurrState(State state);
};


#endif
