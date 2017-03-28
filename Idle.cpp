#include "Idle.h"
#include "Player.h"
#include "PlayerFSM.h"

Idle::Idle(PlayerFSM *fsm) : player_fsm(fsm){}

Idle::~Idle(){}

void Idle::AttackPressed()
{
	if (player_fsm->GetPlayer()->facing_right)
	{
		player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->punch_combo_right1);
		player_fsm->GetPlayer()->current_animation->Reset();

		player_fsm->SetCurrState(player_fsm->GetSimplePunch());
	}
	else
	{
		player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->punch_combo_left1);
		player_fsm->GetPlayer()->current_animation->Reset();

		player_fsm->SetCurrState(player_fsm->GetSimplePunch());
	}
}

void Idle::AttackHold()
{
	//no action
}

void Idle::JumpPressed()
{
	if (player_fsm->GetPlayer()->facing_right)
	{
		player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->jump_right1);
		player_fsm->GetPlayer()->current_animation->Reset();

		player_fsm->SetCurrState(player_fsm->GetJump());
	}
	else
	{
		player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->jump_left1);
		player_fsm->GetPlayer()->current_animation->Reset();

		player_fsm->SetCurrState(player_fsm->GetJump());
	}
}

void Idle::JumpHold()
{
	//no action
}

void Idle::LeftPressed()
{
	player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->walk_left);
	player_fsm->GetPlayer()->current_animation->Reset();

	player_fsm->SetCurrState(player_fsm->GetWalk());
}

void Idle::LeftHold()
{
	player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->walk_left);
	player_fsm->GetPlayer()->current_animation->Reset();

	player_fsm->SetCurrState(player_fsm->GetWalk());
}

void Idle::RightPressed()
{
	player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->walk_right);
	player_fsm->GetPlayer()->current_animation->Reset();

	player_fsm->SetCurrState(player_fsm->GetWalk());
}

void Idle::RightHold()
{
	player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->walk_right);
	player_fsm->GetPlayer()->current_animation->Reset();

	player_fsm->SetCurrState(player_fsm->GetWalk());
}

void Idle::UpPressed()
{
	if (player_fsm->GetPlayer()->facing_right)
	{
		player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->walk_right);
		player_fsm->GetPlayer()->current_animation->Reset();

		player_fsm->SetCurrState(player_fsm->GetWalk());
	}
	else
	{
		player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->walk_left);
		player_fsm->GetPlayer()->current_animation->Reset();

		player_fsm->SetCurrState(player_fsm->GetWalk());
	}
}

void Idle::UpHold()
{
	if (player_fsm->GetPlayer()->facing_right)
	{
		player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->walk_right);
		player_fsm->GetPlayer()->current_animation->Reset();

		player_fsm->SetCurrState(player_fsm->GetWalk());
	}
	else
	{
		player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->walk_left);
		player_fsm->GetPlayer()->current_animation->Reset();

		player_fsm->SetCurrState(player_fsm->GetWalk());
	}
}

void Idle::DownPressed()
{
	if (player_fsm->GetPlayer()->facing_right)
	{
		player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->walk_right);
		player_fsm->GetPlayer()->current_animation->Reset();

		player_fsm->SetCurrState(player_fsm->GetWalk());
	}
	else
	{
		player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->walk_left);
		player_fsm->GetPlayer()->current_animation->Reset();

		player_fsm->SetCurrState(player_fsm->GetWalk());
	}
}

void Idle::DownHold()
{
	if (player_fsm->GetPlayer()->facing_right)
	{
		player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->walk_right);
		player_fsm->GetPlayer()->current_animation->Reset();

		player_fsm->SetCurrState(player_fsm->GetWalk());
	}
	else
	{
		player_fsm->GetPlayer()->current_animation = &(player_fsm->GetPlayer()->walk_left);
		player_fsm->GetPlayer()->current_animation->Reset();

		player_fsm->SetCurrState(player_fsm->GetWalk());
	}
}

void Idle::GoIdle()
{
	//no action
}