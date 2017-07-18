#include "AntonioFSM.h"
#include "Antonio.h"

AntonioFSM::AntonioFSM(Antonio *ant) : antonio(ant) 
{
	prev_state = State::START;
	curr_state = State::IDLE;
}

AntonioFSM::~AntonioFSM() {}

void AntonioFSM::Update()
{
	switch (curr_state)
	{
	case State::IDLE:
		Idle();
		break;
	}
}

void AntonioFSM::Idle()
{
	if (antonio->facing_right)
		antonio->curr_anim = &antonio->antonio_boomerang_idle_right;
	else
		antonio->curr_anim = &antonio->antonio_boomerang_idle_left;
}

void AntonioFSM::Chase()
{

}

void AntonioFSM::Kick()
{

}

void AntonioFSM::ThrowBoomerang()
{

}

void AntonioFSM::Grabbed()
{

}

void AntonioFSM::GrabbedFirstStage()
{

}

void AntonioFSM::GrabbedSecondStage()
{

}

void AntonioFSM::GrabbedThirdStage()
{

}

void AntonioFSM::GrabbedFourthStage()
{

}

void AntonioFSM::GrabbedFifthStage()
{

}

void AntonioFSM::GrabbedSixthStage()
{

}

void AntonioFSM::GrabbedSeventhDownStage()
{

}

void AntonioFSM::Damaged()
{

}

void AntonioFSM::KnockedDown()
{

}

void AntonioFSM::Dead()
{

}


//---------------------------------------------------------------------------------------------------------------------------


AntonioFSM::State AntonioFSM::GetCurrState()  const
{
	return curr_state;
}

void AntonioFSM::SetCurrState(State state)
{
	curr_state = state;
}

void AntonioFSM::UpdateColliderPosition()
{
	if (antonio->facing_right)
	{
		antonio->body_collider->SetPos(antonio->position.x + antonio->body_collider_offset_right, antonio->position.y + antonio->body_collider_offset_y);
		antonio->hit_collider->SetPos(antonio->position.x + antonio->hit_collider_offset_right, antonio->position.y + antonio->hit_collider_offset_y);
	}
	else
	{
		antonio->body_collider->SetPos(antonio->position.x + antonio->body_collider_offset_left, antonio->position.y + antonio->body_collider_offset_y);
		antonio->hit_collider->SetPos(antonio->position.x + antonio->hit_collider_offset_left, antonio->position.y + antonio->hit_collider_offset_y);
	}

}