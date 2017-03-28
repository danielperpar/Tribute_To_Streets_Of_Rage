#ifndef __RELEASE_H__
#define _RELEASE_H__

#include "State.h"

class PlayerFSM;
class Release : public State
{
private:
	PlayerFSM *player_fsm;

public:
	Release(PlayerFSM *fsm);
	~Release();

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
