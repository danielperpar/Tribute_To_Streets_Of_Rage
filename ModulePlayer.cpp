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
#include "ModuleEnemies.h"
#include "AIController.h"



ModulePlayer::ModulePlayer(bool active) : Module(active) {}


ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("assets/spritesheets/axel.png");

	m_player = (Player*)EntityManager::CreateEntity(graphics, "axel", entity_type::PLAYER, { 800, 150 }, 150);
	m_player->m_state = player_state::IDLE;

	SDL_Rect collider;
	collider.x = 0;
	collider.y = 0;
	collider.w = 36;
	collider.h = 63;

	m_player_collider = App->collision->AddCollider(collider, m_player, collider_type::PLAYER);
	m_player_collider->SetPos(m_player->m_position.x + m_player->m_x_ref - collider.w/2, m_player->m_depth);


	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	EntityManager::DestroyEntity(m_player);
	m_player = nullptr;

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	m_time = SDL_GetTicks();
	if (m_time - m_update_time >= m_dt)
	{
		m_do_logic = true;
	}
	if (m_do_logic)
	{
		m_do_logic = false;
		m_update_time = SDL_GetTicks();
	

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		if ((m_player->m_state == player_state::IDLE || m_player->m_state == player_state::WALKING) && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE)
		{
			m_player->m_state = player_state::JUMPING;
			m_player->m_jump_up = true;
			m_player->m_jump_start_pos = m_player->m_position;
			m_player->m_timer_count = 0.0f;
			m_player->m_restart_animation = true;
			m_player->m_jumping = true;
			m_player->m_speed = 2.0f;
		}
	}

	if (m_player->m_state == player_state::JUMPING)
	{

		if (m_player->m_restart_animation)
		{
			if (m_player->m_face_right)
				m_player->m_current_animation = &(m_player->m_jump_right1);
			else
				m_player->m_current_animation = &(m_player->m_jump_left1);

			m_player->m_restart_animation = false;
		}

		if (m_player->m_jump_up)
		{
			m_player->m_position.y = (int)(m_player->m_position.y - m_player->m_jump_speed);
			UpdateColliderPosition();
			
			if (m_player->m_jump_start_pos.y - m_player->m_position.y >= m_player->m_max_jump_height)
				m_player->m_jump_up = false;
		}
		else
		{
			m_player->m_position.y = (int)(m_player->m_position.y + m_player->m_jump_speed);
			UpdateColliderPosition();
		}

		if (m_player->m_jump_start_pos.y - m_player->m_position.y <= 0)
		{
			m_player->m_position.y = m_player->m_jump_start_pos.y;
			UpdateColliderPosition();
			m_player->m_jumping = false;
		}

		if (m_player->m_jumping)
		{	
			if (m_player->m_current_animation->Finished())
			{
				if(m_player->m_face_right)
					m_player->m_current_animation = &(m_player->m_jump_right2);
				else
					m_player->m_current_animation = &(m_player->m_jump_left2);
			}				
		}

		if (!m_player->m_jumping)
		{
		
			if (m_player->m_current_animation == &(m_player->m_jump_right2))
			{
				m_player->m_current_animation = &(m_player->m_jump_right1);
			}
			if (m_player->m_current_animation == &(m_player->m_jump_right1))
			{
				if (m_player->m_current_animation->Finished())
				{
					m_player->m_current_animation = &(m_player->m_idle_right1);
				}
			}

			if (m_player->m_current_animation == &(m_player->m_jump_left2))
			{
				m_player->m_current_animation = &(m_player->m_jump_left1);
			}
			if (m_player->m_current_animation == &(m_player->m_jump_left1))
			{
				if (m_player->m_current_animation->Finished())
				{
					m_player->m_current_animation = &(m_player->m_idle_left1);
				}
			}
			
		}

		if (m_player->m_current_animation == &(m_player->m_idle_right1))
		{
			m_player->m_restart_animation = true;
			m_player->m_speed = 1.0f;
			m_player->m_state = player_state::IDLE;
		}
		if (m_player->m_current_animation == &(m_player->m_idle_left1))
		{
			m_player->m_restart_animation = true;
			m_player->m_speed = 1.0f;
			m_player->m_state = player_state::IDLE;
		}


		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && m_player->m_jumping)
		{
			m_player->m_state = player_state::JUMPING_KICKING;
		}
	
	}

	if (m_player->m_state == player_state::JUMPING_KICKING)
	{
		if (m_player->m_jump_up)
		{
			m_player->m_position.y = (int)(m_player->m_position.y - m_player->m_jump_speed);
			UpdateColliderPosition();

			if (m_player->m_jump_start_pos.y - m_player->m_position.y >= m_player->m_max_jump_height)
				m_player->m_jump_up = false;
		}
		else
		{
			m_player->m_position.y = (int)(m_player->m_position.y + m_player->m_jump_speed);
			UpdateColliderPosition();
		}

		if (m_player->m_jump_start_pos.y - m_player->m_position.y <= 0)
		{
			m_player->m_position.y = m_player->m_jump_start_pos.y;
			UpdateColliderPosition();
			m_player->m_jumping = false;
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && m_player->m_jumping == true)
		{
			if (m_player->m_face_right == true)
				m_player->m_current_animation = &(m_player->m_air_kick_right);
			else
				m_player->m_current_animation = &(m_player->m_air_kick_left);
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_UP || !m_player->m_jumping)
		{
			if (m_player->m_face_right)
				m_player->m_current_animation = &(m_player->m_jump_right2);
			else
				m_player->m_current_animation = &(m_player->m_jump_left2);
			
			m_player->m_state = player_state::JUMPING;
		}
	}


	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{
		switch (m_player->m_state)
		{
		case player_state::IDLE : 
				m_player->m_in_combo_time = true;
				m_player->m_state = player_state::PUNCH;

				for (std::list<Entity*>::iterator it = App->entities.begin(); it != App->entities.end(); it++)
				{
					if ((*it)->m_type == entity_type::ENEMY)
					{
						Enemy* enemy = (Enemy*)*it;
						if (LookingEachOther(enemy) && enemy->m_enemy_to_hit)
						{
							enemy->m_state = enemy_state::DAMAGED;
							if (m_player->m_punch_combo_hits < 2)
								m_player->m_state = player_state::PUNCHING_COMBO_1;
							if (m_player->m_punch_combo_hits == 2)
								m_player->m_state = player_state::PUNCHING_COMBO_2;
							if (m_player->m_punch_combo_hits == 3)
								m_player->m_state = player_state::PUNCHING_COMBO_3;
						}
					}
				}	
				break;
		case player_state::WEAPON_PIPE_IDLE:
			if (m_player->m_face_right)
			{
				m_player->m_state = player_state::WEAPON_PIPE_ATTACK_RIGHT;
			}
			else
			{
				m_player->m_state = player_state::WEAPON_PIPE_ATTACK_LEFT;	
			}
			break;

		case player_state::WEAPON_KNIFE_IDLE:
			if (m_player->m_face_right)
			{
				m_player->m_state = player_state::WEAPON_KNIFE_ATTACK_RIGHT;
			}
			else
			{
				m_player->m_state = player_state::WEAPON_KNIFE_ATTACK_LEFT;
			}
			break;
		}

	}

	if (m_player->m_state == player_state::PUNCH)
	{
		if (m_player->m_face_right == true)
			m_player->m_current_animation = &(m_player->m_punch_combo_right1);
		else
			m_player->m_current_animation = &(m_player->m_punch_combo_left1);

		if (m_player->m_current_animation == &(m_player->m_punch_combo_right1))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation->Reset();
				m_player->m_current_animation = &(m_player->m_idle_right1);
				m_player->m_state = player_state::IDLE;
			}
		}
		if (m_player->m_current_animation == &(m_player->m_punch_combo_left1))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation->Reset();
				m_player->m_current_animation = &(m_player->m_idle_left1);
				m_player->m_state = player_state::IDLE;
			}
		}
	}

	if (m_player->m_state == player_state::PUNCHING_COMBO_1)
	{
		if (m_player->m_face_right == true)
			m_player->m_current_animation = &(m_player->m_punch_combo_right1);
		else
			m_player->m_current_animation = &(m_player->m_punch_combo_left1);

		if (m_player->m_current_animation == &(m_player->m_punch_combo_right1))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_punch_combo_hits++;
				m_player->m_current_animation->Reset();
				m_player->m_current_animation = &(m_player->m_idle_right1);
				m_player->m_state = player_state::IDLE;
			}
		}
		if (m_player->m_current_animation == &(m_player->m_punch_combo_left1))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_punch_combo_hits++;
				m_player->m_current_animation->Reset();
				m_player->m_current_animation = &(m_player->m_idle_left1);
				m_player->m_state = player_state::IDLE;
			}
		}
		if (m_player->m_state == player_state::IDLE)
		{
			m_player->m_combo_timer++;
			if (m_player->m_combo_timer > m_player->m_punch_combo_timeout)
			{
				m_player->m_in_combo_time = false;
				m_player->m_combo_timer = 0.0f;
				m_player->m_punch_combo_hits = 0;
			}
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				m_player->m_in_combo_time = false;
				m_player->m_combo_timer = 0.0f;
				m_player->m_state = player_state::IDLE;
				m_player->m_punch_combo_hits = 0;
			}
		}
	}

	if (m_player->m_state == player_state::PUNCHING_COMBO_2)
	{
		if (m_player->m_face_right == true)
			m_player->m_current_animation = &(m_player->m_punch_combo_right2);
		else
			m_player->m_current_animation = &(m_player->m_punch_combo_left2);

		if (m_player->m_current_animation == &(m_player->m_punch_combo_right2))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation->Reset();
				m_player->m_punch_combo_hits++;
				m_player->m_current_animation = &(m_player->m_idle_right2);
				m_player->m_state = player_state::IDLE;
			}
		}
		if (m_player->m_current_animation == &(m_player->m_punch_combo_left2))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation->Reset();
				m_player->m_punch_combo_hits++;
				m_player->m_current_animation = &(m_player->m_idle_left2);
				m_player->m_state = player_state::IDLE;
			}
		}
		if (m_player->m_state == player_state::IDLE)
		{
			m_player->m_combo_timer++;
			if (m_player->m_combo_timer > m_player->m_punch_combo_timeout)
			{
				m_player->m_in_combo_time = false;
				m_player->m_combo_timer = 0.0f;
				m_player->m_punch_combo_hits = 0;
			}
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				m_player->m_in_combo_time = false;
				m_player->m_combo_timer = 0.0f;
				m_player->m_state = player_state::IDLE;
			}
		}
	}

	if (m_player->m_state == player_state::PUNCHING_COMBO_3)
	{
		m_player->m_float_attack = true;

		if (m_player->m_face_right == true)
			m_player->m_current_animation = &(m_player->m_punch_combo_right3);
		else
			m_player->m_current_animation = &(m_player->m_punch_combo_left3);

		if (m_player->m_current_animation == &(m_player->m_punch_combo_right3))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation->Reset();
				m_player->m_current_animation = &(m_player->m_idle_right2);
				m_player->m_state = player_state::IDLE;
			}
		}
		if (m_player->m_current_animation == &(m_player->m_punch_combo_left3))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation->Reset();
				m_player->m_current_animation = &(m_player->m_idle_left2);
				m_player->m_state = player_state::IDLE;
			}
		}
		if (m_player->m_state == player_state::IDLE)
		{
			m_player->m_combo_timer = 0.0f;
			m_player->m_state = player_state::IDLE;
			m_player->m_punch_combo_hits = 0;
		}
	}

	if (m_player->m_state == player_state::IDLE)
	{
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{
				m_player->m_state = player_state::BACK_PUNCHING;
				m_player->m_restart_animation = true;
				m_player->m_timer_count = 0.0f;
			}
		}
	}

	if (m_player->m_state == player_state::BACK_PUNCHING)
	{
		if (m_player->m_restart_animation == true)
		{
			if (m_player->m_face_right == true)
				m_player->m_current_animation = &(m_player->m_back_punch_right1);
			else
				m_player->m_current_animation = &(m_player->m_back_punch_left1);

			m_player->m_restart_animation = false;
		}

		if (m_player->m_current_animation == &(m_player->m_back_punch_right1))
		{
			
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_back_punch_right2);
			}
		}

		if (m_player->m_current_animation == &(m_player->m_back_punch_right2))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_idle_right1);
			}
		}

		if (m_player->m_current_animation == &(m_player->m_idle_right1))
		{
			m_player->m_state = player_state::IDLE;
			m_player->m_restart_animation = true;
		}

		if (m_player->m_current_animation == &(m_player->m_back_punch_left1))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_back_punch_left2);
			}
		}

		if (m_player->m_current_animation == &(m_player->m_back_punch_left2))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_idle_left1);
			}
		}

		if (m_player->m_current_animation == &(m_player->m_idle_left1))
		{
			m_player->m_state = player_state::IDLE;
			m_player->m_restart_animation = true;
		}

	}

	if (m_player->m_state == player_state::GRAB)
	{
		
		if (m_player->m_face_right)
		{
			m_player->m_current_animation = &(m_player->m_grab_right);

			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
				m_player->m_state = player_state::IDLE;
		}
		else
		{
			m_player->m_current_animation = &(m_player->m_grab_left);

			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
				m_player->m_state = player_state::IDLE;
		}

		if (m_player->m_state != player_state::IDLE)
		{
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
			{
				if (m_player->m_continue_combo_grab == false)
				{
					m_player->m_state = player_state::GRAB_KICK;
					m_player->m_kick_hits++;
					if (m_player->m_kick_hits == 3)
					{
						m_player->m_continue_combo_grab = true;
						m_player->m_kick_hits = 0;
					}
				}

				if (m_player->m_continue_combo_grab == true)
					m_player->m_state = player_state::GRAB_HEAD_HIT;
			}


			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{
				m_player->m_jump_start_pos = m_player->m_position;
				m_player->m_timer_count = 0.0;

				if (m_player->m_face_right)
					m_player->m_state = player_state::GRAB_AIR_SPIN_RIGHT;
				else
					m_player->m_state = player_state::GRAB_AIR_SPIN_LEFT;
			}
		}
	}

	if (m_player->m_state == player_state::GRAB_KICK)
	{
		
		if (m_player->m_face_right)
		{
			m_player->m_current_animation = &(m_player->m_grab_kick_head_combo_right1);	
		}
		else
		{
			m_player->m_current_animation = &(m_player->m_grab_kick_head_combo_left1);
		}

		if (m_player->m_current_animation == &(m_player->m_grab_kick_head_combo_right1))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_right);
			}
		}

		if (m_player->m_current_animation == &(m_player->m_grab_kick_head_combo_left1))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_left);
			}
		}

	
		if(m_player->m_current_animation == &(m_player->m_grab_right) || m_player->m_current_animation == &(m_player->m_grab_left))
			m_player->m_state = player_state::GRAB;
	}

	if (m_player->m_state == player_state::GRAB_HEAD_HIT)
	{
		
		if (m_player->m_face_right)
		{
			m_player->m_current_animation = &(m_player->m_grab_kick_head_combo_right2);
		}
		else
		{
			m_player->m_current_animation = &(m_player->m_grab_kick_head_combo_left2);
		}

		
		if (m_player->m_current_animation->Finished())
		{
			m_player->m_state = player_state::IDLE;
			m_player->m_continue_combo_grab = false;
			m_player->m_current_animation->Reset();
		}
		
	}

	if (m_player->m_state == player_state::GRAB_AIR_SPIN_RIGHT)
	{

		if (m_player->m_current_animation == &(m_player->m_grab_right))
		{
			m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_right1);
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_right1))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_right2);
			}
			m_player->m_position.y = m_player->m_jump_start_pos.y - 11;
			UpdateColliderPosition();
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_right2))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_right3);
			}

			m_player->m_position.y = m_player->m_jump_start_pos.y - 40;
			UpdateColliderPosition();
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_right3))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_right4);
			}
			m_player->m_position.y = m_player->m_jump_start_pos.y - 59;
			UpdateColliderPosition();
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_right4))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_right5);
			}
			m_player->m_position.y = m_player->m_jump_start_pos.y - 59;
			UpdateColliderPosition();
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_right5))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_right6);
			}
			m_player->m_position.y = m_player->m_jump_start_pos.y - 40;
			UpdateColliderPosition();
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_right6))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_right7);
			}

			m_player->m_position.y = m_player->m_jump_start_pos.y - 11;
			UpdateColliderPosition();
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_right7))
		{
			if (m_player->m_position.y == m_player->m_jump_start_pos.y)
			{
				if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
				{
					m_player->m_state = player_state::GRAB_AIR_SPIN_FINISHER_RIGHT;
				}

				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
				{
					m_player->m_face_right = false;
					m_player->m_state = player_state::IDLE;
				}
			}
			else
			{
				m_player->m_position.y = m_player->m_jump_start_pos.y;
				m_player->m_position.x = m_player->m_jump_start_pos.x + 43;
				UpdateColliderPosition();
			}
		}
	}
		
	if (m_player->m_state == player_state::GRAB_AIR_SPIN_LEFT)
	{
		if (m_player->m_current_animation == &(m_player->m_grab_left))
		{
			m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_left1);
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_left1))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_left2);
			}
			m_player->m_position.y = m_player->m_jump_start_pos.y - 11;
			UpdateColliderPosition();
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_left2))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_left3);
			}
			m_player->m_position.y = m_player->m_jump_start_pos.y - 40;
			UpdateColliderPosition();
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_left3))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_left4);
			}
			m_player->m_position.y = m_player->m_jump_start_pos.y - 59;
			UpdateColliderPosition();
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_left4))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_left5);
			}
			m_player->m_position.y = m_player->m_jump_start_pos.y - 59;
			UpdateColliderPosition();
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_left5))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_left6);
			}
			m_player->m_position.y = m_player->m_jump_start_pos.y - 40;
			UpdateColliderPosition();
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_left6))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_left7);
			}
			m_player->m_position.y = m_player->m_jump_start_pos.y - 11;
			UpdateColliderPosition();
		}
		
		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_left7))
		{
			if (m_player->m_position.y == m_player->m_jump_start_pos.y)
			{
				if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
				{
					m_player->m_state = player_state::GRAB_AIR_SPIN_FINISHER_LEFT;
				}
				
				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
				{
					m_player->m_face_right = true;
					m_player->m_state = player_state::IDLE;
				}
			}								
			else
			{
				m_player->m_position.y = m_player->m_jump_start_pos.y;
				m_player->m_position.x = m_player->m_jump_start_pos.x - 43;
				UpdateColliderPosition();
			}
		}
	}
		
	if (m_player->m_state == player_state::GRAB_AIR_SPIN_FINISHER_RIGHT)
	{
		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_right7))
		{
			m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_finisher_right1);
		}
		
		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_finisher_right1))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_finisher_right2);
			}
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_finisher_right2))
		{	
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_finisher_right3);
			}
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_finisher_right3))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_face_right = false;
				m_player->m_state = player_state::IDLE;
			}
		}

	}

	if (m_player->m_state == player_state::GRAB_AIR_SPIN_FINISHER_LEFT)
	{
		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_left7))
		{
			m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_finisher_left1);
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_finisher_left1))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_finisher_left2);
			}
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_finisher_left2))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_current_animation = &(m_player->m_grab_air_spin_combo_finisher_left3);
			}
		}

		if (m_player->m_current_animation == &(m_player->m_grab_air_spin_combo_finisher_left3))
		{
			if (m_player->m_current_animation->Finished())
			{
				m_player->m_face_right = true;
				m_player->m_state = player_state::IDLE;
			}
		}
	}


	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (m_player->m_face_right == true)
			m_player->m_face_right = false;

		if (m_player->m_position.x < MIN_X_POSITION)
			m_player->m_position.x = MIN_X_POSITION;

		/*
		if (m_player->m_enemy_to_grab == true)
		{
			m_player->m_state = player_state::GRAB;
			m_player->m_restart_animation = true;
		}
		*/
		if (m_player->m_state == player_state::JUMPING || m_player->m_state == player_state::JUMPING_KICKING)
		{
			m_player->m_position.x -= (int)m_player->m_speed;
			m_player->m_jump_start_pos.x = m_player->m_position.x;
			UpdateColliderPosition();
		}
		if (m_player->m_state == player_state::IDLE || m_player->m_state == player_state::WALKING)
		{
			m_player->m_state = player_state::WALKING;

			m_player->m_position.x -= (int)m_player->m_speed;
			UpdateColliderPosition();

			if (m_player->m_current_animation != &(m_player->m_walk_left))
			{
				m_player->m_walk_left.Reset();
				m_player->m_current_animation = &(m_player->m_walk_left);
			}
		}
		if (m_player->m_state == player_state::WEAPON_PIPE_IDLE || m_player->m_state == player_state::WEAPON_PIPE_WALKING)
		{
			m_player->m_state = player_state::WEAPON_PIPE_WALKING;
			m_player->m_position.x -= (int)m_player->m_speed;
			UpdateColliderPosition();

			if (m_player->m_current_animation != &(m_player->m_weapon_pipe_walk_left))
			{
				m_player->m_weapon_pipe_walk_left.Reset();
				m_player->m_current_animation = &(m_player->m_weapon_pipe_walk_left);
			}
		}
		if (m_player->m_state == player_state::WEAPON_KNIFE_IDLE || m_player->m_state == player_state::WEAPON_KNIFE_WALKING)
		{
			m_player->m_state = player_state::WEAPON_KNIFE_WALKING;
			m_player->m_position.x -= (int)m_player->m_speed;
			UpdateColliderPosition();

			if (m_player->m_current_animation != &(m_player->m_weapon_knife_walk_left))
			{
				m_player->m_weapon_knife_walk_left.Reset();
				m_player->m_current_animation = &(m_player->m_weapon_knife_walk_left);
			}
		}


	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (m_player->m_face_right == false)
			m_player->m_face_right = true;

		if (m_player->m_position.x > MAX_X_POSITION)
			m_player->m_position.x = MAX_X_POSITION;
		
		/*
		if (m_player->m_enemy_to_grab == true)
		{
			m_player->m_state = player_state::GRAB;
			m_player->m_restart_animation = true;
		}
		*/
		if (m_player->m_state == player_state::JUMPING || m_player->m_state == player_state::JUMPING_KICKING)
		{
			m_player->m_position.x += (int)m_player->m_speed;
			m_player->m_jump_start_pos.x = m_player->m_position.x;
			UpdateColliderPosition();
		}
		if (m_player->m_state == player_state::IDLE || m_player->m_state == player_state::WALKING)
		{
			m_player->m_state = player_state::WALKING;

			m_player->m_position.x += (int)m_player->m_speed;
			UpdateColliderPosition();

			if (m_player->m_current_animation != &(m_player->m_walk_right))
			{
				m_player->m_walk_right.Reset();
				m_player->m_current_animation = &(m_player->m_walk_right);
			}
		}
		if (m_player->m_state == player_state::WEAPON_PIPE_IDLE || m_player->m_state == player_state::WEAPON_PIPE_WALKING)
		{
			m_player->m_state = player_state::WEAPON_PIPE_WALKING;
			m_player->m_position.x += (int)m_player->m_speed;
			UpdateColliderPosition();

			if (m_player->m_current_animation != &(m_player->m_weapon_pipe_walk_right))
			{
				m_player->m_weapon_pipe_walk_right.Reset();
				m_player->m_current_animation = &(m_player->m_weapon_pipe_walk_right);
			}
		}
		if (m_player->m_state == player_state::WEAPON_KNIFE_IDLE || m_player->m_state == player_state::WEAPON_KNIFE_WALKING)
		{
			m_player->m_state = player_state::WEAPON_KNIFE_WALKING;
			m_player->m_position.x += (int)m_player->m_speed;
			UpdateColliderPosition();

			if (m_player->m_current_animation != &(m_player->m_weapon_knife_walk_right))
			{
				m_player->m_weapon_knife_walk_right.Reset();
				m_player->m_current_animation = &(m_player->m_weapon_knife_walk_right);
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (m_player->m_state == player_state::WALKING || m_player->m_state == player_state::IDLE)
		{
			if (m_player->m_position.y < MIN_Y_POSITION) 
				m_player->m_position.y = MIN_Y_POSITION;
			

			m_player->m_position.y -= (int)m_player->m_speed;
			m_player->m_depth = m_player->m_position.y;
			UpdateColliderPosition();

			if (m_player->m_face_right)
			{
				if (m_player->m_current_animation != &(m_player->m_walk_right))
				{
					m_player->m_walk_right.Reset();
					m_player->m_current_animation = &(m_player->m_walk_right);
				}
			}
			else
			{
				if (m_player->m_current_animation != &(m_player->m_walk_left))
				{
					m_player->m_walk_left.Reset();
					m_player->m_current_animation = &(m_player->m_walk_left);
				}
			}
		}
		if (m_player->m_state == player_state::WEAPON_PIPE_WALKING || m_player->m_state == player_state::WEAPON_PIPE_IDLE)
		{
			m_player->m_position.y -= (int)m_player->m_speed;
			m_player->m_depth = m_player->m_position.y;
			UpdateColliderPosition();

			if (m_player->m_face_right)
			{
				if (m_player->m_current_animation != &(m_player->m_weapon_pipe_walk_right))
				{
					m_player->m_weapon_pipe_walk_right.Reset();
					m_player->m_current_animation = &(m_player->m_weapon_pipe_walk_right);
				}
			}
			else
			{
				if (m_player->m_current_animation != &(m_player->m_weapon_pipe_walk_left))
				{
					m_player->m_weapon_pipe_walk_left.Reset();
					m_player->m_current_animation = &(m_player->m_weapon_pipe_walk_left);
				}
			}
		}
		if (m_player->m_state == player_state::WEAPON_KNIFE_WALKING || m_player->m_state == player_state::WEAPON_KNIFE_IDLE)
		{
			m_player->m_position.y -= (int)m_player->m_speed;
			m_player->m_depth = m_player->m_position.y;
			UpdateColliderPosition();

			if (m_player->m_face_right)
			{
				if (m_player->m_current_animation != &(m_player->m_weapon_knife_walk_right))
				{
					m_player->m_weapon_knife_walk_right.Reset();
					m_player->m_current_animation = &(m_player->m_weapon_knife_walk_right);
				}
			}
			else
			{
				if (m_player->m_current_animation != &(m_player->m_weapon_knife_walk_left))
				{
					m_player->m_weapon_knife_walk_left.Reset();
					m_player->m_current_animation = &(m_player->m_weapon_knife_walk_left);
				}
			}
		}
		
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (m_player->m_state == player_state::WALKING || m_player->m_state == player_state::IDLE)
		{
			if (m_player->m_position.y > MAX_Y_POSITION) 
				m_player->m_position.y = MAX_Y_POSITION;
	

			m_player->m_position.y += (int)m_player->m_speed;
			m_player->m_depth = m_player->m_position.y;
			UpdateColliderPosition();

			if (m_player->m_face_right)
			{
				if (m_player->m_current_animation != &(m_player->m_walk_right))
				{
					m_player->m_walk_right.Reset();
					m_player->m_current_animation = &(m_player->m_walk_right);
				}
			}
			else
			{
				if (m_player->m_current_animation != &(m_player->m_walk_left))
				{
					m_player->m_walk_left.Reset();
					m_player->m_current_animation = &(m_player->m_walk_left);
				}
			}
		}
		if (m_player->m_state == player_state::WEAPON_PIPE_WALKING || m_player->m_state == player_state::WEAPON_PIPE_IDLE)
		{
			m_player->m_position.y += (int)m_player->m_speed;
			m_player->m_depth = m_player->m_position.y;
			UpdateColliderPosition();

			if (m_player->m_face_right)
			{
				if (m_player->m_current_animation != &(m_player->m_weapon_pipe_walk_right))
				{
					m_player->m_weapon_pipe_walk_right.Reset();
					m_player->m_current_animation = &(m_player->m_weapon_pipe_walk_right);
				}
			}
			else
			{
				if (m_player->m_current_animation != &(m_player->m_weapon_pipe_walk_left))
				{
					m_player->m_weapon_pipe_walk_left.Reset();
					m_player->m_current_animation = &(m_player->m_weapon_pipe_walk_left);
				}
			}
		}
		if (m_player->m_state == player_state::WEAPON_KNIFE_WALKING || m_player->m_state == player_state::WEAPON_KNIFE_IDLE)
		{
			m_player->m_position.y += (int)m_player->m_speed;
			m_player->m_depth = m_player->m_position.y;
			UpdateColliderPosition();

			if (m_player->m_face_right)
			{
				if (m_player->m_current_animation != &(m_player->m_weapon_knife_walk_right))
				{
					m_player->m_weapon_knife_walk_right.Reset();
					m_player->m_current_animation = &(m_player->m_weapon_knife_walk_right);
				}
			}
			else
			{
				if (m_player->m_current_animation != &(m_player->m_weapon_knife_walk_left))
				{
					m_player->m_weapon_knife_walk_left.Reset();
					m_player->m_current_animation = &(m_player->m_weapon_knife_walk_left);
				}
			}
		}
	}

	if (m_player->m_state == player_state::IDLE || 
		m_player->m_state == player_state::WALKING  &&
		App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE &&
		App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE &&
		App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE &&
		App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE &&
		App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE &&
		App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE &&
		App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE)
	{
		if (m_player->m_state != player_state::IDLE)
		{
			m_player->m_state = player_state::IDLE;
			m_player->m_restart_animation = true;
			m_player->m_timer_count = 0.0f;
		}

		if (m_player->m_state == player_state::IDLE)
		{
			if (m_player->m_carrying_weapon_pipe == true)
			{
				m_player->m_state = player_state::WEAPON_PIPE_IDLE;
				m_player->m_restart_animation = true;
				m_player->m_position.y -= 14;

			}	
		}

		if (m_player->m_state == player_state::IDLE)
		{
			if (m_player->m_carrying_weapon_knife == true)
			{
				m_player->m_state = player_state::WEAPON_KNIFE_IDLE;
				m_player->m_restart_animation = true;
				
			}
		}
	}

	if (m_player->m_state == player_state::IDLE)
	{
		if (m_player->m_face_right)
		{
			if (m_player->m_restart_animation)
			{
				m_player->m_current_animation = &(m_player->m_idle_right1);
				m_player->m_restart_animation = false;
			}
			if (m_player->m_current_animation == &(m_player->m_idle_right1))
			{
				if (m_player->m_current_animation->Finished())
				{
					m_player->m_current_animation->Reset();
					m_player->m_current_animation = &(m_player->m_idle_right2);
				}
			}
			if (m_player->m_current_animation == &(m_player->m_idle_right2))
			{
				if (m_player->m_current_animation->Finished())
				{
					m_player->m_current_animation->Reset();
					m_player->m_current_animation = &(m_player->m_idle_right3);
				}
			}
			if (m_player->m_current_animation == &(m_player->m_idle_right3))	
			{
				if (m_player->m_current_animation->Finished())
				{
					m_player->m_current_animation->Reset();
					m_player->m_current_animation = &(m_player->m_idle_right1);
					m_player->m_restart_animation = true;
				}
			}
		}
		else
		{
			if (m_player->m_restart_animation)
			{
				m_player->m_current_animation = &(m_player->m_idle_left1);
				m_player->m_restart_animation = false;
			}
			if (m_player->m_current_animation == &(m_player->m_idle_left1))
			{
				if (m_player->m_current_animation->Finished())
				{
					m_player->m_current_animation->Reset();
					m_player->m_current_animation = &(m_player->m_idle_left2);
				}
			}

			if (m_player->m_current_animation == &(m_player->m_idle_left2))
			{
				if (m_player->m_current_animation->Finished())
				{
					m_player->m_current_animation->Reset();
					m_player->m_current_animation = &(m_player->m_idle_left3);
				}
			}
				
			if (m_player->m_current_animation == &(m_player->m_idle_left3))
			{
				if (m_player->m_current_animation->Finished())
				{
					m_player->m_current_animation->Reset();
					m_player->m_current_animation = &(m_player->m_idle_left1);
				}
			}
		}
	}

	
	bool idle_condition =	(m_player->m_state == player_state::WEAPON_PIPE_IDLE ||
							m_player->m_state == player_state::WEAPON_PIPE_WALKING ||
							m_player->m_state == player_state::WEAPON_KNIFE_IDLE ||
							m_player->m_state == player_state::WEAPON_KNIFE_WALKING) 
							&&
						    (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE &&
							App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE &&
							App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE &&
							App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE &&
							App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE &&
							App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE &&
							App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE);

	if (idle_condition)
	{
		
		if(m_player->m_carrying_weapon_pipe)
		{
			m_player->m_state = player_state::WEAPON_PIPE_IDLE;

			if (m_player->m_face_right)
			{
				m_player->m_current_animation = &(m_player->m_weapon_pipe_idle_right);

			}
			else
			{
				m_player->m_current_animation = &(m_player->m_weapon_pipe_idle_left);
			}
		}

		if (m_player->m_carrying_weapon_knife)
		{
			m_player->m_state = player_state::WEAPON_KNIFE_IDLE;
			
			if (m_player->m_face_right)
			{
				m_player->m_current_animation = &(m_player->m_weapon_knife_idle_right);

			}
			else
			{
				m_player->m_current_animation = &(m_player->m_weapon_knife_idle_left);
			}
		}
		//Revisarlo cuando tenga estados de haber sido atacado
		/*if (player->m_state == player_state::WEAPON_PIPE_IDLE && player->m_carrying_weapon_pipe == false)
		{
			player->m_state = player_state::IDLE;
			player->m_restart_animation = true;
			player->m_position.y += 14;
		}
		if (player->m_state == player_state::WEAPON_KNIFE_IDLE && player->m_carrying_weapon_knife == false)
		{
			player->m_state = player_state::IDLE;
			player->m_restart_animation = true;
		}*/

	}
	
	if (m_player->m_state == player_state::WEAPON_PIPE_ATTACK_RIGHT)
	{
		m_player->m_current_animation = &(m_player->m_weapon_pipe_attack_right);
		if (m_player->m_current_animation->Finished())
		{
			m_player->m_current_animation->Reset();
			m_player->m_state = player_state::WEAPON_PIPE_IDLE;
		}
	}

	if (m_player->m_state == player_state::WEAPON_PIPE_ATTACK_LEFT)
	{
		m_player->m_current_animation = &(m_player->m_weapon_pipe_attack_left);
		if (m_player->m_current_animation->Finished())
		{
			m_player->m_current_animation->Reset();
			m_player->m_state = player_state::WEAPON_PIPE_IDLE;
		}
	}

	
	if (m_player->m_state == player_state::WEAPON_KNIFE_ATTACK_RIGHT)
	{
		m_player->m_current_animation = &(m_player->m_weapon_knife_attack_right);
		if (m_player->m_current_animation->Finished())
		{
			m_player->m_current_animation->Reset();
			m_player->m_state = player_state::WEAPON_KNIFE_IDLE;
		}
	}

	if (m_player->m_state == player_state::WEAPON_KNIFE_ATTACK_LEFT)
	{
		m_player->m_current_animation = &(m_player->m_weapon_knife_attack_left);
		if (m_player->m_current_animation->Finished())
		{
			m_player->m_current_animation->Reset();
			m_player->m_state = player_state::WEAPON_KNIFE_IDLE;
		}
	}

	if (m_player->m_state == player_state::DAMAGED)
	{
		//In case player is hit while jumping, speed returns to initial speed
		m_player->m_speed = 1.0f;
		Enemy* enemy = m_player->m_enemy_attacking_player;
		
			
			if (enemy->m_face_right)
				m_player->m_face_right = false;

			if (enemy->m_face_right == false)
				m_player->m_face_right = true;


			if (!strcmp(enemy->m_name, "garcia"))
			{
				if (enemy->m_floating_attack == false)
				{
					if (m_player->m_face_right)
					{
						m_player->m_current_animation = &(m_player->m_damage_received_right);
						if (m_player->m_current_animation->Finished())
						{
							if (m_player->m_dead == false)
							{
								m_player->m_current_animation->Reset();
								m_player->m_state = player_state::IDLE;
								m_player->m_current_animation = &(m_player->m_idle_right1);
								
							}
						}
					}
					if (m_player->m_face_right == false)
					{
						m_player->m_current_animation = &(m_player->m_damage_received_left);
						if (m_player->m_current_animation->Finished())
						{
							if (m_player->m_dead == false)
							{
								m_player->m_current_animation->Reset();
								m_player->m_state = player_state::IDLE;
								m_player->m_current_animation = &(m_player->m_idle_left1);
								
							}
						}
					}
				}
				if (enemy->m_floating_attack == true)
				{
					if (m_player->m_face_right)
					{
						m_player->m_current_animation = &(m_player->m_down_right);
						if (m_player->m_current_animation->Finished())
						{
							if (m_player->m_dead == false)
							{
								m_player->m_current_animation->Reset();
								m_player->m_state = player_state::UP;
								m_player->m_current_animation = &(m_player->m_up_right);
								
							}
						}

					}
					if (m_player->m_face_right == false)
					{
						m_player->m_current_animation = &(m_player->m_down_left);
						if (m_player->m_current_animation->Finished())
						{
							if (m_player->m_dead == false)
							{
								m_player->m_current_animation->Reset();
								m_player->m_state = player_state::UP;
								m_player->m_current_animation = &(m_player->m_up_left);
								
							}
						}
					}
				}
			}

			if (!strcmp(enemy->m_name, "garcia_knife"))
			{
				if (m_player->m_face_right)
					m_player->m_current_animation = &(m_player->m_damage_received_right);
				else
					m_player->m_current_animation = &(m_player->m_damage_received_left);

				if (m_player->m_current_animation->Finished())
				{
					if (m_player->m_dead == false)
					{
						m_player->m_current_animation->Reset();
						m_player->m_state = player_state::IDLE;
						

						if (m_player->m_face_right)
							m_player->m_current_animation = &(m_player->m_idle_right1);
						else
							m_player->m_current_animation = &(m_player->m_idle_left1);
					}
				}
			}

			if (!strcmp(enemy->m_name, "punky"))
			{
				if (m_player->m_face_right)
				{
					m_player->m_current_animation = &(m_player->m_down_right);
					if (m_player->m_current_animation->Finished())
					{
						if (m_player->m_dead == false)
						{
							m_player->m_current_animation->Reset();
							m_player->m_state = player_state::UP;
							m_player->m_current_animation = &(m_player->m_up_right);
							
						}
					}

				}
				if (m_player->m_face_right == false)
				{
					m_player->m_current_animation = &(m_player->m_down_left);
					if (m_player->m_current_animation->Finished())
					{
						if (m_player->m_dead == false)
						{
							m_player->m_current_animation->Reset();
							m_player->m_state = player_state::UP;
							m_player->m_current_animation = &(m_player->m_up_left);
							
						}
					}
				}
			}

			if (!strcmp(enemy->m_name, "nora"))
			{
				if (m_player->m_face_right)
				{
					m_player->m_current_animation = &(m_player->m_down_right);
					if (m_player->m_current_animation->Finished())
					{
						if (m_player->m_dead == false)
						{
							m_player->m_current_animation->Reset();
							m_player->m_state = player_state::UP;
							m_player->m_current_animation = &(m_player->m_up_right);
						}
					}

				}
				if (m_player->m_face_right == false)
				{
					m_player->m_current_animation = &(m_player->m_down_left);
					if (m_player->m_current_animation->Finished())
					{
						if (m_player->m_dead == false)
						{
							m_player->m_current_animation->Reset();
							m_player->m_state = player_state::UP;
							m_player->m_current_animation = &(m_player->m_up_left);
						}
					}
				}
			}

			if (!strcmp(enemy->m_name, "antonio"))
			{
				if (m_player->m_face_right)
					m_player->m_current_animation = &(m_player->m_damage_received_right);
				else
					m_player->m_current_animation = &(m_player->m_damage_received_left);

				if (m_player->m_current_animation->Finished())
				{
					if (m_player->m_dead == false)
					{
						m_player->m_current_animation->Reset();
						m_player->m_state = player_state::IDLE;

						if (m_player->m_face_right)
							m_player->m_current_animation = &(m_player->m_idle_right1);
						else
							m_player->m_current_animation = &(m_player->m_idle_left1);
					}
				}
			}
		
	}

	if (m_player->m_state == player_state::UP)
	{
		if (m_player->m_face_right)
			m_player->m_current_animation = &(m_player->m_up_right);
		else
			m_player->m_current_animation = &(m_player->m_up_left);

		if (m_player->m_current_animation->Finished())
		{
			m_player->m_current_animation->Reset();
			m_player->m_state = player_state::IDLE;
			if (m_player->m_face_right)
				m_player->m_current_animation = &(m_player->m_idle_right1);
			else
				m_player->m_current_animation = &(m_player->m_idle_left1);

			Enemy* enemy = m_player->m_enemy_attacking_player;
			enemy->m_floating_attack = false;
			
		}
	}

}
	

	// Draw everything --------------------------------------

	App->renderer->Blit(m_player->m_texture, m_player->m_position.x, m_player->m_position.y, &(m_player->m_current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}


void ModulePlayer::UpdateColliderPosition()
{
	m_player_collider->SetPos(m_player->m_position.x + m_player->m_x_ref - m_player_collider->m_rect.w / 2, m_player->m_depth);
}

bool ModulePlayer::LookingEachOther(Enemy *enemy)
{
	bool ret = false;
	int vector_x = enemy->m_position.x - m_player->m_position.x;
	
	if (vector_x > 0 && m_player->m_face_right)
		ret = true;

	if (vector_x < 0 && m_player->m_face_right == false)
		ret = true;


	return ret;
}

