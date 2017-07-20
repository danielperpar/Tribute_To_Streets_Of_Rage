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
	case State::GRABBED:
		Grabbed();
		if (!antonio->grabbed)
		{
			if (antonio->facing_right)
			{
				antonio->curr_anim = &(antonio->antonio_idle_right);
			}
			else
			{
				antonio->curr_anim = &(antonio->antonio_idle_left);
			}
			frames_counter++;
			if (frames_counter >= num_frames)
			{
				frames_counter = 0;
				curr_state = State::IDLE;
			}
		}
		if (antonio->damaged)
		{
			if (antonio->life > 0)
				curr_state = State::DAMAGED;
			else
			{
				antonio->knocked_down = true;
				curr_state = State::KNOCKED_DOWN;
			}

			prev_state = State::GRABBED;
			break;
		}
		if (antonio->knocked_down)
		{
			curr_state = State::KNOCKED_DOWN;
			break;
		}
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
	switch (grab_stage)
	{
	case GrabStage::FIRST_STAGE:
		GrabbedFirstStage();
		break;
	case GrabStage::SECOND_STAGE:
		GrabbedSecondStage();
		break;
	case GrabStage::THIRD_STAGE:
		GrabbedThirdStage();
		break;
	case GrabStage::FOURTH_STAGE:
		GrabbedFourthStage();
		break;
	case GrabStage::FIFTH_STAGE:
		GrabbedFifthStage();
		break;
	case GrabStage::SIXTH_STAGE:
		GrabbedSixthStage();
		break;
	case GrabStage::SEVENTH_DOWN_STAGE:
		GrabbedSeventhDownStage();
		break;
	}
}

void AntonioFSM::GrabbedFirstStage()
{
	if (antonio->facing_right)
		antonio->curr_anim = &antonio->antonio_grabbed_right;	
	else
		antonio->curr_anim = &antonio->antonio_grabbed_left;
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