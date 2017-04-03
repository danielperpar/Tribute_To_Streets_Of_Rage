#ifndef __FINITE_STATE_MACHINE_H__
#define __FINITE_STATE_MACHINE__

class ModulePlayer;
class PlayerFSM;
class Player;

class PlayerFSM{
private:
	enum class State
	{
		IDLE,
		WALK,
		JUMP,
		AIR_KICK,
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
		KNOCK_DOWN,
	};

	State curr_state = State::IDLE;
	State prev_state = State::IDLE;
	ModulePlayer *module_player = nullptr;
		
public:
	PlayerFSM(ModulePlayer *module_player);
	~PlayerFSM();

	void Update();

	//-----------------------------  ACTIONS TO PERFORM IN EACH STATE ------------------------------------
	void Idle();
	void Walk();
	void Jump();
	void AirKick();
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
	void KnockDown();

	State GetCurrState() const;
	void SetCurrState(State state);

};

#endif
