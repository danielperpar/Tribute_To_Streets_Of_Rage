#ifndef __CBOLOWPUNCH_H__
#define __CBOLOWPUNCH_H__

#include "State.h"

class PlayerFSM;
class CboLowPunch : public State
{
private:
	PlayerFSM *player_fsm;

public:
	CboLowPunch(PlayerFSM *fsm);
	~CboLowPunch();

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
