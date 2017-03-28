#ifndef __STATE_H__
#define __STATE_H__

class State
{
public:
	State();
	virtual ~State();

	virtual void AttackPressed() = 0;
	virtual void AttackHold() = 0;
	virtual void JumpPressed() = 0;
	virtual void JumpHold() = 0;
	virtual void LeftPressed() = 0;
	virtual void LeftHold() = 0;
	virtual void RightPressed() = 0;
	virtual void RightHold() = 0;
	virtual void UpPressed() = 0;
	virtual void UpHold() = 0;
	virtual void DownPressed() = 0;
	virtual void DownHold() = 0;
	virtual void GoIdle() = 0;
};

#endif