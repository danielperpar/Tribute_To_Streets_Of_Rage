#include "AIController.h"
#include "Enemy.h"
#include "Player.h"
#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"

AIController::AIController() {}
AIController::AIController(Enemy *owner) : m_ai_owner_enemy(owner){}
AIController::~AIController() {}

void AIController::UpdateBehaviour()
{
	//Refactorizar cuando tenga colisiones

	//All npc except boss antonio and boomerang
	if (strcmp(m_ai_owner_enemy->m_name, "antonio") && strcmp(m_ai_owner_enemy->m_name, "boomerang"))
	{
		
		m_vector_enemy_to_player = { m_player->m_position.x + 14 - m_ai_owner_enemy->m_position.x - 9, m_player->m_position.y - m_ai_owner_enemy->m_position.y };

		if (m_vector_enemy_to_player.x > 0)
			m_sign_x = 1;

		if (m_vector_enemy_to_player.x == 0)
			m_sign_x = 0;

		if (m_vector_enemy_to_player.x < 0)
			m_sign_x = -1;

		if (m_vector_enemy_to_player.y > 0)
			m_sign_y = 1;

		if (m_vector_enemy_to_player.y == 0)
			m_sign_y = 0;

		if (m_vector_enemy_to_player.y < 0)
			m_sign_y = -1;

		if (m_sign_x <= 0)
			m_ai_owner_enemy->m_face_right = false;

		if (m_sign_x > 0)
			m_ai_owner_enemy->m_face_right = true;

	
		if (m_ai_owner_enemy->m_ai_walk == true)
		{

			bool grab_condition = (
				m_player->m_state == player_state::GRAB ||
				m_player->m_state == player_state::GRAB_KICK ||
				m_player->m_state == player_state::GRAB_HEAD_HIT ||
				m_player->m_state == player_state::GRAB_AIR_SPIN_RIGHT ||
				m_player->m_state == player_state::GRAB_AIR_SPIN_LEFT ||
				m_player->m_state == player_state::GRAB_AIR_SPIN_FINISHER_RIGHT ||
				m_player->m_state == player_state::GRAB_AIR_SPIN_FINISHER_LEFT);

			if (!grab_condition)
			{
				m_ai_owner_enemy->m_position.x = (int)(m_ai_owner_enemy->m_position.x + m_sign_x);
				App->enemies->UpdateColliderPosition(m_ai_owner_enemy);
			}

			if (m_player->m_state != player_state::JUMPING && m_player->m_state != player_state::JUMPING_KICKING && !grab_condition)
			{
				m_t_acum += m_speed_y;

				if (m_t_acum >= 1.0f)
				{
					m_t_acum = 0.0f;
					m_ai_owner_enemy->m_position.y = (int)(m_ai_owner_enemy->m_position.y + m_sign_y);
					m_ai_owner_enemy->m_depth = m_ai_owner_enemy->m_position.y;
					App->enemies->UpdateColliderPosition(m_ai_owner_enemy);
				}
			}

		}
	}
	//boss
	if (!strcmp(m_ai_owner_enemy->m_name, "antonio"))
	{

		m_vector_enemy_to_player = { m_player->m_position.x + 14 - m_ai_owner_enemy->m_position.x - 9, m_player->m_position.y - m_ai_owner_enemy->m_position.y - 51 };

		if (m_vector_enemy_to_player.x > 0)
			m_sign_x = 1;

		if (m_vector_enemy_to_player.x == 0)
			m_sign_x = 0;

		if (m_vector_enemy_to_player.x < 0)
			m_sign_x = -1;

		if (m_vector_enemy_to_player.y > 0)
			m_sign_y = 1;

		if (m_vector_enemy_to_player.y == 0)
			m_sign_y = 0;

		if (m_vector_enemy_to_player.y < 0)
			m_sign_y = -1;

		if (m_sign_x <= 0)
			m_ai_owner_enemy->m_face_right = false;

		if (m_sign_x > 0)
			m_ai_owner_enemy->m_face_right = true;

		
		if (m_ai_owner_enemy->m_ai_walk == true)
		{
			bool grab_condition = (
				m_player->m_state == player_state::GRAB ||
				m_player->m_state == player_state::GRAB_KICK ||
				m_player->m_state == player_state::GRAB_HEAD_HIT ||
				m_player->m_state == player_state::GRAB_AIR_SPIN_RIGHT ||
				m_player->m_state == player_state::GRAB_AIR_SPIN_LEFT ||
				m_player->m_state == player_state::GRAB_AIR_SPIN_FINISHER_RIGHT ||
				m_player->m_state == player_state::GRAB_AIR_SPIN_FINISHER_LEFT);

			if (!grab_condition)
			{
				m_ai_owner_enemy->m_position.x = (int)(m_ai_owner_enemy->m_position.x + m_sign_x);
				App->enemies->UpdateColliderPosition(m_ai_owner_enemy);
			}

			if (m_player->m_state != player_state::JUMPING && m_player->m_state != player_state::JUMPING_KICKING && !grab_condition)
			{
				m_t_acum += m_speed_y;

				if (m_t_acum >= 1.0f)
				{
					m_t_acum = 0.0f;
					m_ai_owner_enemy->m_position.y = (int)(m_ai_owner_enemy->m_position.y + m_sign_y);
					m_ai_owner_enemy->m_depth = m_ai_owner_enemy->m_position.y;
					App->enemies->UpdateColliderPosition(m_ai_owner_enemy);
				}
			}

		}
	}

	
	
}

