#ifndef __FINITE_STATE_MACHINE_H__
#define __FINITE_STATE_MACHINE__

class Player;
class PlayerFSM{
private:
	enum class State
	{
		START,
		IDLE,
		WALK,
		JUMP,
		SIMPLE_PUNCH,
		CBO_PUNCH,
		CBO_LOW_PUNCH,
		CBO_KICK,
		GRAB,
		LOW_KICK,
		HEAD_HIT,
		AIR_ATTACK,
		FINISHER,
		RELEASE,
		PRE_BACK_PUNCH,
		BACK_PUNCH,
		DAMAGED,
		KNOCKED_DOWN,
	};

	State curr_state = State::START;
	State prev_state = State::START;

	Player *the_player = nullptr;
		
public:
	PlayerFSM(Player *player);
	~PlayerFSM();

	void Update();

	//-----------------------------  ACTIONS TO PERFORM IN EACH STATE ------------------------------------
	void Idle();
	void Walk();
	void Jump();
	void SimplePunch();
	void CboPunch();
	void CboLowPunch();
	void CboKick();
	void Grab();
	void LowKick();
	void HeadHit();
	void AirAttack();
	void Finisher();
	void Release();
	void PreBackPunch();
	void BackPunch();
	void Damaged();
	void KnockedDown();

	State GetCurrState() const;
	void SetCurrState(State state);

};

#endif
