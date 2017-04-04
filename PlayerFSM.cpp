#include "PlayerFSM.h"
#include "Globals.h"
#include "ModulePlayer.h"
#include "Player.h"

PlayerFSM::PlayerFSM(Player *player) : the_player(player)
{
	prev_state = State::START;
	curr_state = State::IDLE;	
}
// ------------------------------- UPDATE THE FSM -------------------------------------------------------
void PlayerFSM::Update()
{
	switch (curr_state)
	{
	case State::IDLE:
		Idle();
		prev_state = curr_state;
		if (	
			the_player->walk_left || the_player->walk_right ||
			the_player->walk_up || the_player->walk_down
			)		
		{
			curr_state = State::WALK;
			break;
		}
		if (the_player->jump)
		{
			curr_state = State::JUMP;
			break;
		}
		break;
	case State::WALK:
		Walk();
		prev_state = curr_state;
		if (
			!the_player->walk_left && !the_player->walk_right &&
			!the_player->walk_up && !the_player->walk_down
			)
		{
			curr_state = State::IDLE;
			break;
		}
		if (the_player->jump)
		{
			curr_state = State::JUMP;
			break;
		}
		break;
	case State::JUMP:
		Jump();
		prev_state = curr_state;
		if (the_player->landed)
		{
			curr_state = State::IDLE;
			the_player->jump = false;
			break;
		}

		break;	
	}
}

// ------------------------------- ACTIONS TO PERFORM IN EVERY STATE ------------------------------------
void PlayerFSM::Idle()
{	
	if (prev_state != State::IDLE)
	{
		if (the_player->facing_right)
			the_player->curr_anim = &(the_player->anim_idle_right1);

		if(!the_player->facing_right)
			the_player->curr_anim = &(the_player->anim_idle_left1);
	}
	else
	{
		//setting right animations
		if (the_player->curr_anim == &(the_player->anim_idle_right1))
		{
			if (the_player->curr_anim->Finished())
			{
				the_player->curr_anim->Reset();
				the_player->curr_anim = &(the_player->anim_idle_right2);
			}
		}
		else if (the_player->curr_anim == &(the_player->anim_idle_right2))
		{
			if (the_player->curr_anim->Finished())
			{
				the_player->curr_anim->Reset();
				the_player->curr_anim = &(the_player->anim_idle_right3);
			}
		}
		else if (the_player->curr_anim == &(the_player->anim_idle_right3))
		{
			if (the_player->curr_anim->Finished())
			{
				the_player->curr_anim->Reset();
				the_player->curr_anim = &(the_player->anim_idle_right1);
			}
		}
		// Setting left animations
		else if (the_player->curr_anim == &(the_player->anim_idle_left1))
		{
			if (the_player->curr_anim->Finished())
			{
				the_player->curr_anim->Reset();
				the_player->curr_anim = &(the_player->anim_idle_left2);
			}
		}
		else if (the_player->curr_anim == &(the_player->anim_idle_left2))
		{
			if (the_player->curr_anim->Finished())
			{
				the_player->curr_anim->Reset();
				the_player->curr_anim = &(the_player->anim_idle_left3);
			}
		}
		else if (the_player->curr_anim == &(the_player->anim_idle_left3))
		{
			if (the_player->curr_anim->Finished())
			{
				//the_player->curr_anim->Reset();
				the_player->curr_anim = &(the_player->anim_idle_left1);
			}
		}
	}
	
}

void PlayerFSM::Walk()
{
	iPoint temp = the_player->position;

	//set position
	if (the_player->walk_left)
	{
		the_player->facing_right = false;
		temp.x -= the_player->speed;
		the_player->position = temp;
	}
	if (the_player->walk_right)
	{
		the_player->facing_right = true;
		temp.x += the_player->speed;
		the_player->position = temp;
	}
	if (the_player->walk_up)
	{
		temp.y -= the_player->speed;
		the_player->position = temp;
		the_player->depth = temp.y;
	}
	if (the_player->walk_down)
	{
		temp.y += the_player->speed;
		the_player->position = temp;
		the_player->depth = temp.y;
	}

	//set animation
	if (prev_state != State::WALK)
	{
		if (the_player->facing_right)
		{
			the_player->curr_anim = &(the_player->anim_walk_right);
			the_player->curr_anim->Reset();
		}

		if (!the_player->facing_right)
		{
			the_player->curr_anim = &(the_player->anim_walk_left);
			the_player->curr_anim->Reset();
		}
	}

	if (the_player->facing_right)
	{
		the_player->curr_anim = &(the_player->anim_walk_right);	
	}

	if (!the_player->facing_right)
	{
		the_player->curr_anim = &(the_player->anim_walk_left);	
	}

}

