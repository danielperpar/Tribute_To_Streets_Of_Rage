#ifndef __BACKPUNCH_H__
#define __BACKPUNCH_H__

#include "State.h"

class PlayerFSM;
class BackPunch : public State
{
private:
	PlayerFSM *player_fsm;

public:
	BackPunch(PlayerFSM *fsm);
	~BackPunch();

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
