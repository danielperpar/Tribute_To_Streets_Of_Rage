#ifndef __FINITE_STATE_MACHINE_H__
#define __FINITE_STATE_MACHINE__

class Player;
class PlayerFSM{

public:
	enum class State
	{
		START,
		IDLE,
		WALK,
		JUMP,
		CBO_PUNCH,
		GRAB,
		LOW_KICK,
		HEAD_HIT,
		AIR_ATTACK,
		POST_AIR_ATTACK,
		AIR_ATTACK_REVERSE,
		FINISHER,
		RELEASE,
		PRE_BACK_PUNCH,
		BACK_PUNCH,
		DAMAGED,
		KNOCKED_DOWN,
		DEAD
	};

	enum class CboPunchStage
	{
		HIGH_PUNCH,
		LOW_PUNCH,
		HIGH_KICK
	};

private:

	State curr_state = State::START;
	State prev_state = State::START;

	CboPunchStage cbo_punch_stage = CboPunchStage::HIGH_PUNCH;

	Player *the_player = nullptr;
	void UpdateColliderPosition();
		
public:
	PlayerFSM(Player *player);
	~PlayerFSM();

	void Update();

	//-----------------------------  ACTIONS TO PERFORM IN EACH STATE ------------------------------------
	void Start();
	void Idle();
	void Walk();
	void Jump();
	void Punch();
	void CboHighPunch();
	void CboLowPunch();
	void CboKick();
	void Grab();
	void LowKick();
	void HeadHit();
	void AirAttack();
	void AirAttackReverse();
	void Finisher();
	void Release();
	void PreBackPunch();
	void BackPunch();
	void Damaged();
	void KnockedDown();
	void Dead();

	State GetCurrState() const;
	void SetCurrState(State state);

	

};

#endif
