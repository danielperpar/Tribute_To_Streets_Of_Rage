#ifndef __WALK_H__
#define __WALK_H__

#include "State.h"

class PlayerFSM;
class Walk : public State
{
private:
	PlayerFSM *player_fsm;

public:
	Walk(PlayerFSM *fsm);
	~Walk();

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
	virtual void GoIdle();

};

#endif
