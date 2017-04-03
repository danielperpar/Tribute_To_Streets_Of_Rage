#include "PlayerFSM.h"
#include "Globals.h"
#include "ModulePlayer.h"
#include "Player.h"

PlayerFSM::PlayerFSM(ModulePlayer *module_player) : module_player(module_player)
{
	curr_state = State::IDLE;	
}
// ------------------------------- UPDATE THE FSM -------------------------------------------------------
void PlayerFSM::Update()
{
	switch (curr_state)
	{
	case State::IDLE:
		Idle();
		if (	
			module_player->walk_left ||	module_player->walk_right ||
			module_player->walk_up || module_player->walk_down
			)		
		{
			curr_state = State::WALK;
			break;
		}
		

		break;
	case State::WALK:
		Walk();
	}
}

// ------------------------------- ACTIONS TO PERFORM IN EVERY STATE ------------------------------------
void PlayerFSM::Idle()
{
	
	if (prev_state != State::IDLE)
	{
		if (module_player->facing_right)
			module_player->player->curr_anim = &(module_player->player->anim_idle_right1);

		if(!module_player->facing_right)
			module_player->player->curr_anim = &(module_player->player->anim_idle_left1);
	}
	else
	{
		//setting right animations
		if (module_player->player->curr_anim == &(module_player->player->anim_idle_right1))
		{
			if (module_player->player->curr_anim->Finished())
			{
				module_player->player->curr_anim->Reset();
				module_player->player->curr_anim = &(module_player->player->anim_idle_right2);
			}
		}
		else if (module_player->player->curr_anim == &(module_player->player->anim_idle_right2))
		{
			if (module_player->player->curr_anim->Finished())
			{
				module_player->player->curr_anim->Reset();
				module_player->player->curr_anim = &(module_player->player->anim_idle_right3);
			}
		}
		else if (module_player->player->curr_anim == &(module_player->player->anim_idle_right3))
		{
			if (module_player->player->curr_anim->Finished())
			{
				module_player->player->curr_anim->Reset();
				module_player->player->curr_anim = &(module_player->player->anim_idle_right1);
			}
		}
		// Setting left animations
		else if (module_player->player->curr_anim == &(module_player->player->anim_idle_left1))
		{
			if (module_player->player->curr_anim->Finished())
			{
				module_player->player->curr_anim->Reset();
				module_player->player->curr_anim = &(module_player->player->anim_idle_left2);
			}
		}
		else if (module_player->player->curr_anim == &(module_player->player->anim_idle_left2))
		{
			if (module_player->player->curr_anim->Finished())
			{
				module_player->player->curr_anim->Reset();
				module_player->player->curr_anim = &(module_player->player->anim_idle_left3);
			}
		}
		else if (module_player->player->curr_anim == &(module_player->player->anim_idle_left3))
		{
			if (module_player->player->curr_anim->Finished())
			{
				module_player->player->curr_anim->Reset();
				module_player->player->curr_anim = &(module_player->player->anim_idle_left1);
			}
		}
	}
	
}

void PlayerFSM::Walk()
{
	iPoint temp = module_player->player->position;

	//set position
	if (module_player->walk_left) 
	{
		module_player->facing_right = false;
		temp.x -= module_player->player->speed;
		module_player->walk_left = false;
	}
	if (module_player->walk_right)
	{
		module_player->facing_right = true;
		temp.x += module_player->player->speed;
		module_player->walk_right = false;
	}
	if (module_player->walk_up)
	{
		temp.y -= module_player->player->speed;
		module_player->walk_up = false;
	}
	if (module_player->walk_down)
	{
		temp.y += module_player->player->speed;
		module_player->walk_down = false;
	}

	//set animation
	if (module_player->facing_right == true)
	{
		if (module_player->player->curr_anim != &(module_player->player->anim_walk_right))
		{
			module_player->player->curr_anim = &(module_player->player->anim_walk_right);
			module_player->player->curr_anim->Reset();
		}
	}
	else
	{
		if (module_player->player->curr_anim != &(module_player->player->anim_walk_left))
		{
			module_player->player->curr_anim = &(module_player->player->anim_walk_left);
			module_player->player->curr_anim->Reset();
		}
	}
}

void PlayerFSM::Jump()
{

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

