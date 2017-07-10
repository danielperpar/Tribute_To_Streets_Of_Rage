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
		KNOCKED_DOWN,
		GRABBED,
		DEAD
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
	bool evasion_upper = false;
	bool evasion_lower = false;

	Garcia *garcia = nullptr;
	
	int num_frames = 60;
	int frames_counter = 0;
	bool punch_wait = false;

public:
	GarciaFSM(Garcia *garcia);
	~GarciaFSM();
	
	void Update();
	void UpdateColliderPosition();
	//-----------------------------  ACTIONS TO PERFORM IN EACH STATE ------------------------------------
	void Idle();
	void Chase();
	void Attack();
	void Evasive();
	void EvasiveFirstStage();
	void EvasiveSecondStage();
	void EvasiveThirdStage();
	void Grabbed();
	void GrabbedFirstStage();
	void GrabbedSecondStage();
	void GrabbedThirdStage();
	void GrabbedFourthStage();
	void GrabbedFifthStage();
	void GrabbedSixthStage();
	void GrabbedSeventhDownStage();
	void Damaged();
	void KnockedDown();
	void Dead();
	State GetCurrState()  const;
	void SetCurrState(State state);

	enum class GrabStage
	{
		FIRST_STAGE,
		SECOND_STAGE,
		THIRD_STAGE,
		FOURTH_STAGE,
		FIFTH_STAGE,
		SIXTH_STAGE,
		SEVENTH_DOWN_STAGE
	};

	GrabStage grab_stage = GrabStage::FIRST_STAGE;
	
};


#endif
