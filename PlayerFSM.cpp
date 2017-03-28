#include "PlayerFSM.h"
#include "Globals.h"
#include "Idle.h"
#include "Walk.h"
#include "Jump.h"
#include "AirKick.h"
#include "SimplePunch.h"
#include "CboPunch.h"
#include "CboLowPunch.h"
#include "CboKick.h"
#include "Grab.h"
#include "LowKick.h"
#include "HeadHit.h"
#include "AirAttack.h"
#include "Finisher.h"
#include "Release.h"
#include "PreBackPunch.h"
#include "BackPunch.h"
#include "Damaged.h"
#include "KnockDown.h"

PlayerFSM::PlayerFSM(Player *player) : player(player)
{
	idle = new Idle(this);
	walk = new Walk(this);
	jump = new Jump(this);
	air_kick = new AirKick(this);
	simple_punch = new SimplePunch(this);
	cbo_punch = new CboPunch(this);
	cbo_low_punch = new CboLowPunch(this);
	cbo_kick = new CboKick(this);
	grab = new Grab(this);
	low_kick = new LowKick(this);
	head_hit = new HeadHit(this);
	air_attack = new AirAttack(this);
	finisher = new Finisher(this);
	release = new Release(this);
	pre_back_punch = new PreBackPunch(this);
	back_punch = new BackPunch(this);
	damaged = new Damaged(this);
	knock_down = new KnockDown(this);

	curr_state = idle;
}

void PlayerFSM::AttackPressed()
{
	curr_state->AttackPressed();
}

void PlayerFSM::AttackHold()
{
	curr_state->AttackHold();
}

void PlayerFSM::JumpPressed()
{
	curr_state->JumpPressed();
}

void PlayerFSM::JumpHold()
{
	curr_state->JumpHold();
}

void PlayerFSM::LeftPressed()
{
	curr_state->LeftPressed();
}

void PlayerFSM::LeftHold()
{
	curr_state->LeftHold();
}

void PlayerFSM::RightPressed()
{
	curr_state->RightPressed();
}

void PlayerFSM::RightHold()
{
	curr_state->RightHold();
}

void PlayerFSM::UpPressed()
{
	curr_state->UpPressed();
}

void PlayerFSM::UpHold()
{
	curr_state->UpHold();
}

void PlayerFSM::DownPressed()
{
	curr_state->DownPressed();
}

void PlayerFSM::DownHold()
{
	curr_state->DownHold();
}

const State *PlayerFSM::GetState() const
{
	return curr_state;
}

void PlayerFSM::SetState(State *state)
{
	curr_state = state;
}

PlayerFSM::~PlayerFSM()
{
	RELEASE(idle);
	RELEASE(walk);
	RELEASE(jump);
	RELEASE(air_kick);
	RELEASE(simple_punch);
	RELEASE(cbo_punch);
	RELEASE(cbo_low_punch);
	RELEASE(cbo_kick);
	RELEASE(grab);
	RELEASE(low_kick);
	RELEASE(head_hit);
	RELEASE(air_attack);
	RELEASE(finisher);
	RELEASE(release);
	RELEASE(pre_back_punch);
	RELEASE(back_punch);
	RELEASE(damaged);
	RELEASE(knock_down);
}

