#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "EntityManager.h"
#include "Entity.h"


ModulePlayer::ModulePlayer(bool active) : Module(active) {}


ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("assets/spritesheets/axel.png");

	//Debug test
	player = (Player*)EntityManager::CreateEntity(graphics, "Axel", entity_type::PLAYER, { 800, 100 }, 0);
	player->m_state = player_state::IDLE;


	/*SDL_Rect colliderRect = SDL_Rect();
	colliderRect.x = 0;
	colliderRect.y = 0;
	colliderRect.w = 32;
	colliderRect.h = 14;
	playerCollider = App->collision->AddCollider(colliderRect, nullptr, collider_type::PLAYER);
	playerCollider->SetPos(position.x, position.y);*/

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		//position.x -= speed;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		if ((player->m_state == player_state::IDLE || player->m_state == player_state::WALKING) && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE)
		{
			player->m_state = player_state::JUMPING;
			player->m_jump_up = true;
			player->m_jump_start_pos = player->m_position;
			player->m_timer_count = 0.0f;
			player->m_restart_animation = true;
			player->m_jumping = true;
			player->m_speed = 2.0f;
		}
	}

	if (player->m_state == player_state::JUMPING)
	{

		if (player->m_restart_animation)
		{
			if (player->m_face_right)
				player->m_current_animation = &(player->m_jump_right1);
			else
				player->m_current_animation = &(player->m_jump_left1);

			player->m_restart_animation = false;
		}

		if (player->m_jump_up)
		{
			player->m_position.y = (int)(player->m_position.y - player->m_jump_speed);
			if (player->m_jump_start_pos.y - player->m_position.y >= player->m_max_jump_height)
				player->m_jump_up = false;
		}
		else
		{
			player->m_position.y = (int)(player->m_position.y + player->m_jump_speed);	
		}

		if (player->m_jump_start_pos.y - player->m_position.y <= 0)
		{
			player->m_position.y = player->m_jump_start_pos.y;
			player->m_jumping = false;
		}

		if (player->m_jumping)
		{
			if (player->m_face_right)
				player->AdvanceAnimation(player->m_jump1_duration, &(player->m_jump_right2), false);
			else
				player->AdvanceAnimation(player->m_jump1_duration, &(player->m_jump_left2), false);
		}

		if (!player->m_jumping)
		{
		
			if (player->m_current_animation == &(player->m_jump_right2))
			{
				player->m_current_animation = &(player->m_jump_right1);
			}
			if (player->m_current_animation == &(player->m_jump_right1))
			{
				player->AdvanceAnimation(player->m_jump1_duration, &(player->m_idle_right1), false);
			}

			if (player->m_current_animation == &(player->m_jump_left2))
			{
				player->m_current_animation = &(player->m_jump_left1);
			}
			if (player->m_current_animation == &(player->m_jump_left1))
			{
				player->AdvanceAnimation(player->m_jump1_duration, &(player->m_idle_left1), false);
			}
			
		}

		if (player->m_current_animation == &(player->m_idle_right1))
		{
			player->m_restart_animation = true;
			player->m_speed = 1.0f;
			player->m_state = player_state::IDLE;
		}
		if (player->m_current_animation == &(player->m_idle_left1))
		{
			player->m_restart_animation = true;
			player->m_speed = 1.0f;
			player->m_state = player_state::IDLE;
		}


		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && player->m_jumping)
		{
			player->m_state = player_state::JUMPING_KICKING;
		}
	
	}

	if (player->m_state == player_state::JUMPING_KICKING)
	{
		if (player->m_jump_up)
		{
			player->m_position.y = (int)(player->m_position.y - player->m_jump_speed);
			if (player->m_jump_start_pos.y - player->m_position.y >= player->m_max_jump_height)
				player->m_jump_up = false;
		}
		else
		{
			player->m_position.y = (int)(player->m_position.y + player->m_jump_speed);
		}

		if (player->m_jump_start_pos.y - player->m_position.y <= 0)
		{
			player->m_position.y = player->m_jump_start_pos.y;
			player->m_jumping = false;
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && player->m_jumping == true)
		{
			if (player->m_face_right == true)
				player->m_current_animation = &(player->m_air_kick_right);
			else
				player->m_current_animation = &(player->m_air_kick_left);
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_UP || !player->m_jumping)
		{
			if (player->m_face_right)
				player->m_current_animation = &(player->m_jump_right2);
			else
				player->m_current_animation = &(player->m_jump_left2);
			
			player->m_state = player_state::JUMPING;
		}
	}


	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{

		switch (player->m_state)
		{
		case player_state::IDLE : 
			player->m_state = player_state::PUNCHING_COMBO_1;
			break;

		case player_state::PUNCHING_COMBO_1 :
			if (player->m_enemy_alive)
				player->m_state = player->m_continue_combo && player->m_upper_punch_hits == 2 ? player_state::PUNCHING_COMBO_2 : player_state::PUNCHING_COMBO_1;
			else
				player->m_state = player_state::IDLE;
			
			break;

		case player_state::PUNCHING_COMBO_2:
			if (player->m_enemy_alive)
				player->m_state = player->m_continue_combo ? player_state::PUNCHING_COMBO_3 : player_state::PUNCHING_COMBO_2;
			else
				player->m_state = player_state::IDLE;
			
			break;
		
		case player_state::WEAPON_PIPE_IDLE:
			if (player->m_face_right)
			{
				player->m_state = player_state::WEAPON_PIPE_ATTACK_RIGHT;
			}
			else
			{
				player->m_state = player_state::WEAPON_PIPE_ATTACK_LEFT;	
			}
			break;

		case player_state::WEAPON_KNIFE_IDLE:
			if (player->m_face_right)
			{
				player->m_state = player_state::WEAPON_KNIFE_ATTACK_RIGHT;
			}
			else
			{
				player->m_state = player_state::WEAPON_KNIFE_ATTACK_LEFT;
			}
			break;
		}

		player->m_restart_animation = true;
		player->m_timer_count = 0.0f;
		
		if (player->m_upper_punch_hits == 2)
			player->m_upper_punch_hits = 0;
	}

	if (player->m_state == player_state::PUNCHING_COMBO_1)
	{

		if (player->m_restart_animation == true)
		{
			if (player->m_face_right == true)
				player->m_current_animation = &(player->m_punch_combo_right1);
			else
				player->m_current_animation = &(player->m_punch_combo_left1);

			player->m_restart_animation = false;
			player->m_upper_punch_hits++;
		}

		if (player->m_current_animation == &(player->m_punch_combo_right1))
		{
			player->AdvanceAnimation(player->m_punch_combo_duration, &(player->m_idle_right1), false);
		}

		if (player->m_current_animation == &(player->m_punch_combo_left1))
		{
			player->AdvanceAnimation(player->m_punch_combo_duration, &(player->m_idle_left1), false);
		}

		if (player->m_current_animation == &(player->m_idle_right1) || player->m_current_animation == &(player->m_idle_left1))
		{
			player->m_combo_timer++;

			if (player->m_combo_timer > player->m_punch_combo_timeout)
			{
				player->m_continue_combo = false;
				player->m_combo_timer = 0.0f;
				player->m_state = player_state::IDLE;
			}
			else
			{
				player->m_continue_combo = true;
			}

			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				player->m_continue_combo = false;
				player->m_combo_timer = 0.0f;
				player->m_state = player_state::IDLE;
				player->m_upper_punch_hits = 0;
			}
		}
	}

	if (player->m_state == player_state::PUNCHING_COMBO_2)
	{
		if (player->m_restart_animation == true)
		{
			if (player->m_face_right == true)
				player->m_current_animation = &(player->m_punch_combo_right2);
			else
				player->m_current_animation = &(player->m_punch_combo_left2);

			player->m_restart_animation = false;
		}

		if (player->m_current_animation == &(player->m_punch_combo_right2))
		{
			player->AdvanceAnimation(player->m_punch_combo_duration, &(player->m_idle_right2), false);
		}

		if (player->m_current_animation == &(player->m_punch_combo_left2))
		{
			player->AdvanceAnimation(player->m_punch_combo_duration, &(player->m_idle_left2), false);
		}

		if (player->m_current_animation == &(player->m_idle_right2) || player->m_current_animation == &(player->m_idle_left2))
		{
			player->m_combo_timer++;

			if (player->m_combo_timer > player->m_punch_combo_timeout)
			{
				player->m_continue_combo = false;
				player->m_combo_timer = 0.0f;
				player->m_state = player_state::IDLE;
			}
			else
			{
				player->m_continue_combo = true;
			}

			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				player->m_continue_combo = false;
				player->m_combo_timer = 0.0f;
				player->m_state = player_state::IDLE;
			}
		}

	}

	if (player->m_state == player_state::PUNCHING_COMBO_3)
	{
		if (player->m_restart_animation == true)
		{
			if (player->m_face_right == true)
				player->m_current_animation = &(player->m_punch_combo_right3);
			else
				player->m_current_animation = &(player->m_punch_combo_left3);

			player->m_restart_animation = false;
		}

		if (player->m_current_animation == &(player->m_punch_combo_right3))
		{
			player->AdvanceAnimation(player->m_punch_combo_duration, &(player->m_idle_right2), false);
		}

		if (player->m_current_animation == &(player->m_punch_combo_left3))
		{
			player->AdvanceAnimation(player->m_punch_combo_duration, &(player->m_idle_left2), false);
		}

		if (player->m_current_animation == &(player->m_idle_right2) || player->m_current_animation == &(player->m_idle_left2))
		{
			player->m_continue_combo = false;
			player->m_combo_timer = 0.0f;
			player->m_state = player_state::IDLE;
		}

	}


	if (player->m_state == player_state::IDLE)
	{
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{
				player->m_state = player_state::BACK_PUNCHING;
				player->m_restart_animation = true;
				player->m_timer_count = 0.0f;
			}
		}
	}

	if (player->m_state == player_state::BACK_PUNCHING)
	{
		if (player->m_restart_animation == true)
		{
			if (player->m_face_right == true)
				player->m_current_animation = &(player->m_back_punch_right1);
			else
				player->m_current_animation = &(player->m_back_punch_left1);

			player->m_restart_animation = false;
		}

		if (player->m_current_animation == &(player->m_back_punch_right1))
		{
			player->AdvanceAnimation(player->m_back_punch_duration, &(player->m_back_punch_right2), false);
		}

		if (player->m_current_animation == &(player->m_back_punch_right2))
		{
			player->AdvanceAnimation(player->m_back_punch_duration, &(player->m_idle_right1), false);
		}

		if (player->m_current_animation == &(player->m_idle_right1))
		{
			player->m_state = player_state::IDLE;
			player->m_restart_animation = true;
		}

		if (player->m_current_animation == &(player->m_back_punch_left1))
		{
			player->AdvanceAnimation(player->m_back_punch_duration, &(player->m_back_punch_left2), false);
		}

		if (player->m_current_animation == &(player->m_back_punch_left2))
		{
			player->AdvanceAnimation(player->m_back_punch_duration, &(player->m_idle_left1), true);
		}

		if (player->m_current_animation == &(player->m_idle_left1))
		{
			player->m_state = player_state::IDLE;
			player->m_restart_animation = true;
		}

	}

	if (player->m_state == player_state::GRAB)
	{
		if (player->m_enemy_alive)
		{
			if (player->m_face_right)
			{
				player->m_current_animation = &(player->m_grab_right);

				if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
					player->m_state = player_state::IDLE;
			}
			else
			{
				player->m_current_animation = &(player->m_grab_left);

				if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
					player->m_state = player_state::IDLE;
			}

			if (player->m_state != player_state::IDLE)
			{
				if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
				{
					if (player->m_continue_combo_grab == false)
					{
						player->m_state = player_state::GRAB_KICK;
						player->m_kick_hits++;
						if (player->m_kick_hits == 3)
						{
							player->m_continue_combo_grab = true;
							player->m_kick_hits = 0;
						}
					}

					if (player->m_continue_combo_grab == true)
						player->m_state = player_state::GRAB_HEAD_HIT;
				}


				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
				{
					player->m_jump_start_pos = player->m_position;
					player->m_timer_count = 0.0;

					if (player->m_face_right)
						player->m_state = player_state::GRAB_AIR_SPIN_RIGHT;
					else
						player->m_state = player_state::GRAB_AIR_SPIN_LEFT;
				}
			}
		}
		else
		{
			player->m_state = player_state::IDLE;
			if (player->m_kick_hits == 2)
				player->m_kick_hits = 0;
		}	
	}

	if (player->m_state == player_state::GRAB_KICK)
	{
		
		if (player->m_face_right)
		{
			player->m_current_animation = &(player->m_grab_kick_head_combo_right1);	
		}
		else
		{
			player->m_current_animation = &(player->m_grab_kick_head_combo_left1);
		}

		if (player->m_current_animation == &(player->m_grab_kick_head_combo_right1))
		{
			player->AdvanceAnimation(player->m_grab_kick_head_duration, &(player->m_grab_right), true);
		}

		if (player->m_current_animation == &(player->m_grab_kick_head_combo_left1))
		{
			player->AdvanceAnimation(player->m_grab_kick_head_duration, &(player->m_grab_left), true);
		}

	
		if(player->m_current_animation == &(player->m_grab_right) || player->m_current_animation == &(player->m_grab_left))
			player->m_state = player_state::GRAB;
	}

	if (player->m_state == player_state::GRAB_HEAD_HIT)
	{
		
		if (player->m_face_right)
		{
			player->m_current_animation = &(player->m_grab_kick_head_combo_right2);
		}
		else
		{
			player->m_current_animation = &(player->m_grab_kick_head_combo_left2);
		}

		
		if (player->m_current_animation->Finished())
		{
			player->m_state = player_state::IDLE;
			player->m_continue_combo_grab = false;
			player->m_current_animation->Reset();
		}
		
	}

	if (player->m_state == player_state::GRAB_AIR_SPIN_RIGHT)
	{

		if (player->m_current_animation == &(player->m_grab_right))
		{
			player->m_current_animation = &(player->m_grab_air_spin_combo_right1);
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_right1))
		{
			player->AdvanceAnimation(player->m_grab_air_spin_duration, &(player->m_grab_air_spin_combo_right2), false);
			player->m_position.y = player->m_jump_start_pos.y - 11;
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_right2))
		{
			player->AdvanceAnimation(player->m_grab_air_spin_duration, &(player->m_grab_air_spin_combo_right3), false);
			player->m_position.y = player->m_jump_start_pos.y - 40;
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_right3))
		{
			player->AdvanceAnimation(player->m_grab_air_spin_duration, &(player->m_grab_air_spin_combo_right4), false);
			player->m_position.y = player->m_jump_start_pos.y - 59;
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_right4))
		{
			player->AdvanceAnimation(player->m_grab_air_spin_duration, &(player->m_grab_air_spin_combo_right5), false);
			player->m_position.y = player->m_jump_start_pos.y - 59;
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_right5))
		{
			player->AdvanceAnimation(player->m_grab_air_spin_duration, &(player->m_grab_air_spin_combo_right6), false);
			player->m_position.y = player->m_jump_start_pos.y - 40;
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_right6))
		{
			player->AdvanceAnimation(player->m_grab_air_spin_duration, &(player->m_grab_air_spin_combo_right7), true);
			player->m_position.y = player->m_jump_start_pos.y - 11;
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_right7))
		{
			if (player->m_position.y == player->m_jump_start_pos.y)
			{
				if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
				{
					player->m_state = player_state::GRAB_AIR_SPIN_FINISHER_RIGHT;
				}

				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
				{
					player->m_face_right = false;
					player->m_state = player_state::IDLE;
				}
			}
			else
			{
				player->m_position.y = player->m_jump_start_pos.y;
				player->m_position.x = player->m_jump_start_pos.x + 43;
			}
		}
	}
		
	if (player->m_state == player_state::GRAB_AIR_SPIN_LEFT)
	{
		if (player->m_current_animation == &(player->m_grab_left))
		{
			player->m_current_animation = &(player->m_grab_air_spin_combo_left1);
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_left1))
		{
			player->AdvanceAnimation(player->m_grab_air_spin_duration, &(player->m_grab_air_spin_combo_left2), false);
			player->m_position.y = player->m_jump_start_pos.y - 11;
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_left2))
		{
			player->AdvanceAnimation(player->m_grab_air_spin_duration, &(player->m_grab_air_spin_combo_left3), false);
			player->m_position.y = player->m_jump_start_pos.y - 40;
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_left3))
		{
			player->AdvanceAnimation(player->m_grab_air_spin_duration, &(player->m_grab_air_spin_combo_left4), false);
			player->m_position.y = player->m_jump_start_pos.y - 59;
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_left4))
		{
			player->AdvanceAnimation(player->m_grab_air_spin_duration, &(player->m_grab_air_spin_combo_left5), false);
			player->m_position.y = player->m_jump_start_pos.y - 59;
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_left5))
		{
			player->AdvanceAnimation(player->m_grab_air_spin_duration, &(player->m_grab_air_spin_combo_left6), false);
			player->m_position.y = player->m_jump_start_pos.y - 40;
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_left6))
		{
			player->AdvanceAnimation(player->m_grab_air_spin_duration, &(player->m_grab_air_spin_combo_left7), true);
			player->m_position.y = player->m_jump_start_pos.y - 11;
		}
		
		if (player->m_current_animation == &(player->m_grab_air_spin_combo_left7))
		{
			if (player->m_position.y == player->m_jump_start_pos.y)
			{
				if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
				{
					player->m_state = player_state::GRAB_AIR_SPIN_FINISHER_LEFT;
				}
				
				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
				{
					player->m_face_right = true;
					player->m_state = player_state::IDLE;
				}
			}								
			else
			{
				player->m_position.y = player->m_jump_start_pos.y;
				player->m_position.x = player->m_jump_start_pos.x - 43;
			}
		}
	}
		
	if (player->m_state == player_state::GRAB_AIR_SPIN_FINISHER_RIGHT)
	{
		if (player->m_current_animation == &(player->m_grab_air_spin_combo_right7))
		{
			player->m_current_animation = &(player->m_grab_air_spin_combo_finisher_right1);
		}
		
		if (player->m_current_animation == &(player->m_grab_air_spin_combo_finisher_right1))
		{
			if (player->m_current_animation->Finished())
			{
				player->m_current_animation = &(player->m_grab_air_spin_combo_finisher_right2);
			}
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_finisher_right2))
		{	
			player->AdvanceAnimation(player->m_grab_air_spin_finisher2_duration, &(player->m_grab_air_spin_combo_finisher_right3), true);
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_finisher_right3))
		{
			if (player->m_current_animation->Finished())
			{
				player->m_face_right = false;
				player->m_state = player_state::IDLE;
			}
		}

	}

	if (player->m_state == player_state::GRAB_AIR_SPIN_FINISHER_LEFT)
	{
		if (player->m_current_animation == &(player->m_grab_air_spin_combo_left7))
		{
			player->m_current_animation = &(player->m_grab_air_spin_combo_finisher_left1);
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_finisher_left1))
		{
			if (player->m_current_animation->Finished())
			{
				player->m_current_animation = &(player->m_grab_air_spin_combo_finisher_left2);
			}
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_finisher_left2))
		{
			player->AdvanceAnimation(player->m_grab_air_spin_finisher2_duration, &(player->m_grab_air_spin_combo_finisher_left3), true);
		}

		if (player->m_current_animation == &(player->m_grab_air_spin_combo_finisher_left3))
		{
			if (player->m_current_animation->Finished())
			{
				player->m_face_right = true;
				player->m_state = player_state::IDLE;
			}
		}
	}


	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (player->m_face_right == true)
			player->m_face_right = false;
		
		if (player->m_enemy_to_grab == true)
		{
			player->m_state = player_state::GRAB;
			player->m_restart_animation = true;
		}
		
		if (player->m_state == player_state::JUMPING || player->m_state == player_state::JUMPING_KICKING)
		{
			player->m_position.x -= (int)player->m_speed;
			player->m_jump_start_pos.x = player->m_position.x;
		}
		if (player->m_state == player_state::IDLE || player->m_state == player_state::WALKING)
		{
			player->m_state = player_state::WALKING;

			player->m_position.x -= (int)player->m_speed;

			if (player->m_current_animation != &(player->m_walk_left))
			{
				player->m_walk_left.Reset();
				player->m_current_animation = &(player->m_walk_left);
			}
		}
		if (player->m_carrying_weapon_pipe)
		{
			player->m_state = player_state::WEAPON_PIPE_WALKING_LEFT;

		}
		if (player->m_carrying_weapon_knife)
		{
			player->m_state = player_state::WEAPON_KNIFE_WALKING_LEFT;

		}


	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (player->m_face_right == false)
			player->m_face_right = true;
		
		if (player->m_enemy_to_grab == true)
		{
			player->m_state = player_state::GRAB;
			player->m_restart_animation = true;
		}
		
		if (player->m_state == player_state::JUMPING || player->m_state == player_state::JUMPING_KICKING)
		{
			player->m_position.x += (int)player->m_speed;
			player->m_jump_start_pos.x = player->m_position.x;
		}
		if (player->m_state == player_state::IDLE || player->m_state == player_state::WALKING)
		{
			player->m_state = player_state::WALKING;

			player->m_position.x += (int)player->m_speed;

			if (player->m_current_animation != &(player->m_walk_right))
			{
				player->m_walk_right.Reset();
				player->m_current_animation = &(player->m_walk_right);
			}
		}
		if (player->m_carrying_weapon_pipe)
		{
			player->m_state = player_state::WEAPON_PIPE_WALKING_RIGHT;

		}
		if (player->m_carrying_weapon_knife)
		{
			player->m_state = player_state::WEAPON_KNIFE_WALKING_RIGHT;

		}
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (player->m_state == player_state::WALKING || player->m_state == player_state::IDLE)
		{
			player->m_position.y -= (int)player->m_speed;

			if (player->m_face_right)
			{
				if (player->m_current_animation != &(player->m_walk_right))
				{
					player->m_walk_right.Reset();
					player->m_current_animation = &(player->m_walk_right);
				}
			}
			else
			{
				if (player->m_current_animation != &(player->m_walk_left))
				{
					player->m_walk_left.Reset();
					player->m_current_animation = &(player->m_walk_left);
				}
			}
		}
		if (player->m_carrying_weapon_pipe)
		{
			player->m_state = player_state::WEAPON_PIPE_WALKING_UP;

		}
		if (player->m_carrying_weapon_knife)
		{
			player->m_state = player_state::WEAPON_KNIFE_WALKING_UP;

		}
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (player->m_state == player_state::WALKING || player->m_state == player_state::IDLE)
		{
			player->m_position.y += (int)player->m_speed;

			if (player->m_face_right)
			{
				if (player->m_current_animation != &(player->m_walk_right))
				{
					player->m_walk_right.Reset();
					player->m_current_animation = &(player->m_walk_right);
				}
			}
			else
			{
				if (player->m_current_animation != &(player->m_walk_left))
				{
					player->m_walk_left.Reset();
					player->m_current_animation = &(player->m_walk_left);
				}
			}
		}

		if (player->m_carrying_weapon_pipe)
		{
			player->m_state = player_state::WEAPON_PIPE_WALKING_DOWN;

		}
		if (player->m_carrying_weapon_knife)
		{
			player->m_state = player_state::WEAPON_KNIFE_WALKING_DOWN;

		}

		// TODO 6: Shoot a laser using the particle system

		//App->particles->AddParticle(*(App->particles->laserParticle), App->player->position.x + 30, App->player->position.y, collider_type::LASER);
		//App->audio->PlayFx(App->particles->fxLaser, 0);
	}

	if (player->m_state == player_state::IDLE || 
		player->m_state == player_state::WALKING  &&
		App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE &&
		App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE &&
		App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE &&
		App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE &&
		App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE &&
		App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE &&
		App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE)
	{
		if (player->m_state != player_state::IDLE)
		{
			player->m_state = player_state::IDLE;
			player->m_restart_animation = true;
			player->m_timer_count = 0.0f;
		}

		if (player->m_state == player_state::IDLE)
		{
			if (player->m_carrying_weapon_pipe == true)
			{
				player->m_state = player_state::WEAPON_PIPE_IDLE;
				player->m_restart_animation = true;
				player->m_position.y -= 14;

			}
		}

		if (player->m_state == player_state::IDLE)
		{
			if (player->m_carrying_weapon_knife == true)
			{
				player->m_state = player_state::WEAPON_KNIFE_IDLE;
				player->m_restart_animation = true;
				//rectificación en Y
			}
		}
	}

	if (player->m_state == player_state::IDLE)
	{
		if (player->m_face_right)
		{
			if (player->m_restart_animation)
			{
				player->m_current_animation = &(player->m_idle_right1);
				player->m_restart_animation = false;
			}
			if (player->m_current_animation == &(player->m_idle_right1))
				player->AdvanceAnimation(player->m_idle1_duration, &(player->m_idle_right2), false);

			if (player->m_current_animation == &(player->m_idle_right2))
				player->AdvanceAnimation(player->m_idle2_duration, &(player->m_idle_right3), false);

			if (player->m_current_animation == &(player->m_idle_right3))
				player->AdvanceAnimation(player->m_idle3_duration, &(player->m_idle_right1), true);
		}
		else
		{
			if (player->m_restart_animation)
			{
				player->m_current_animation = &(player->m_idle_left1);
				player->m_restart_animation = false;
			}
			if (player->m_current_animation == &(player->m_idle_left1))
				player->AdvanceAnimation(player->m_idle1_duration, &(player->m_idle_left2), false);

			if (player->m_current_animation == &(player->m_idle_left2))
				player->AdvanceAnimation(player->m_idle2_duration, &(player->m_idle_left3), false);

			if (player->m_current_animation == &(player->m_idle_left3))
				player->AdvanceAnimation(player->m_idle3_duration, &(player->m_idle_left1), true);
		}
	}


	if (player->m_state == player_state::WEAPON_PIPE_IDLE)
	{
		
		if (player->m_face_right)
		{
			player->m_current_animation = &(player->m_weapon_pipe_idle_right);

		}
		else
		{
			player->m_current_animation = &(player->m_weapon_pipe_idle_left);
		}

		if (player->m_carrying_weapon_pipe == false)
		{
			player->m_state = player_state::IDLE;
			player->m_restart_animation = true;
			player->m_position.y += 14;
		}

	}
	if (player->m_state == player_state::WEAPON_PIPE_WALKING_LEFT)
	{
		player->m_position.x -= (int)player->m_speed;

		if (player->m_current_animation != &(player->m_weapon_pipe_walk_left))
		{
			player->m_weapon_pipe_walk_left.Reset();
			player->m_current_animation = &(player->m_weapon_pipe_walk_left);
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
		{
			player->m_state = player_state::WEAPON_PIPE_IDLE;
		}
		
		if (player->m_carrying_weapon_pipe == false)
		{
			player->m_state = player_state::IDLE;
			player->m_position.y += 14;
		}
	}
	
	if (player->m_state == player_state::WEAPON_PIPE_WALKING_RIGHT)
	{
		player->m_position.x += (int)player->m_speed;

		if (player->m_current_animation != &(player->m_weapon_pipe_walk_right))
		{
			player->m_weapon_pipe_walk_left.Reset();
			player->m_current_animation = &(player->m_weapon_pipe_walk_right);
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
		{
			player->m_state = player_state::WEAPON_PIPE_IDLE;
		}

		if (player->m_carrying_weapon_pipe == false)
		{
			player->m_state = player_state::IDLE;
			player->m_position.y += 14;
		}
	}

	if (player->m_state == player_state::WEAPON_PIPE_WALKING_UP)
	{
		player->m_position.y -= (int)player->m_speed;

		if (player->m_face_right)
		{
			if (player->m_current_animation != &(player->m_weapon_pipe_walk_right))
			{
				player->m_weapon_pipe_walk_right.Reset();
				player->m_current_animation = &(player->m_weapon_pipe_walk_right);
			}
		}
		else
		{
			if (player->m_current_animation != &(player->m_weapon_pipe_walk_left))
			{
				player->m_weapon_pipe_walk_left.Reset();
				player->m_current_animation = &(player->m_weapon_pipe_walk_left);
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
		{
			player->m_state = player_state::WEAPON_PIPE_IDLE;
		}

		if (player->m_carrying_weapon_pipe == false)
		{
			player->m_state = player_state::IDLE;
			player->m_position.y += 14;
		}
	}

	if (player->m_state == player_state::WEAPON_PIPE_WALKING_DOWN)
	{
		player->m_position.y += (int)player->m_speed;

		if (player->m_face_right)
		{
			if (player->m_current_animation != &(player->m_weapon_pipe_walk_right))
			{
				player->m_weapon_pipe_walk_right.Reset();
				player->m_current_animation = &(player->m_weapon_pipe_walk_right);
			}
		}
		else
		{
			if (player->m_current_animation != &(player->m_weapon_pipe_walk_left))
			{
				player->m_weapon_pipe_walk_left.Reset();
				player->m_current_animation = &(player->m_weapon_pipe_walk_left);
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
		{
			player->m_state = player_state::WEAPON_PIPE_IDLE;
		}

		if (player->m_carrying_weapon_pipe == false)
		{
			player->m_state = player_state::IDLE;
			player->m_position.y += 14;
		}
	}

	if (player->m_state == player_state::WEAPON_PIPE_ATTACK_RIGHT)
	{
		player->m_current_animation = &(player->m_weapon_pipe_attack_right);
		if (player->m_current_animation->Finished())
		{
			player->m_current_animation->Reset();
			player->m_state = player_state::WEAPON_PIPE_IDLE;
		}
	}

	if (player->m_state == player_state::WEAPON_PIPE_ATTACK_LEFT)
	{
		player->m_current_animation = &(player->m_weapon_pipe_attack_left);
		if (player->m_current_animation->Finished())
		{
			player->m_current_animation->Reset();
			player->m_state = player_state::WEAPON_PIPE_IDLE;
		}
	}

	if (player->m_state == player_state::WEAPON_KNIFE_IDLE)
	{

		if (player->m_face_right)
		{
			player->m_current_animation = &(player->m_weapon_knife_idle_right);

		}
		else
		{
			player->m_current_animation = &(player->m_weapon_knife_idle_left);
		}

		if (player->m_carrying_weapon_knife == false)
		{
			player->m_state = player_state::IDLE;
			player->m_restart_animation = true;
			
		}
	}

	if (player->m_state == player_state::WEAPON_KNIFE_WALKING_LEFT)
	{
		player->m_position.x -= (int)player->m_speed;

		if (player->m_current_animation != &(player->m_weapon_knife_walk_left))
		{
			player->m_weapon_knife_walk_left.Reset();
			player->m_current_animation = &(player->m_weapon_knife_walk_left);
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
		{
			player->m_state = player_state::WEAPON_KNIFE_IDLE;
		}

		if (player->m_carrying_weapon_knife == false)
		{
			player->m_state = player_state::IDLE;
			
		}
	}

	if (player->m_state == player_state::WEAPON_KNIFE_WALKING_RIGHT)
	{
		player->m_position.x += (int)player->m_speed;

		if (player->m_current_animation != &(player->m_weapon_knife_walk_right))
		{
			player->m_weapon_knife_walk_left.Reset();
			player->m_current_animation = &(player->m_weapon_knife_walk_right);
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
		{
			player->m_state = player_state::WEAPON_KNIFE_IDLE;
		}

		if (player->m_carrying_weapon_knife == false)
		{
			player->m_state = player_state::IDLE;
			
		}
	}

	if (player->m_state == player_state::WEAPON_KNIFE_WALKING_UP)
	{
		player->m_position.y -= (int)player->m_speed;

		if (player->m_face_right)
		{
			if (player->m_current_animation != &(player->m_weapon_knife_walk_right))
			{
				player->m_weapon_knife_walk_right.Reset();
				player->m_current_animation = &(player->m_weapon_knife_walk_right);
			}
		}
		else
		{
			if (player->m_current_animation != &(player->m_weapon_knife_walk_left))
			{
				player->m_weapon_knife_walk_left.Reset();
				player->m_current_animation = &(player->m_weapon_knife_walk_left);
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
		{
			player->m_state = player_state::WEAPON_KNIFE_IDLE;
		}

		if (player->m_carrying_weapon_knife == false)
		{
			player->m_state = player_state::IDLE;
			
		}
	}

	if (player->m_state == player_state::WEAPON_KNIFE_WALKING_DOWN)
	{
		player->m_position.y += (int)player->m_speed;

		if (player->m_face_right)
		{
			if (player->m_current_animation != &(player->m_weapon_knife_walk_right))
			{
				player->m_weapon_knife_walk_right.Reset();
				player->m_current_animation = &(player->m_weapon_knife_walk_right);
			}
		}
		else
		{
			if (player->m_current_animation != &(player->m_weapon_knife_walk_left))
			{
				player->m_weapon_knife_walk_left.Reset();
				player->m_current_animation = &(player->m_weapon_knife_walk_left);
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
		{
			player->m_state = player_state::WEAPON_KNIFE_IDLE;
		}

		if (player->m_carrying_weapon_pipe == false)
		{
			player->m_state = player_state::IDLE;
			
		}
	}

	if (player->m_state == player_state::WEAPON_KNIFE_ATTACK_RIGHT)
	{
		player->m_current_animation = &(player->m_weapon_knife_attack_right);
		if (player->m_current_animation->Finished())
		{
			player->m_current_animation->Reset();
			player->m_state = player_state::WEAPON_KNIFE_IDLE;
		}
	}

	if (player->m_state == player_state::WEAPON_KNIFE_ATTACK_LEFT)
	{
		player->m_current_animation = &(player->m_weapon_knife_attack_left);
		if (player->m_current_animation->Finished())
		{
			player->m_current_animation->Reset();
			player->m_state = player_state::WEAPON_KNIFE_IDLE;
		}
	}


	//playerCollider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------

	App->renderer->Blit(player->m_texture, player->m_position.x, player->m_position.y, &(player->m_current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

// TODO 13: Make so is the laser collides, it is removed and create an explosion particle at its position

// TODO 14: Make so if the player collides, it is removed and create few explosions at its positions
// then fade away back to the first screen (use the "destroyed" bool already created 
// You will need to create, update and destroy the collider with the player

void ModulePlayer::OnCollision(Collider* collider1, Collider* collider2)
{
	/*Collider* laserCollider = nullptr;
	Collider* playerCollider = nullptr;
	Collider* wallCollider = nullptr;

	switch (collider1->c_type)
	{
	case collider_type::LASER:
	laserCollider = collider1;
	break;
	case collider_type::PLAYER:
	playerCollider = collider1;
	break;
	case collider_type::WALL:
	wallCollider = collider1;
	break;
	}

	switch (collider2->c_type)
	{
	case collider_type::LASER:
	laserCollider = collider2;
	break;
	case collider_type::PLAYER:
	playerCollider = collider2;
	break;
	case collider_type::WALL:
	wallCollider = collider2;
	break;
	}

	if (laserCollider != nullptr)
	{
	laserCollider->particle->to_delete = true;
	laserCollider->to_delete = true;
	App->particles->AddParticle(*(App->particles->explosionParticle), laserCollider->rect.x, laserCollider->rect.y, collider_type::EXPLOSION);
	}

	if (playerCollider != nullptr)
	{
	destroyed = true;
	playerCollider->to_delete = true;
	App->particles->AddParticle(*(App->particles->explosionParticle), playerCollider->rect.x, playerCollider->rect.y, collider_type::EXPLOSION);

	App->fade->FadeToBlack((Module*)App->scene_intro, (Module*)App->scene_space);
	}*/
}
