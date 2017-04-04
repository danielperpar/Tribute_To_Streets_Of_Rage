#ifndef __GAMETIMER_H__
#define __GAMETIMER_H__
#include "SDL/include/SDL.h"

class GameTimer
{
private:
	Uint32 current = 0;
	Uint32 previous = 0;

public:
	GameTimer();
	~GameTimer();
	void Start();
	int Read();
};

#endif
