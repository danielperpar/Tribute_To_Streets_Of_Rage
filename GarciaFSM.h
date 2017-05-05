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

	enum class EvasiveMovement
	{
		FIRST_STAGE,
		SECOND_STAGE,
		THIRD_STAGE
	};

	State curr_state = State::START;
	State prev_state = State::START;
	EvasiveMovement evasive_movement = EvasiveMovement::FIRST_STAGE;
	int evasive_v_count = 0;
	int evasive_h_count = 0;
	bool evasive_go = true;
	bool evasive_back = false;

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
	void EvasiveFirstStage();
	void EvasiveSecondStage();
	void EvasiveThirdStage();
	State GetCurrState()  const;
	void SetCurrState(State state);
};


#endif
