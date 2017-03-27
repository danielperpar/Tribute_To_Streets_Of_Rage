#ifndef __PREBACKPUNCH_H__
#define __PREBACKPUNCH_H__

#include "State.h"

class PreBackPunch : public State
{
public:
	PreBackPunch();
	~PreBackPunch();

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
