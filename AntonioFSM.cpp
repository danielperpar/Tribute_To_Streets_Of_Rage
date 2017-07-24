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
		prev_state = curr_state;

		if (antonio->kick)
		{
			curr_state = State::KICK;
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
		if (antonio->player_in_sight)
		{
			curr_state = State::CHASE;
			break;
		}
		break;
	
	case State::CHASE:
		Chase();
		if (antonio->kick)
		{
			curr_state = State::KICK;
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
		Kick();
		if (antonio->kick == false)
		{			
			curr_state = State::IDLE;		
		}
		
		if (antonio->grabbed)
		{
			antonio->attack = false;
			curr_state = State::GRABBED;
			antonio->start_pos = antonio->position;
			break;
		}
		if (antonio->damaged)
		{
			antonio->kick = false;

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


	case State::KNOCKED_DOWN:
		KnockedDown();
		prev_state = curr_state;
		if (antonio->knocked_down == false)
		{
			if (antonio->life > 0)
				curr_state = State::IDLE;
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
						
			curr_state = State::IDLE;		
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

	case State::DEAD:
		Dead();
		break;
	}


}

void AntonioFSM::Idle()
{
	if (antonio->facing_right)
		antonio->curr_anim = &antonio->antonio_boomerang_idle_right;
	else
	{
		antonio->curr_anim = &antonio->antonio_boomerang_idle_left;

		if (antonio->offset_applied)
		{
			antonio->position.x -= antonio->offset_left_x1;
			antonio->offset_applied = false;
		}
	}
}

void AntonioFSM::Chase()
{

}

void AntonioFSM::Kick()
{
	//kick finished
	antonio->kick = false;
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
	{
		if (antonio->curr_anim != &antonio->antonio_grabbed_left)
		{
			antonio->curr_anim = &antonio->antonio_grabbed_left;
			antonio->position.x += antonio->offset_left_x1;
			antonio->offset_applied = true;
		}
		
	}
}

void AntonioFSM::GrabbedSecondStage()
{
	if (antonio->facing_right)
	{		
		antonio->curr_anim = &antonio->antonio_grabbed_finisher_right;
	}
	else
	{
		if (antonio->curr_anim != &antonio->antonio_grabbed_finisher_left)
		{
			antonio->curr_anim = &antonio->antonio_grabbed_finisher_left;
			antonio->position.x -= antonio->offset_left_x2;			
		}
	}
}

void AntonioFSM::GrabbedThirdStage()
{
	if (antonio->facing_right)
	{
		antonio->curr_anim = &antonio->antonio_grabbed_finisher_right;
		antonio->offset_applied = false; //reset flag
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
			antonio->curr_anim = &antonio->antonio_grabbed_finisher_horiz_right;
			antonio->offset_applied_2 = false; //reset flag
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
		antonio->curr_anim = &antonio->antonio_grabbed_finisher_vert_right;
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
		antonio->curr_anim = &antonio->antonio_grabbed_finisher_vert_right;
	}
	else
	{
		if (antonio->offset_applied_2 == false)
		{
			if (antonio->offset_applied_2 == false)
			{
				antonio->curr_anim = &antonio->antonio_grabbed_finisher_vert_left;
				antonio->position.x += antonio->offset_left_x6;
				antonio->position.y += antonio->offset_left_y6;
				antonio->offset_applied_2 = true;
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
	}
	else
	{
		antonio->curr_anim = &antonio->antonio_down_left2;
		antonio->position.y = antonio->start_pos.y;
	}
	antonio->knocked_down = true;
	antonio->body_collider->rect.w = antonio->body_collider_original;
}

void AntonioFSM::Damaged()
{

}

void AntonioFSM::KnockedDown()
{
	if (prev_state != State::KNOCKED_DOWN)
	{
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
						antonio->curr_anim = &(antonio->antonio_up_right);
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
					antonio->depth = antonio->position.y;
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
					antonio->depth = antonio->position.y;
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