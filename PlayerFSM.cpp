#include "PlayerFSM.h"
#include "Globals.h"
#include "ModulePlayer.h"
#include "Player.h"
#include "Application.h"
#include "ModuleSceneRound1.h"
#include "Garcia.h"

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
		if (the_player->hit_down)
		{
			curr_state = State::CBO_PUNCH;
			break;
		}
		if (the_player->damaged)
		{
			LOG("entro damage");
			curr_state = State::DAMAGED;
			break;
		}
		if (the_player->knocked_down)
		{
			curr_state = State::KNOCKED_DOWN;
			break;
		}
		if (the_player->enemy_to_grab)
		{
			curr_state = State::GRAB;
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
		if (the_player->hit_down)
		{
			curr_state = State::CBO_PUNCH;
			break;
		}
		if (the_player->damaged)
		{
			curr_state = State::DAMAGED;
			break;
		}
		if (the_player->knocked_down)
		{
			curr_state = State::KNOCKED_DOWN;
			break;
		}
		if (the_player->enemy_to_grab)
		{			
			curr_state = State::GRAB;
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
	case State::CBO_PUNCH:
		Punch();
		prev_state = curr_state;
		if (the_player->attack_finished)
		{
			curr_state = State::IDLE;
			the_player->attack_finished = false;
			break;
		}
		break;

	case State::DAMAGED:
		Damaged();
		prev_state = curr_state;
		if (!the_player->damaged)
		{
			curr_state = State::IDLE;			
			break;
		}
		break;

	case State::KNOCKED_DOWN:
		KnockedDown();
		prev_state = curr_state;
		if (!the_player->knocked_down)
		{
			curr_state = State::IDLE;		
			break;
		}
		break;

	case State::GRAB:
		Grab();
		prev_state = curr_state;
		if (
			the_player->walk_left && the_player->left_blocked == false	||
			the_player->walk_right && the_player->right_blocked == false			
			)
		{
			curr_state = State::WALK;
			the_player->enemy_to_grab = false;
			if (the_player->facing_right)
				the_player->position.x -= the_player->release_grab_offset;
			else
				the_player->position.x += the_player->release_grab_offset;

			UpdateColliderPosition();

			break;
		}
		if (the_player->hit_down)
		{
			if (the_player->grab_hit_counter < the_player->max_grab_kick)
			{
				the_player->grab_hit_counter++;
				curr_state = State::LOW_KICK;
			}
			else
			{
				the_player->grab_hit_counter = 0;
				curr_state = State::HEAD_HIT;
			}
			break;
		}
		if (the_player->jump)
		{
			curr_state = State::AIR_ATTACK;
			break;
		}
		if (the_player->damaged)
		{
			curr_state = State::DAMAGED;
			break;
		}
		break;

	case State::LOW_KICK:
		LowKick();
		break;

	case State::HEAD_HIT:
		HeadHit();
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

	//Update punch combo timer
	if (the_player->start_combo_timer)
	{
		the_player->combo_timer_count++;
		if (the_player->combo_timer_count >= the_player->combo_max_frames)
		{
			the_player->combo_timer_count = 0;
			the_player->punch_combo_hits = 0;
			cbo_punch_stage = CboPunchStage::HIGH_PUNCH;
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
		UpdateColliderPosition();
	}
	if (the_player->walk_right)
	{
		the_player->facing_right = true;
		temp.x += the_player->speed;
		the_player->position = temp;
		UpdateColliderPosition();
	}
	if (the_player->walk_up)
	{
		if (the_player->position.y > App->scene_round1->upper_limit)
		{
			temp.y -= the_player->speed;
			the_player->position = temp;
			the_player->depth = temp.y;
			UpdateColliderPosition();
		}
	}
	if (the_player->walk_down)
	{
		if (the_player->position.y < App->scene_round1->lower_limit)
		{
			temp.y += the_player->speed;
			the_player->position = temp;
			the_player->depth = temp.y;
			UpdateColliderPosition();
		}
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
		
		//Only garcia enemy atm, enemy type not checked
		for (std::list<std::pair<CollisionInfo, CollisionInfo>>::iterator it = the_player->player_collision_status.begin(); it != the_player->player_collision_status.end(); it++)
		{
			if ((*it).first.collider->type == collider_type::PLAYER_HIT && (*it).second.collider->type == collider_type::ENEMY_BODY)
				((Garcia*)((*it).second.collider->entity))->knocked_down = true;
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
			UpdateColliderPosition();
		}
		if (the_player->walk_right)
		{
			the_player->facing_right = true;
			temp.x += the_player->speed;
			UpdateColliderPosition();
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
		UpdateColliderPosition();

	}
}

void PlayerFSM::Punch()
{
	the_player->enemy_at_range = false;

	for (std::list<std::pair<CollisionInfo, CollisionInfo>>::iterator it = the_player->player_collision_status.begin(); it != the_player->player_collision_status.end(); it++)
	{
		if ((*it).first.collider->type == collider_type::PLAYER_HIT && (*it).second.collider->type == collider_type::ENEMY_BODY)
		{
			the_player->enemy_at_range = true;
			the_player->grabbed_enemy = (*it).second.collider->entity;
			break;
		}
	}

	//Only Garcia atm
	Garcia *garcia = (Garcia*)(the_player->grabbed_enemy);

	if (the_player->enemy_at_range && garcia->knocked_down == false)
	{	
		switch (cbo_punch_stage)
		{
		case CboPunchStage::HIGH_PUNCH:
			CboHighPunch();			
			break;

		case CboPunchStage::LOW_PUNCH:
			CboLowPunch();
			break;

		case CboPunchStage::HIGH_KICK:
			CboKick();
			break;
		}	
	}
	else
	{
		if (the_player->facing_right)
			the_player->curr_anim = &(the_player->anim_punch_combo_right1);

		if (!the_player->facing_right)
			the_player->curr_anim = &(the_player->anim_punch_combo_left1);

		if (the_player->curr_anim->Finished())
		{
			the_player->curr_anim->Reset();
			the_player->attack_finished = true;
		}
	}

}

void PlayerFSM::CboHighPunch()
{
	if (the_player->facing_right)
		the_player->curr_anim = &(the_player->anim_punch_combo_right1);

	if (!the_player->facing_right)
		the_player->curr_anim = &(the_player->anim_punch_combo_left1);

	if (the_player->curr_anim->Finished())
	{
		the_player->curr_anim->Reset();
		the_player->punch_combo_hits++;
		the_player->attack_finished = true; //go to IDLE
		the_player->start_combo_timer = true;
		the_player->combo_timer_count = 0;

		//Only garcia enemy atm, enemy type not checked
		for (std::list<std::pair<CollisionInfo, CollisionInfo>>::iterator it = the_player->player_collision_status.begin(); it != the_player->player_collision_status.end(); it++)
		{
			if ((*it).first.collider->type == collider_type::PLAYER_HIT && (*it).second.collider->type == collider_type::ENEMY_BODY)
				((Garcia*)((*it).second.collider->entity))->damaged = true;			
		}
	}

	if (the_player->punch_combo_hits == 2)
	{
		cbo_punch_stage = CboPunchStage::LOW_PUNCH;
		the_player->punch_combo_hits = 0;	
	}
}

void PlayerFSM::CboLowPunch()
{
	if (the_player->facing_right)
		the_player->curr_anim = &(the_player->anim_punch_combo_right2);

	if (!the_player->facing_right)
		the_player->curr_anim = &(the_player->anim_punch_combo_left2);

	if (the_player->curr_anim->Finished())
	{
		the_player->curr_anim->Reset();		
		cbo_punch_stage = CboPunchStage::HIGH_KICK;
		the_player->attack_finished = true; //go to IDLE
		the_player->start_combo_timer = true;
		the_player->combo_timer_count = 0;

		//Only garcia enemy atm, enemy type not checked
		for (std::list<std::pair<CollisionInfo, CollisionInfo>>::iterator it = the_player->player_collision_status.begin(); it != the_player->player_collision_status.end(); it++)
		{
			if ((*it).first.collider->type == collider_type::PLAYER_HIT && (*it).second.collider->type == collider_type::ENEMY_BODY)
				((Garcia*)((*it).second.collider->entity))->damaged = true;
		}
	}
}

void PlayerFSM::CboKick()
{
	if (the_player->facing_right)
		the_player->curr_anim = &(the_player->anim_punch_combo_right3);

	if (!the_player->facing_right)
		the_player->curr_anim = &(the_player->anim_punch_combo_left3);


	if (the_player->curr_anim->Finished())
	{
		the_player->curr_anim->Reset();
		cbo_punch_stage = CboPunchStage::HIGH_PUNCH;
		the_player->attack_finished = true; //go to IDLE
		the_player->start_combo_timer = false;
		the_player->combo_timer_count = 0;

		//Only garcia enemy atm, enemy type not checked
		for (std::list<std::pair<CollisionInfo, CollisionInfo>>::iterator it = the_player->player_collision_status.begin(); it != the_player->player_collision_status.end(); it++)
		{
			if ((*it).first.collider->type == collider_type::PLAYER_HIT && (*it).second.collider->type == collider_type::ENEMY_BODY)
				((Garcia*)((*it).second.collider->entity))->knocked_down = true;
		}
		
	}
}

void PlayerFSM::Grab()
{
	if (the_player->facing_right)
		the_player->curr_anim = &the_player->anim_grab_right;
	else
		the_player->curr_anim = &the_player->anim_grab_left;

}

void PlayerFSM::LowKick()
{
	if (the_player->facing_right)
		the_player->curr_anim = &the_player->anim_grab_kick_head_combo_right1;
	else
		the_player->curr_anim = &the_player->anim_grab_kick_head_combo_left1;

	if (the_player->curr_anim->Finished())
	{
		((Garcia*)(the_player->grabbed_enemy))->damaged = true;
		the_player->curr_anim->Reset();
		curr_state = State::GRAB;
	}

}

void PlayerFSM::HeadHit()
{
	if (the_player->facing_right)
		the_player->curr_anim = &the_player->anim_grab_kick_head_combo_right2;
	else
		the_player->curr_anim = &the_player->anim_grab_kick_head_combo_left2;

	if (the_player->curr_anim->Finished())
	{
		((Garcia*)(the_player->grabbed_enemy))->knocked_down = true;
		the_player->curr_anim->Reset();
		the_player->enemy_to_grab = false;
		curr_state = State::IDLE;
	}
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
	//Set player facing the enemy to react to
	if (the_player->enemy_attacker->position.x >= the_player->position.x)
	{
		if (the_player->facing_right == false)
			the_player->facing_right = true;
	}
	else
	{
		if (the_player->facing_right)
			the_player->facing_right = false;
	}

	if (the_player->facing_right)
		the_player->curr_anim = &(the_player->anim_damage_received_right);

	if (!the_player->facing_right)
		the_player->curr_anim = &(the_player->anim_damage_received_left);	
	
	if (the_player->curr_anim->Finished())
	{
		the_player->curr_anim->Reset();
		the_player->damaged = false;

		
		if (the_player->enemy_to_grab)
		{
			the_player->enemy_to_grab = false;
			((Garcia*)the_player->grabbed_enemy)->grabbed = false;
		}
	}
	
}
void PlayerFSM::KnockedDown()
{
	if (prev_state != State::KNOCKED_DOWN)
	{
		the_player->pos_before_knockdown = the_player->position;

		if (the_player->facing_right)
			the_player->curr_anim = &(the_player->anim_down_right);

		if (!the_player->facing_right)
			the_player->curr_anim = &(the_player->anim_down_left);
	}
	else 
	{
		//position offset
		iPoint temp = the_player->position;
		
		the_player->down_count++;
		if (the_player->down_count < the_player->down_frames)
		{
			if (the_player->facing_right)
			{
				if (the_player->down_count <= the_player->down_inflection)
				{
					temp.x -= the_player->speed;
					temp.y -= the_player->speed;
				}
				else
				{
					temp.x -= the_player->speed;
					temp.y += the_player->speed;
				}
			}
			if (!the_player->facing_right)
			{
				if (the_player->down_count <= the_player->down_inflection)
				{
					temp.x += the_player->speed;
					temp.y -= the_player->speed;
				}
				else
				{
					temp.x += the_player->speed;
					temp.y += the_player->speed;
				}
			}

			the_player->position = temp;
			
		}
		if (the_player->down_count == the_player->down_frames)
		{			
			the_player->up = true;
			the_player->curr_anim->Reset();
			UpdateColliderPosition();
		}
	
		//right animations
		if (the_player->curr_anim == &(the_player->anim_down_right))
		{
			if (the_player->up)
			{						
				if (the_player->curr_anim->Finished())
				{
					the_player->curr_anim->Reset();
					the_player->curr_anim = &(the_player->anim_ground_right1);
					the_player->up = false;					
				}				 
			}
		}
		else if (the_player->curr_anim == &(the_player->anim_ground_right1))
		{
			if (the_player->curr_anim->Finished())
			{
				the_player->curr_anim->Reset();
				the_player->curr_anim = &(the_player->anim_ground_right2);
			}
		}
		else if (the_player->curr_anim == &(the_player->anim_ground_right2))
		{
			if (the_player->curr_anim->Finished())
			{
				the_player->curr_anim->Reset();
				the_player->curr_anim = &(the_player->anim_up_right);
			}
		}
		else if (the_player->curr_anim == &(the_player->anim_up_right))
		{
			if (the_player->curr_anim->Finished())
			{
				the_player->curr_anim->Reset();
				the_player->knocked_down = false;
				the_player->down_count = 0;
				the_player->position.y = the_player->pos_before_knockdown.y;
				the_player->depth = the_player->position.y;
			}
		}

		//left animations
		if (the_player->curr_anim == &(the_player->anim_down_left))
		{
			if (the_player->up)
			{
				if (the_player->curr_anim->Finished())
				{
					the_player->curr_anim->Reset();
					the_player->curr_anim = &(the_player->anim_ground_left1);
					the_player->up = false;
				}				
			}
		}
		else if (the_player->curr_anim == &(the_player->anim_ground_left1))
		{
			if (the_player->curr_anim->Finished())
			{
				the_player->curr_anim->Reset();
				the_player->curr_anim = &(the_player->anim_ground_left2);
			}
		}
		else if (the_player->curr_anim == &(the_player->anim_ground_left2))
		{
			if (the_player->curr_anim->Finished())
			{
				the_player->curr_anim->Reset();
				the_player->curr_anim = &(the_player->anim_up_left);
			}
		}
		else if (the_player->curr_anim == &(the_player->anim_up_left))
		{
			if (the_player->curr_anim->Finished())
			{
				the_player->curr_anim->Reset();
				the_player->knocked_down = false;
				the_player->down_count = 0;
				the_player->position.y = the_player->pos_before_knockdown.y;
				the_player->depth = the_player->position.y;
			}
		}
	}
}

PlayerFSM::State PlayerFSM::GetCurrState() const
{
	return curr_state;
}

void PlayerFSM::SetCurrState(State state)
{	
		curr_state = state;	
}

void PlayerFSM::UpdateColliderPosition()
{
	if (the_player->facing_right)
	{
		the_player->body_collider->SetPos(the_player->position.x + the_player->body_collider_offset_right, the_player->position.y);
		the_player->hit_collider->SetPos(the_player->position.x + the_player->hit_collider_offset_right, the_player->position.y);
	}
	else
	{
		the_player->body_collider->SetPos(the_player->position.x + the_player->body_collider_offset_left, the_player->position.y);
		the_player->hit_collider->SetPos(the_player->position.x + the_player->hit_collider_offset_left, the_player->position.y);
	}
	
}

//------------------------------------- DESTRUCTOR ----------------------------
PlayerFSM::~PlayerFSM()
{

}

