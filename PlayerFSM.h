#ifndef __FINITE_STATE_MACHINE_H__
#define __FINITE_STATE_MACHINE__

class Idle;
class Walk;
class Jump;
class AirKick;
class SimplePunch;
class CboPunch;
class CboLowPunch;
class CboKick;
class Grab;
class LowKick;
class HeadHit;
class AirAttack;
class Finisher;
class Release;
class PreBackPunch;
class BackPunch;
class Damaged;
class KnockDown;
class State;

class PlayerFSM
{
private:
	State *curr_state;
	Idle *idle;
	Walk *walk;
	Jump *jump;
	AirKick *air_kick;
	SimplePunch *simple_punch;
	CboPunch *cbo_punch;
	CboLowPunch *cbo_low_punch;
	CboKick *cbo_kick;
	Grab *grab;
	LowKick *low_kick;
	HeadHit *head_hit;
	AirAttack *air_attack;
	Finisher *finisher;
	Release *release;
	PreBackPunch *pre_back_punch;
	BackPunch *back_punch;
	Damaged *damaged;
	KnockDown *knock_down;

public:
	PlayerFSM();
	~PlayerFSM();

	void AttackPressed();
	void AttackHold();
	void JumpPressed();
	void JumpHold();
	void LeftPressed();
	void LeftHold();
	void RightPressed();
	void RightHold();
	void UpPressed();
	void UpHold();
	void DownPressed();
	void DownHold();

};



#endif