void PlayerFSM::Jump()
{
	iPoint temp = the_player->position;

	//set animation
	if (prev_state != State::JUMP)
	{
		if (the_player->facing_right)
			the_player->curr_anim = &(the_player->anim_jump_right1);

		if (!the_player->facing_right)
			the_player->curr_anim = &(the_player->anim_jump_left1);
	}

	if (the_player->hit_hold == false)
	{
		//setting right animations
		if (the_player->curr_anim == &(the_player->anim_jump_right1))
		{
			if (the_player->curr_anim->Finished())
			{
				the_player->curr_anim->Reset();
				the_player->curr_anim = &(the_player->anim_jump_right2);
			}
		}

		//setting left animations
		if (the_player->curr_anim == &(the_player->anim_jump_left1))
		{
			if (the_player->curr_anim->Finished())
			{
				the_player->curr_anim->Reset();
				the_player->curr_anim = &(the_player->anim_jump_left2);
			}
		}
	}
	else if(the_player->hit_hold == true)
	{
		//setting right animations
		if (the_player->facing_right)
		{			
			the_player->curr_anim = &(the_player->anim_air_kick_right);			
		}

		//setting left animations
		if (!the_player->facing_right)
		{
			the_player->curr_anim = &(the_player->anim_air_kick_left);
		}
	}

	if (
		the_player->curr_anim == &(the_player->anim_jump_right2) || the_player->curr_anim == &(the_player->anim_jump_left2) ||
		the_player->curr_anim == &(the_player->anim_air_kick_right) || the_player->curr_anim == &(the_player->anim_air_kick_left)
		)
	{
		//set position x
		if (the_player->walk_left)
		{
			the_player->facing_right = false;
			temp.x -= the_player->speed;
		}
		if (the_player->walk_right)
		{
			the_player->facing_right = true;
			temp.x += the_player->speed;
		}

		//set position y
		if (the_player->jump_up)
		{
			temp.y -= the_player->jump_speed;
			the_player->jump_count++;
			if (the_player->jump_count >= the_player->max_jump_height)
			{
				the_player->jump_up = false;
			}
		}
		if (the_player->jump_up == false)
		{
			temp.y += the_player->jump_speed;
			the_player->jump_count--;
			if (the_player->jump_count == 0)
			{
				the_player->landed = true;
			}
		}
		if (the_player->landed) //reset jump_up
			the_player->jump_up = true;

		the_player->position = temp;

	}


}
void PlayerFSM::AirKick()
{

}

void PlayerFSM::SimplePunch()
{

}

void PlayerFSM::CboPunch()
{

}

void PlayerFSM::CboLowPunch()
{

}

void PlayerFSM::CboKick()
{

}

void PlayerFSM::Grab()
{

}

void PlayerFSM::LowKick()
{

}

void PlayerFSM::HeadHit()
{

}

void PlayerFSM::AirAttack()
{

}

void PlayerFSM::Finisher()
{

}
void PlayerFSM::Release()
{

}

void PlayerFSM::PreBackPunch()
{

}
void PlayerFSM::BackPunch()
{

}
void PlayerFSM::Damaged()
{

}
void PlayerFSM::KnockDown()
{

}

PlayerFSM::State PlayerFSM::GetCurrState() const
{
	return curr_state;
}

void PlayerFSM::SetCurrState(State state)
{	
		curr_state = state;
	
}


//------------------------------------- DESTRUCTOR ----------------------------
PlayerFSM::~PlayerFSM()
{

}

