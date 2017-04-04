#include "GarciaFSM.h"

GarciaFSM::GarciaFSM(Enemy *enemy) : garcia(enemy) 
{
	garcia = enemy;
}

GarciaFSM::~GarciaFSM() {}

void GarciaFSM::Update()
{

}

//-----------------------------  ACTIONS TO PERFORM IN EACH STATE ------------------------------------
void GarciaFSM::Idle()
{

}
void GarciaFSM::Chase()
{

}
void GarciaFSM::FastChase()
{

}
void GarciaFSM::Attack()
{

}
void GarciaFSM::Evasive()
{

}

GarciaFSM::State GarciaFSM::GetCurrState()  const
{
	return curr_state;
}

void GarciaFSM::SetCurrState(State state)
{
	curr_state = state;
}