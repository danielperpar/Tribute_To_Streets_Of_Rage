#include "GameTimer.h"

GameTimer::GameTimer() {}
GameTimer::~GameTimer() {}

void GameTimer::Start()
{
	//timer reset
	current = SDL_GetTicks();
	previous = 0;
}


int GameTimer::Read()
{
	return current - previous;
}