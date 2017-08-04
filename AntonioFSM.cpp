#include "AntonioFSM.h"
#include "Antonio.h"
#include "Player.h"

//-------------------- test boomerang
#include "ModuleInput.h"
#include "Application.h"

AntonioFSM::AntonioFSM(Antonio *ant) : antonio(ant) 
{
	prev_state = State::START;
	curr_state = State::START;
}

AntonioFSM::~AntonioFSM() {}

void AntonioFSM::Update()
{

	//test recover boomerang
	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
	{
		antonio->recover_boomerang = true;
	}
//--------------------------------------------------

	switch (curr_state)
	{

	case State::START:
		Start();
		if (antonio->throw_boomerang)
		{
			curr_state = State::THROW_BOOMERANG;
			break;
		}
		break;

	case State::IDLE:
		Idle();	
		if (antonio->prekick)
		{
			prev_state = curr_state;
			curr_state = State::PRE_KICK;
			break;
		}
		if (antonio->recover_boomerang)
		{
			curr_state = State::RECOVER_BOOMERANG;
			break;
		}
		if (antonio->grabbed)
		{
			antonio->kick = false;
			curr_state = State::GRABBED;
			antonio->start_pos = antonio->position;
			break;
		}
		if (antonio->damaged)
		{
			prev_state = curr_state;

			if (antonio->life > 0)
				curr_state = State::DAMAGED;
			else
			{
				antonio->knocked_down = true;
				curr_state = State::KNOCKED_DOWN;
			}
			break;
		}
		if (antonio->knocked_down)
		{
			prev_state = curr_state;
			curr_state = State::KNOCKED_DOWN;
			break;
		}
		
		break;
	
	case State::CHASE:
		Chase();
		if (antonio->prekick)
		{
			antonio->chase_counter = 0;
			prev_state = curr_state;
			curr_state = State::PRE_KICK;
			break;
		}
		if (antonio->grabbed)
		{
			antonio->chase_counter = 0;
			antonio->kick = false;
			curr_state = State::GRABBED;
			antonio->start_pos = antonio->position;
			break;
		}
		if (antonio->damaged)
		{
			antonio->chase_counter = 0;
			prev_state = curr_state;

			if (antonio->life > 0)
				curr_state = State::DAMAGED;
			else
			{
				antonio->knocked_down = true;
				curr_state = State::KNOCKED_DOWN;
			}
			break;
		}
		if (antonio->knocked_down)
		{
			antonio->chase_counter = 0;
			prev_state = curr_state;
			curr_state = State::KNOCKED_DOWN;
			break;
		}

		antonio->chase_counter++;
		if (antonio->chase_counter == antonio->chase_time_out)
		{
			antonio->chase_counter = 0;
			curr_state = State::CAST;
		}
		break;

	case State::CAST:
		MoveToCastPosition();
		if (antonio->throw_boomerang)
		{
			curr_state = State::THROW_BOOMERANG;
			break;
		}
		if (antonio->damaged)
		{
			prev_state = curr_state;

			if (antonio->life > 0)
				curr_state = State::DAMAGED;
			else
			{
				antonio->knocked_down = true;
				curr_state = State::KNOCKED_DOWN;
			}
			break;
		}
		if (antonio->knocked_down)
		{
			prev_state = curr_state;
			curr_state = State::KNOCKED_DOWN;
			break;
		}
		break;
	case State::PRE_KICK:
		PreKick();
		if (antonio->kick)
		{
			curr_state = State::KICK;
			break;
		}
		if (antonio->grabbed)
		{			
			curr_state = State::GRABBED;
			antonio->start_pos = antonio->position;
			break;
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
			break;
		}
		if (antonio->knocked_down)
		{
			curr_state = State::KNOCKED_DOWN;
			break;
		}
		break;
	case State::KICK:
		if (antonio->grabbed)
		{
			curr_state = State::GRABBED;
			antonio->start_pos = antonio->position;
			antonio->kick = false;
			break;
		}
		if (antonio->kick == false)
		{								
			if (prev_state == State::IDLE)
			{
				curr_state = State::IDLE;
				if (antonio->facing_right)
					antonio->curr_anim = &antonio->antonio_idle_right;
				else
					antonio->curr_anim = &antonio->antonio_idle_left;

				break;
			}
			else if(prev_state == State::CHASE)
			{
				curr_state = State::CAST;
				if (antonio->facing_right)
					antonio->curr_anim = &antonio->antonio_boomerang_walk_right;
				else
					antonio->curr_anim = &antonio->antonio_boomerang_walk_left;
				break;
			}				
		}
		Kick();
		break;

	case State::DAMAGED:
		Damaged();
		if (antonio->damaged == false)
		{
			if (antonio->life > 0)
			{				
				switch (prev_state)
				{
				case State::IDLE:
					curr_state = State::IDLE;
					break;
				case State::CHASE:
					curr_state = State::CHASE;
					break;
				case State::CAST:
					curr_state = State::CAST;
					break;
				case State::GRABBED:
					curr_state = State::GRABBED;					
					break;
				}
			}
			else
			{
				antonio->knocked_down = true;
				curr_state = State::KNOCKED_DOWN;
				break;
			}
		}
		break;
	case State::KNOCKED_DOWN:
		KnockedDown();
		if (antonio->knocked_down == false)
		{
			if (antonio->life > 0)
			{
				switch (prev_state)
				{
				case State::IDLE:
					curr_state = State::IDLE;
					break;
				case State::CHASE:
					curr_state = State::CHASE;
					break;
				case State::CAST:
					curr_state = State::CAST;
					break;
				case State::GRABBED:
					curr_state = State::CAST;
					break;
				}
			}
			else
				curr_state = State::DEAD;
		}
		break;

	case State::GRABBED:
		Grabbed();
		if (!antonio->grabbed)
		{
			if (antonio->facing_right)
			{
				antonio->curr_anim = &(antonio->antonio_boomerang_idle_right);
			}
			else
			{
				antonio->curr_anim = &(antonio->antonio_boomerang_idle_left);				
			}
						
			curr_state = State::CHASE;		
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

	case State::THROW_BOOMERANG:
		ThrowBoomerang();
		if (antonio->throw_boomerang == false)
		{
			curr_state = State::IDLE;
			break;
		}
		break;

	case State::RECOVER_BOOMERANG:
		RecoverBoomerang();
		if (antonio->recover_boomerang == false)
		{
			curr_state = State::CHASE;
			break;
		}
		break;

	case State::DEAD:
		Dead();
		break;
	}
}

void AntonioFSM::Start()
{
	//facing left by default

	antonio->position.x -= antonio->speed_vect.x;
	if (antonio->position.x == antonio->cast_right.x)
		antonio->throw_boomerang = true;

	antonio->curr_anim = &antonio->antonio_boomerang_walk_left;

	UpdateColliderPosition();
}

void AntonioFSM::Idle()
{
	if (antonio->facing_right)
	{
		if (antonio->curr_anim != &antonio->antonio_idle_right)
		{
			antonio->curr_anim->Reset();
			antonio->curr_anim = &antonio->antonio_idle_right;
		}

		if (antonio->offset_applied)
		{
			antonio->position.x += antonio->offset_right_x1;
			antonio->position.y -= antonio->offset_right_y1;
			antonio->offset_applied = false;
		}
	}
	else
	{
		if (antonio->curr_anim != &antonio->antonio_idle_left)
		{
			antonio->curr_anim->Reset();
			antonio->curr_anim = &antonio->antonio_idle_left;
		}

		if (antonio->offset_applied)
		{
			antonio->position.x -= antonio->offset_left_x1;
			antonio->position.y -= antonio->offset_left_y1;
			antonio->offset_applied = false;
		}
	}
	
}

void AntonioFSM::Chase()
{
	iPoint target;

	target.x = antonio->the_player->position.x - antonio->position.x;
	target.y = antonio->the_player->depth - antonio->ref_y - 1 - antonio->position.y; //one pixel behind the player for right draw order when the player grabs Antonio

	int direction_x = 0;
	int direction_y = 0;

	if (target.x > 0)
	{
		direction_x = 1;
		if (!antonio->facing_right)
			antonio->facing_right = true;
	}

	if (target.x < 0)
	{
		direction_x = -1;
		if (antonio->facing_right)
			antonio->facing_right = false;
	}

	if (target.y > 0)
		direction_y = 1;

	if (target.y < 0)
		direction_y = -1;


	antonio->position += {direction_x * antonio->speed_vect.x, direction_y * antonio->speed_vect.y};
	antonio->depth = antonio->position.y + antonio->ref_y;
	UpdateColliderPosition();

	//set animations

	if (!antonio->facing_right)
	{
		if (antonio->curr_anim != &(antonio->antonio_boomerang_walk_left))
		{
			antonio->curr_anim = &(antonio->antonio_boomerang_walk_left);
			antonio->curr_anim->Reset();
		}
	}

	if (antonio->facing_right)
	{
		if (antonio->curr_anim != &(antonio->antonio_boomerang_walk_right))
		{
			antonio->curr_anim = &(antonio->antonio_boomerang_walk_right);
			antonio->curr_anim->Reset();
		}
	}
}

void AntonioFSM::MoveToCastPosition()
{
	
	if (antonio->the_player->position.x >= antonio->position.x)
	{
		if (!antonio->facing_right)
			antonio->facing_right = true;
	}
	else
	{
		if (antonio->facing_right)
			antonio->facing_right = false;
	}

	//animations
	if (antonio->facing_right)
		antonio->curr_anim = &antonio->antonio_boomerang_walk_right;
	else
		antonio->curr_anim = &antonio->antonio_boomerang_walk_left;

	//compute distances from antonio to casting points
	int sign_right_x = 1;
	int sign_right_y = 1;

	int sign_left_x = 1;
	int sign_left_y = 1;

	int dist_right_x = antonio->cast_right.x - antonio->position.x;
	if (dist_right_x < 0)
	{
		dist_right_x = -dist_right_x;
		sign_right_x = -1;
	}

	int dist_right_y = antonio->cast_right.y - antonio->position.y;
	if (dist_right_y < 0)
	{
		sign_right_y = -1;
	}
	else if (dist_right_y == 0)
	{
		sign_right_y = 0;
	}

	int dist_left_x = antonio->position.x - antonio->cast_left.x;
	if (dist_left_x < 0)
	{
		dist_left_x = -dist_left_x;
	}
	else
		sign_left_x = -1;

	int dist_left_y = antonio->position.y - antonio->cast_left.y;
	if (dist_left_y > 0)
	{
		sign_left_y = -1;
	}
	else if (dist_left_y == 0)
	{
		sign_left_y = 0;
	}

	//antonio closer to the left casting point
	if (dist_left_x < dist_right_x)
	{
		antonio->position.x += sign_left_x * antonio->speed_vect.x;
		antonio->position.y += sign_left_y * antonio->speed_vect.y;
		antonio->depth += sign_left_y * antonio->speed_vect.y;

		if (antonio->position.x == antonio->cast_left.x)
		{
			antonio->throw_boomerang = true;
		}

	}
	else //antonio closer to the right casting point
	{
		antonio->position.x += sign_right_x * antonio->speed_vect.x;
		antonio->position.y += sign_right_y * antonio->speed_vect.y;
		antonio->depth += sign_right_y * antonio->speed_vect.y;

		if (antonio->position.x == antonio->cast_right.x)
		{
			antonio->throw_boomerang = true;
		}
	}

	UpdateColliderPosition();
}

void AntonioFSM::PreKick()
{
	if (prev_state == State::IDLE)
	{
		if (antonio->facing_right)
			antonio->curr_anim = &antonio->antonio_idle_right;
		else
			antonio->curr_anim = &antonio->antonio_idle_left;
	}
	else if (prev_state == State::CHASE)
	{
		if (antonio->facing_right)
			antonio->curr_anim = &antonio->antonio_boomerang_idle_right;
		else
			antonio->curr_anim = &antonio->antonio_boomerang_idle_left;
	}

	if (antonio->curr_anim->Finished())
	{
		antonio->prekick_counter++;
		if (antonio->prekick_counter == antonio->prekick_frames)
		{			
			antonio->prekick_counter = 0;			
			antonio->kick = true;
		}
	}
}

void AntonioFSM::Kick()
{
	//kick finished
	if (antonio->facing_right && antonio->kick)
	{
		antonio->curr_anim = &antonio->antonio_kick_right;		
	}
	else if(!antonio->facing_right && antonio->kick)
	{
		antonio->curr_anim = &antonio->antonio_kick_left;		
	}

	if (antonio->curr_anim->Finished())
	{			
		antonio->curr_anim->Reset();		
		if (antonio->prekick)
		{
			antonio->the_player->knocked_down = true;
		}
		antonio->kick = false;

		if (prev_state == State::IDLE)
		{
			if (antonio->facing_right)
				antonio->curr_anim = &antonio->antonio_idle_right;
			else
				antonio->curr_anim = &antonio->antonio_idle_left;
		}
		else if (prev_state == State::CHASE)
		{
			if (antonio->facing_right)
				antonio->curr_anim = &antonio->antonio_boomerang_idle_right;
			else
				antonio->curr_anim = &antonio->antonio_boomerang_idle_left;
		}
	}
}

void AntonioFSM::ThrowBoomerang()
{
	if (antonio->facing_right)
		antonio->curr_anim = &antonio->antonio_throw_boomerang_right;
	else
		antonio->curr_anim = &antonio->antonio_throw_boomerang_left;

	if (antonio->curr_anim->Finished())
	{
		antonio->curr_anim->Reset();
		antonio->throw_boomerang = false;

		if (antonio->facing_right)
			antonio->curr_anim = &antonio->antonio_idle_right;
		else
			antonio->curr_anim = &antonio->antonio_idle_left;
	}

}

void AntonioFSM::RecoverBoomerang()
{
	if (antonio->facing_right)
		antonio->curr_anim = &antonio->antonio_recover_boomerang_right;
	else
		antonio->curr_anim = &antonio->antonio_recover_boomerang_left;

	if (antonio->curr_anim->Finished())
	{
		antonio->curr_anim->Reset();
		antonio->recover_boomerang = false;
	}
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
	{
		if (antonio->curr_anim != &antonio->antonio_grabbed_right)
		{	
			//in case player is comming from reverse air sommersault, position offsets must be erased
			antonio->position = antonio->start_pos; 
			antonio->curr_anim = &antonio->antonio_grabbed_right;
			antonio->position.x -= antonio->offset_right_x1;
			antonio->position.y += antonio->offset_right_y1;
			antonio->offset_applied = true;			
		}
	}
	else
	{
		if (antonio->curr_anim != &antonio->antonio_grabbed_left)
		{	
			antonio->position = antonio->start_pos; //in case player is comming from reverse air sommersault, position offsets must be undone
			antonio->curr_anim = &antonio->antonio_grabbed_left;
			antonio->position.x += antonio->offset_left_x1;
			antonio->position.y += antonio->offset_left_y1;
			antonio->offset_applied = true;			
		}
		
	}
}

void AntonioFSM::GrabbedSecondStage()
{
	if (antonio->facing_right)
	{
		if(antonio->curr_anim != &antonio->antonio_grabbed_finisher_right)
		{
			antonio->curr_anim = &antonio->antonio_grabbed_finisher_right;
			antonio->position.x += antonio->offset_right_x2;
			antonio->position.y += antonio->offset_right_y2;
		}
	}
	else
	{
		if (antonio->curr_anim != &antonio->antonio_grabbed_finisher_left)
		{
			antonio->curr_anim = &antonio->antonio_grabbed_finisher_left;
			antonio->position.x -= antonio->offset_left_x2;
			antonio->position.y += antonio->offset_left_y2;
		}
	}
}

void AntonioFSM::GrabbedThirdStage()
{
	if (antonio->facing_right)
	{
		if (antonio->offset_applied_2 == false)
		{
			antonio->offset_applied = false; //reset flag
			antonio->curr_anim = &antonio->antonio_grabbed_finisher_right;
			antonio->position.x -= antonio->offset_right_x3;
			antonio->offset_applied_2 = true;
		}
	}
	else
	{
		if (antonio->offset_applied_2 == false)
		{
			antonio->offset_applied = false; //reset flag
			antonio->curr_anim = &antonio->antonio_grabbed_finisher_left;
			antonio->position.x += antonio->offset_left_x3;
			antonio->offset_applied_2 = true;
		}
	}
}

void AntonioFSM::GrabbedFourthStage()
{
	if (antonio->facing_right)
	{
		if(antonio->curr_anim != &antonio->antonio_grabbed_finisher_horiz_right)
		{
			antonio->offset_applied_2 = false; //reset flag
			antonio->curr_anim = &antonio->antonio_grabbed_finisher_horiz_right;
			antonio->position.x += antonio->offset_right_x4;
			antonio->position.y += antonio->offset_right_y4;
		}
	}
	else
	{
		if (antonio->curr_anim != &antonio->antonio_grabbed_finisher_horiz_left)
		{
			antonio->offset_applied_2 = false; //reset flag
			antonio->curr_anim = &antonio->antonio_grabbed_finisher_horiz_left;
			antonio->position.x += antonio->offset_left_x4;
			antonio->position.y += antonio->offset_left_y4;
		}
	}
}

void AntonioFSM::GrabbedFifthStage()
{
	if (antonio->facing_right)
	{
		if (antonio->offset_applied == false)
		{
			antonio->curr_anim = &antonio->antonio_grabbed_finisher_vert_right;
			antonio->position.x -= antonio->offset_right_x5;
			antonio->offset_applied = true;
		}
	}
	else
	{
		if (antonio->offset_applied == false)
		{
			if (antonio->offset_applied == false)
			{
				antonio->curr_anim = &antonio->antonio_grabbed_finisher_vert_left;
				antonio->position.x += antonio->offset_left_x5;
				antonio->position.y -= antonio->offset_left_y5;
				antonio->offset_applied = true;
			}
		}
	}
}

void AntonioFSM::GrabbedSixthStage()
{
	if (antonio->facing_right)
	{
		if (antonio->offset_applied_2 == false)
		{
			antonio->curr_anim->Reset();
			antonio->curr_anim = &antonio->antonio_grabbed_finisher_vert_right;
			antonio->position.x -= antonio->offset_left_x6;
			antonio->position.y += antonio->offset_left_y6;
			antonio->offset_applied_2 = true;
			antonio->offset_applied = false; //reset flag
		}
	}
	else
	{
		if (antonio->offset_applied_2 == false)
		{
			if (antonio->offset_applied_2 == false)
			{
				antonio->curr_anim->Reset();
				antonio->curr_anim = &antonio->antonio_grabbed_finisher_vert_left;
				antonio->position.x += antonio->offset_left_x6;
				antonio->position.y += antonio->offset_left_y6;
				antonio->offset_applied_2 = true;
				antonio->offset_applied = false; //reset flag
			}
		}
	}

	if (antonio->curr_anim->Finished())
	{
		grab_stage = GrabStage::SEVENTH_DOWN_STAGE;
		antonio->offset_applied_2 = false;
	}
}

void AntonioFSM::GrabbedSeventhDownStage()
{
	if (antonio->facing_right)
	{
		antonio->curr_anim = &antonio->antonio_down_right2;
		antonio->position.x -= antonio->offset_right_x7;
		antonio->position.y = antonio->start_pos.y;
		if (antonio->body_coll_adjustment_made)
		{
			antonio->body_collider->rect.x += antonio->body_collider_adjusted_x;
			antonio->body_coll_adjustment_made = false;
		}
	}
	else
	{
		antonio->curr_anim = &antonio->antonio_down_left2;
		antonio->position.y = antonio->start_pos.y;
		antonio->body_collider->rect.w = antonio->body_collider_original;
	}
	antonio->knocked_down = true;
	
}

void AntonioFSM::Damaged()
{
	if (antonio->facing_right)
		antonio->curr_anim = &antonio->antonio_damaged_right;
	else
		antonio->curr_anim = &antonio->antonio_damaged_left;

	if (antonio->curr_anim->Finished())
	{
		antonio->curr_anim->Reset();
		antonio->damaged = false;
	}
}

void AntonioFSM::KnockedDown()
{
	if (antonio->entered_knocked_down == false)
	{
		antonio->entered_knocked_down = true;
		antonio->pos_before_knockdown = antonio->position;

		if (antonio->facing_right)
			antonio->curr_anim = &(antonio->antonio_down_right1);

		if (!antonio->facing_right)
			antonio->curr_anim = &(antonio->antonio_down_left1);
	}
	else
	{
		//position offset
		iPoint temp = antonio->position;

		antonio->down_count++;
		if (antonio->down_count < antonio->down_frames)
		{
			if (antonio->facing_right)
			{
				if (antonio->down_count <= antonio->down_inflection)
				{
					temp.x -= 2 * antonio->speed;
					temp.y -= antonio->speed;
				}
				else
				{
					temp.x -= 2 * antonio->speed;
					temp.y += antonio->speed;
				}
			}
			if (!antonio->facing_right)
			{
				if (antonio->down_count <= antonio->down_inflection)
				{
					temp.x += 2 * antonio->speed;
					temp.y -= antonio->speed;
				}
				else
				{
					temp.x += 2 * antonio->speed;
					temp.y += antonio->speed;
				}
			}

			antonio->position = temp;
			UpdateColliderPosition();
		}
		if (antonio->down_count == antonio->down_frames)
		{
			antonio->up = true;
			antonio->curr_anim->Reset();			
		}

		if (antonio->up)
		{
			//right animations
			if (antonio->curr_anim == &(antonio->antonio_down_right1))
			{
				antonio->curr_anim->Reset();
				antonio->curr_anim = &(antonio->antonio_down_right2);
			}
			else if (antonio->curr_anim == &(antonio->antonio_down_right2))
			{
				if (antonio->curr_anim->Finished())
				{
					antonio->curr_anim->Reset();

					if (antonio->life > 0)
					{
						antonio->curr_anim = &(antonio->antonio_up_right);												
					}
					else
						antonio->knocked_down = false;

				}
			}
			else if (antonio->curr_anim == &(antonio->antonio_up_right))		
			{
				if (antonio->curr_anim->Finished())
				{					
					antonio->curr_anim->Reset();
					antonio->knocked_down = false;
					antonio->up = false;
					antonio->down_count = 0;
					antonio->position.y = antonio->pos_before_knockdown.y;					
					antonio->depth = antonio->position.y + antonio->ref_y;
					antonio->entered_knocked_down = false;
				}
			}

			//left animations
			if (antonio->curr_anim == &(antonio->antonio_down_left1))
			{
				antonio->curr_anim->Reset();
				antonio->curr_anim = &(antonio->antonio_down_left2);
			}
			else if (antonio->curr_anim == &(antonio->antonio_down_left2))
			{
				if (antonio->curr_anim->Finished())
				{
					antonio->curr_anim->Reset();

					if (antonio->life > 0)
						antonio->curr_anim = &(antonio->antonio_up_left);
					else
						antonio->knocked_down = false;
				}
			}
			else if (antonio->curr_anim == &(antonio->antonio_up_left))
			{
				if (antonio->curr_anim->Finished())
				{
					antonio->curr_anim->Reset();
					antonio->knocked_down = false;
					antonio->up = false;
					antonio->down_count = 0;
					antonio->position.y = antonio->pos_before_knockdown.y;
					antonio->depth = antonio->position.y + antonio->ref_y;
					antonio->entered_knocked_down = false;
				}
			}
		}
	}
}

void AntonioFSM::Dead()
{
	//Mark colliders as deleteable
	if (antonio->body_collider != nullptr)
		antonio->body_collider->to_delete = true;

	if (antonio->hit_collider != nullptr)
		antonio->hit_collider->to_delete = true;

	if (antonio->facing_right)
	{
		if (antonio->blink)
			antonio->curr_anim = &antonio->antonio_dead_blink_effect;
		else
			antonio->curr_anim = &antonio->antonio_down_right2;
	}
	else
	{
		if (antonio->blink)
			antonio->curr_anim = &antonio->antonio_dead_blink_effect;
		else
			antonio->curr_anim = &antonio->antonio_down_left2;
	}

	antonio->blink_counter++;
	if (antonio->blink_counter == antonio->blink_wait_frames)
	{
		antonio->blink_counter = 0;
		antonio->blink = !antonio->blink;
		antonio->blink_times_counter++;
		if (antonio->blink_times_counter > antonio->blink_max_times)
		{
			//destroy de entity
			antonio->destroy_this = true;
		}
	}
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