void AIController::UpdateBehaviour(Particle *boomerang, Entity *owner)
{
		
	if (boomerang->m_forward)
	{
		if (((Enemy*)owner)->m_face_right)
		{
			boomerang->m_position.x += (int)boomerang->m_speed_x;
			
			//update collider position
			boomerang->m_collider->SetPos(boomerang->m_position.x + m_x_ref - boomerang->m_collider->m_rect.w / 2, boomerang->m_depth);
			

			if (boomerang->m_start_position.x - boomerang->m_position.x >= -160)
			{
				boomerang->m_forward = false;
			}

		}
		else
		{
			boomerang->m_position.x -= (int)boomerang->m_speed_x;
			
			//update collider position
			boomerang->m_collider->SetPos(boomerang->m_position.x + m_x_ref - boomerang->m_collider->m_rect.w / 2, boomerang->m_depth);

			if (boomerang->m_start_position.x - boomerang->m_position.x >= 160)
			{
				boomerang->m_forward = false;
			}
		}
	}

	if (boomerang->m_forward == false)
	{
		if (m_ai_owner_enemy->m_face_right)
			m_vector_boomerang_to_boss = { owner->m_position.x + 30 - boomerang->m_position.x, owner->m_position.y + m_y_ref - boomerang->m_position.y };
		else
			m_vector_boomerang_to_boss = { owner->m_position.x - 40 - boomerang->m_position.x, owner->m_position.y + m_y_ref - boomerang->m_position.y };


		if (m_vector_boomerang_to_boss.x > 0)
			m_sign_x = 1;

		if (m_vector_boomerang_to_boss.x == 0)
			m_sign_x = 0;

		if (m_vector_boomerang_to_boss.x < 0)
			m_sign_x = -1;

		if (m_vector_boomerang_to_boss.y > 0)
			m_sign_y = 1;

		if (m_vector_boomerang_to_boss.y == 0)
			m_sign_y = 0;

		if (m_vector_boomerang_to_boss.y < 0)
			m_sign_y = -1;

		if (m_sign_x <= 0)
			boomerang->m_face_right = false;

		if (m_sign_x > 0)
			boomerang->m_face_right = true;

		
		boomerang->m_position.x = (int)(boomerang->m_position.x + 2 * m_sign_x);
		
		//update collider position
		boomerang->m_collider->SetPos(boomerang->m_position.x + m_x_ref - boomerang->m_collider->m_rect.w / 2, boomerang->m_depth);

		m_t_acum += boomerang->m_speed_y;

		if (m_t_acum >= 1.0f)
		{
			m_t_acum = 0.0f;
			boomerang->m_position.y = (int)(boomerang->m_position.y + m_sign_y);
			boomerang->m_depth = boomerang->m_position.y;
			
			//update collider position
			boomerang->m_collider->SetPos(boomerang->m_position.x + m_x_ref - boomerang->m_collider->m_rect.w / 2, boomerang->m_depth);
		}

		//El enemigo recogerá el boomerang cuando éste colisione con él.

	}
}


	
	


