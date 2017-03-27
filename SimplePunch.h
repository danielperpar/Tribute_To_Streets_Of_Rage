#ifndef __SIMPLEPUNCH_H__
#define __SIMPLEPUNCH_H__

#include "State.h"

class SimplePunch : public State
{
public:
	SimplePunch();
	~SimplePunch();

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

