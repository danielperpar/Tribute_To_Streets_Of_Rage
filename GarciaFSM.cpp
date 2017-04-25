#include "GarciaFSM.h"
#include "Garcia.h"
#include "Player.h"
#include "Point.h"

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
		Chase();
		if (garcia->attack)
		{
			curr_state = State::ATTACK;
			break;
		}
		break;

	case State::ATTACK:
		Attack();
		if (garcia->attack == false)
		{
			curr_state = State::CHASE;
		}
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
	iPoint target;

	target.x = garcia->the_player->position.x - garcia->position.x;
	target.y = garcia->the_player->depth - garcia->position.y;
		
	iPoint direction{ 0,0 };
	
	if (target.x > 0)
	{
		direction.x = 1;
		if (!garcia->facing_right)
			garcia->facing_right = true;	
	}

	if(target.x < 0)
	{
		direction.x = -1;
		if (garcia->facing_right)
			garcia->facing_right = false;	
	}

	if (target.y > 0)	
		direction.y = 1;		
	
	if (target.y < 0)
		direction.y = -1;		
	

	int distance_x = target.x > 0 ? target.x : -target.x;
	int distance_y = target.y > 0 ? target.y : -target.y;

	if (garcia->facing_right && garcia->the_player->facing_right || !garcia->facing_right && !garcia->the_player->facing_right)
	{
		if (distance_x < garcia->speed_vect.x)
		{
			garcia->speed_vect.x = 1;
		}
		else
		{
			garcia->speed_vect.x = 2;
		}

		if (distance_y < garcia->speed_vect.y)
		{
			garcia->speed_vect.y = 1;
		}
		else
		{
			garcia->speed_vect.y = 2;
		}
	}
	else
	{
		garcia->speed_vect = { 1,1 };
	}
	garcia->position += {direction.x * garcia->speed_vect.x , direction.y * garcia->speed_vect.y};
	garcia->depth = garcia->position.y;
	UpdateColliderPosition();

	//set animations
		
	if (!garcia->facing_right)
	{
		if (garcia->curr_anim != &(garcia->garcia_walk_left))
		{
			garcia->curr_anim = &(garcia->garcia_walk_left);
			garcia->curr_anim->Reset();
		}
	}
			
	if (garcia->facing_right)
	{
		if (garcia->curr_anim != &(garcia->garcia_walk_right))
		{
			garcia->curr_anim = &(garcia->garcia_walk_right);
			garcia->curr_anim->Reset();
		}		
	}
}
	
void GarciaFSM::Attack()
{
	if (garcia->facing_right)
	{
		if (garcia->punch_hits == 0 || garcia->punch_hits == 1)
		{
			garcia->curr_anim = &garcia->garcia_punch_right1;
			if (garcia->curr_anim->Finished())
			{
				garcia->curr_anim->Reset();
				garcia->punch_hits++;
			}
		}
		if (garcia->punch_hits == 2)
		{
			if (garcia->curr_anim != &garcia->garcia_punch_right2)
			{
				garcia->curr_anim = &garcia->garcia_punch_right2;
				garcia->curr_anim->Reset();
			}		
			if (garcia->curr_anim->Finished())
			{			
				garcia->punch_hits++;
			}
		}
	
		if (garcia->punch_hits == 3)
			garcia->punch_hits = 0;
	}

	if (garcia->facing_right == false)
	{
		if (garcia->punch_hits == 0 || garcia->punch_hits == 1)
		{			
			garcia->curr_anim = &garcia->garcia_punch_left1;
						
			if (garcia->curr_anim->Finished())
			{			
				garcia->curr_anim->Reset();
				garcia->punch_hits++;
			}
		}
		if (garcia->punch_hits == 2)
		{
			if (garcia->curr_anim != &garcia->garcia_punch_left2)
			{
				garcia->curr_anim = &garcia->garcia_punch_left2;
				garcia->curr_anim->Reset();
			}		
			if (garcia->curr_anim->Finished())
			{				
				garcia->punch_hits++;
			}
		}

		if (garcia->punch_hits == 3)
			garcia->punch_hits = 0;
	}
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

void GarciaFSM::UpdateColliderPosition()
{
	if (garcia->facing_right)
	{
		garcia->body_collider->SetPos(garcia->position.x + garcia->body_collider_offset_right, garcia->position.y);
		garcia->hit_collider->SetPos(garcia->position.x + garcia->hit_collider_offset_right, garcia->position.y);
	}
	else
	{
		garcia->body_collider->SetPos(garcia->position.x + garcia->body_collider_offset_left, garcia->position.y);
		garcia->hit_collider->SetPos(garcia->position.x + garcia->hit_collider_offset_left, garcia->position.y);
	}

}