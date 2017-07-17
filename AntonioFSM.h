#ifndef __ANTONIO_FSM_H__
#define __ANTONIO_FSM_H__

class Antonio;
class AntonioFSM
{

private:
	enum class State
	{
		START,
		IDLE,
		CHASE,
		KICK,
		THROW_BOOMERANG,
		DAMAGED,
		KNOCKED_DOWN,
		GRABBED,
		DEAD
	};

	Antonio *antonio = nullptr;
	State curr_state = State::START;
	State prev_state = State::START;

public:
	AntonioFSM(Antonio *antonio);
	~AntonioFSM();

	void Update();
	void UpdateColliderPosition();


	//-----------------------------  ACTIONS TO PERFORM IN EACH STATE ------------------------------------
	void Idle();
	void Chase();
	void Kick();
	void ThrowBoomerang();
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
