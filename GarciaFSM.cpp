#include "GarciaFSM.h"
#include "Garcia.h"
#include "Player.h"
#include "Point.h"
#include "Application.h"
#include "ModuleSceneRound1.h"

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
		if (garcia->grabbed)
		{
			garcia->attack = false;
			curr_state = State::GRABBED;
			break;
		}
		break;

	case State::ATTACK:
		Attack();
		if (garcia->attack == false)
		{
			garcia->punch_hits = 0;
			curr_state = State::CHASE;
		}
		if (garcia->evasive)
		{
			garcia->punch_hits = 0;
			garcia->evasive_started_facing_right = garcia->facing_right;
			if ((garcia->position.y - garcia->evasive_v_offset) <= App->scene_round1->upper_limit)
			{
				evasion_upper = false;
				evasion_lower = true;
			}
			else if ((garcia->position.y + garcia->evasive_v_offset) >= App->scene_round1->lower_limit)
			{
				evasion_upper = true;
				evasion_lower = false;
			}
			else
			{
				evasion_upper = true;
				evasion_lower = false;
			}
			curr_state = State::EVASIVE;			
		}
		if (garcia->grabbed)
		{
			garcia->attack = false;

			// reset evasive state in case the enemy is grabbed while in evasive state
			garcia->evasive = false;
			evasive_v_count = 0;
			garcia->punch_hits = 0;
			curr_state = State::GRABBED;
			break;
		}
		break;

	case State::EVASIVE:
		Evasive();
		if (garcia->evasive == false)
		{
			curr_state = State::CHASE;
		}
		break;

	case State::DAMAGED:
		break;

	case State::KNOCKED_DOWN:
		break;

	case State::GRABBED:
		Grabbed();
		if (!garcia->grabbed)
		{
			if (garcia->facing_right)
			{
				garcia->curr_anim = &(garcia->garcia_idle_right);
			}
			else
			{
				garcia->curr_anim = &(garcia->garcia_idle_left);
			}
			frames_counter++;
			if (frames_counter >= num_frames)
			{
				frames_counter = 0;
				curr_state = State::CHASE;
			}
		}
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

			if (garcia->curr_anim->GetCurrentFrameCount() == 1)
			{
				garcia->the_player->damaged = true;	//Damage the player	
				garcia->the_player->enemy_attacker = garcia;	//enemy to react to
			}
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

			if (garcia->curr_anim->GetCurrentFrameCount() == 1)
			{
				garcia->the_player->knocked_down = true;	//Knock down the player
				garcia->the_player->enemy_attacker = garcia;	//enemy to react to
			}

			if (garcia->curr_anim->Finished())
			{			
				garcia->punch_hits++;
				garcia->evasive = true;
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
			
			if (garcia->curr_anim->GetCurrentFrameCount() == 1)
			{
				garcia->the_player->damaged = true;	//Damage the player	
				garcia->the_player->enemy_attacker = garcia;	//enemy to react to
			}

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

			if (garcia->curr_anim->GetCurrentFrameCount() == 1)
			{
				garcia->the_player->knocked_down = true;	//Knock down the player 
				garcia->the_player->enemy_attacker = garcia;	//enemy to react to
			}

			if (garcia->curr_anim->Finished())
			{				
				garcia->punch_hits++;
				garcia->evasive = true;
			}
		}

		if (garcia->punch_hits == 3)
			garcia->punch_hits = 0;
	}
}
void GarciaFSM::Evasive()
{
	switch (evasive_movement)
	{
	case EvasiveMovement::FIRST_STAGE:
		EvasiveFirstStage();
		break;

	case EvasiveMovement::SECOND_STAGE:
		EvasiveSecondStage();
		break;

	case EvasiveMovement::THIRD_STAGE:
		EvasiveThirdStage();
		break;
	}
}

