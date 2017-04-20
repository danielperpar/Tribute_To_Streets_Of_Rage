#ifndef __GARCIAFSM_H__
#define __GARCIAFSM_H__

class Garcia;
class GarciaFSM
{
private:
	enum class State
	{
		START,
		IDLE,
		CHASE,		
		ATTACK,
		EVASIVE,
		DAMAGED,
		KNOCKED_DOWN
	};

	State curr_state = State::START;
	State prev_state = State::START;

	Garcia *garcia = nullptr;
	void UpdateColliderPosition();

public:
	GarciaFSM(Garcia *garcia);
	~GarciaFSM();
	
	void Update();

	//-----------------------------  ACTIONS TO PERFORM IN EACH STATE ------------------------------------
	void Idle();
	void Chase();
	void Attack();
	void Evasive();

	State GetCurrState()  const;
	void SetCurrState(State state);
};


#endif
