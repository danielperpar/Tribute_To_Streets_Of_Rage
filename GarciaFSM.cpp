#include "GarciaFSM.h"
#include "Garcia.h"

GarciaFSM::GarciaFSM(Garcia *grc) : garcia(grc) 
{
	prev_state = State::START;
	curr_state = State::IDLE;
	
}

GarciaFSM::~GarciaFSM() {}

void GarciaFSM::Update()
{
	switch (curr_state)
	{
	case State::IDLE:
		Idle();
		prev_state = curr_state;

		if (garcia->player_in_sight)
		{
			curr_state = State::CHASE;
			break;
		}
		break;

	case State::CHASE:
		break;

	case State::FAST_CHASE:
		break;

	case State::ATTACK:
		break;

	case State::EVASIVE:
		break;

	case State::DAMAGED:
		break;

	case State::KNOCKED_DOWN:
		break;

	}
}

//-----------------------------  ACTIONS TO PERFORM IN EACH STATE ------------------------------------
void GarciaFSM::Idle()
{
	if(garcia->facing_right)
		garcia->curr_anim = &(garcia->garcia_idle_right);
	if (!garcia->facing_right)
		garcia->curr_anim = &(garcia->garcia_idle_left);
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