void GarciaFSM::EvasiveFirstStage()
{
	if (evasive_v_count < garcia->evasive_v_offset)
	{
		if (evasive_go)
		{
			if (evasion_upper)
			{
				iPoint temp = garcia->position;
				temp.y -= garcia->speed;
				garcia->position = temp;
				garcia->depth = temp.y;
				evasive_v_count++;
			}
			if (evasion_lower)
			{
				iPoint temp = garcia->position;
				temp.y += garcia->speed;
				garcia->position = temp;
				garcia->depth = temp.y;
				evasive_v_count++;
			}
		}
		if (evasive_back)
		{
			if (evasion_upper)
			{
				iPoint temp = garcia->position;
				temp.y += garcia->speed;
				garcia->position = temp;
				garcia->depth = temp.y;
				evasive_v_count++;
			}
			if (evasion_lower)
			{
				iPoint temp = garcia->position;
				temp.y -= garcia->speed;
				garcia->position = temp;
				garcia->depth = temp.y;
				evasive_v_count++;
			}
		}

		//set animation
		if (garcia->facing_right)
		{
			if (garcia->curr_anim != &garcia->garcia_walk_right)
			{
				garcia->curr_anim = &garcia->garcia_walk_right;
				garcia->curr_anim->Reset();
			}
		}
		else
		{
			if (garcia->curr_anim != &garcia->garcia_walk_left)
			{
				garcia->curr_anim = &garcia->garcia_walk_left;
				garcia->curr_anim->Reset();
			}
		}
	}
	else
	{
		evasive_v_count = 0;

		if(evasive_go)
			evasive_movement = EvasiveMovement::SECOND_STAGE;
		if (evasive_back)
		{
			curr_state = State::CHASE;
			evasive_back = false;
			evasive_go = true;
			garcia->evasive = false;
		}
	}

	UpdateColliderPosition();
}

void GarciaFSM::EvasiveSecondStage()
{
	if (evasive_h_count < garcia->evasive_h_offset)
	{
		if (evasive_go)
		{
			if (garcia->evasive_started_facing_right)
			{
				iPoint temp = garcia->position;
				temp.x += garcia->speed;
				garcia->position = temp;
				evasive_h_count++;
			}
			else 
			{
				iPoint temp = garcia->position;
				temp.x -= garcia->speed;
				garcia->position = temp;				
				evasive_h_count++;
			}
		}
		else if (evasive_back)
		{
			if (garcia->evasive_started_facing_right)
			{
				iPoint temp = garcia->position;
				temp.x -= garcia->speed;
				garcia->position = temp;
				evasive_h_count++;
			}
			else
			{
				iPoint temp = garcia->position;
				temp.x += garcia->speed;
				garcia->position = temp;
				evasive_h_count++;
			}
		}

		//set enemy facing right or left
		int target_x = garcia->the_player->position.x - garcia->position.x;

		if (target_x >= 0)
			garcia->facing_right = true;
		else
			garcia->facing_right = false;

		//set animation
		if (garcia->facing_right)
		{
			if (garcia->curr_anim != &garcia->garcia_walk_right)
			{
				garcia->curr_anim = &garcia->garcia_walk_right;
				garcia->curr_anim->Reset();
			}
		}
		else
		{
			if (garcia->curr_anim != &garcia->garcia_walk_left)
			{
				garcia->curr_anim = &garcia->garcia_walk_left;
				garcia->curr_anim->Reset();
			}
		}
	}
	else
	{
		evasive_h_count = 0;
		if (evasive_go)
			evasive_movement = EvasiveMovement::THIRD_STAGE;
		if (evasive_back)
			evasive_movement = EvasiveMovement::FIRST_STAGE;
	}

	UpdateColliderPosition();
}

void GarciaFSM::EvasiveThirdStage()
{
	if (evasive_v_count < garcia->evasive_v_offset)
	{
		if (evasive_go)
		{
			if (garcia->evasive_started_facing_right)
				garcia->position.x -= garcia->speed;
			else
				garcia->position.x += garcia->speed;

			if(evasion_upper)
				garcia->position.y += garcia->speed;
			if(evasion_lower)
				garcia->position.y -= garcia->speed;

			evasive_v_count++;
		}
		if (evasive_back)
		{
			if (garcia->evasive_started_facing_right)
				garcia->position.x += garcia->speed;
			else
				garcia->position.x -= garcia->speed;

			if(evasion_upper)
				garcia->position.y -= garcia->speed;
			if(evasion_lower)
				garcia->position.y += garcia->speed;

			evasive_v_count++;
		}
	}
	else
	{
		if (evasive_go)
		{
			evasive_go = false;
			evasive_back = true;
		}
		else if (evasive_back)
		{
			evasive_movement = EvasiveMovement::SECOND_STAGE;
		}
		
		evasive_v_count = 0;
	}

	UpdateColliderPosition();
}

void GarciaFSM::Grabbed()
{
	if (garcia->facing_right)
		garcia->curr_anim = &garcia->garcia_grabbed_right;
	else
		garcia->curr_anim = &garcia->garcia_grabbed_left;
}

//---------------------------------------------------------------------------------------------------------------------------


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