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

void PlayerFSM::GoIdle()
{
	curr_state->GoIdle();
}
//----------------------------------- GETTERS & SETTERS -------------------------
 State* PlayerFSM::GetCurrState() const
{
	return curr_state;
}

void PlayerFSM::SetCurrState(State *state)
{
	curr_state = state;
}

Player* PlayerFSM::GetPlayer() const
{
	return player;
}

State* PlayerFSM::GetIdle() const
{
	return idle;
}

State* PlayerFSM::GetWalk() const
{
	return walk;
}

State* PlayerFSM::GetJump() const
{
	return jump;
}

State* PlayerFSM::GetAirKick() const
{
	return air_kick;
}

State* PlayerFSM::GetSimplePunch() const
{
	return simple_punch;
}

State* PlayerFSM::GetCboPunch() const
{
	return cbo_punch;
}

State* PlayerFSM::GetCboLowPunch() const
{
	return cbo_low_punch;
}

State* PlayerFSM::GetCboKick() const
{
	return cbo_kick;
}

State* PlayerFSM::GetGrab() const
{
	return grab;
}

State* PlayerFSM::GetLowKick() const
{
	return low_kick;
}

State* PlayerFSM::GetHeadHit() const
{
	return head_hit;
}

State* PlayerFSM::GetAirAttack() const
{
	return air_attack;
}

State* PlayerFSM::GetFinisher() const
{
	return finisher;
}

State* PlayerFSM::GetRelease() const
{
	return release;
}

State* PlayerFSM::GetPreBackPunch() const
{
	return pre_back_punch;
}

State* PlayerFSM::GetBackPunch() const
{
	return back_punch;
}

State* PlayerFSM::GetDamaged() const
{
	return damaged;
}

State* PlayerFSM::GetKnockDown() const
{
	return knock_down;
}


//------------------------------------- DESTRUCTOR ----------------------------
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

