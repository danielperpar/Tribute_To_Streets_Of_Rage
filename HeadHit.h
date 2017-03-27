#ifndef __HEADHIT_H__
#define __HEADHIT_H__

#include "State.h"

class HeadHit : public State
{
public:
	HeadHit();
	~HeadHit();

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
