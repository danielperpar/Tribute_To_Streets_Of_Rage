#ifndef __AIRKICK_H__
#define __AIRKICK_H__

#include "State.h"
class PlayerFSM;
class AirKick : public State
{
private:
	PlayerFSM *player_fsm;

public:
	AirKick(PlayerFSM *fsm);
	~AirKick();

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
