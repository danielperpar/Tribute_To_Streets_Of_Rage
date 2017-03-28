#ifndef __AIRATTACK_H__
#define __AIRATTACK_H__

#include "State.h"
class PlayerFSM;
class AirAttack : public State
{
private:

	PlayerFSM *player_fsm;

public:
	AirAttack(PlayerFSM *fsm);
	~AirAttack();

	virtual void AttackPressed();
	virtual void AttackHold();
	virtual void JumpPressed();
	virtual void JumpHold();
	virtual void LeftPressed();
	virtual void LeftHold();
	virtual void RightPressed();
	virtual void RightHold();
	virtual void UpPressed();
	virtual void UpHold();
	virtual void DownPressed();
	virtual void DownHold();
};

#endif
