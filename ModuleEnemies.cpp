#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"
#include "EntityManager.h"
#include "Entity.h"
#include "ModulePlayer.h"



ModuleEnemies::ModuleEnemies(bool active) : Module(active) {}


ModuleEnemies::~ModuleEnemies()
{}

// Load assets
bool ModuleEnemies::Start()
{

	LOG("Loading enemy");
	graphics = App->textures->Load("assets/spritesheets/enemies.png");
	m_player = App->player->m_player;

	/*m_enemy = (Enemy*)EntityManager::CreateEntity(graphics, "garcia", entity_type::ENEMY, { 1000, 100 }, 100);
	m_enemy->m_state = enemy_state::IDLE;
	m_enemy->m_ai_controller.m_enemy = m_enemy;
	m_enemy->m_ai_controller.m_player = App->player->m_player;
	

	SDL_Rect collider;
	collider.x = 0;
	collider.y = 0;
	collider.w = 15;
	collider.h = 63;
	m_enemy_grab_collider = App->collision->AddCollider(collider, nullptr, collider_type::COMMON_ENEMY_GRAB);
	m_enemy_grab_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_grab_collider->m_rect.w / 2, m_enemy->m_depth);

	collider.x = 0;
	collider.y = 0;
	collider.w = 30;
	collider.h = 63;
	m_enemy_hit_collider = App->collision->AddCollider(collider, nullptr, collider_type::COMMON_ENEMY_HIT);
	m_enemy_hit_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_hit_collider->m_rect.w / 2, m_enemy->m_depth);*/

	/*m_enemy = (Enemy*)EntityManager::CreateEntity(graphics, "garcia_knife", entity_type::ENEMY, { 1000, 100 }, 100);
	m_enemy->m_state = enemy_state::IDLE;
	m_enemy->m_ai_controller.m_enemy = m_enemy;
	m_enemy->m_ai_controller.m_player = App->player->m_player;


	SDL_Rect collider;
	collider.x = 0;
	collider.y = 0;
	collider.w = 15;
	collider.h = 63;
	m_enemy_grab_collider = App->collision->AddCollider(collider, m_enemy, collider_type::COMMON_ENEMY_GRAB);
	m_enemy_grab_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_grab_collider->m_rect.w / 2, m_enemy->m_depth);

	collider.x = 0;
	collider.y = 0;
	collider.w = 35;
	collider.h = 63;
	m_enemy_hit_collider = App->collision->AddCollider(collider, m_enemy, collider_type::COMMON_ENEMY_HIT);
	m_enemy_hit_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_hit_collider->m_rect.w / 2, m_enemy->m_depth);*/


	/*m_enemy = (Enemy*)EntityManager::CreateEntity(graphics, "punky", entity_type::ENEMY, { 1000, 100 }, 100);
	m_enemy->m_state = enemy_state::IDLE;
	m_enemy->m_ai_controller.m_enemy = m_enemy;
	m_enemy->m_ai_controller.m_player = App->player->m_player;

	SDL_Rect collider;
	collider.x = 0;
	collider.y = 0;
	collider.w = 15;
	collider.h = 63;
	m_enemy_grab_collider = App->collision->AddCollider(collider, nullptr, collider_type::COMMON_ENEMY_GRAB);
	m_enemy_grab_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_grab_collider->m_rect.w / 2, m_enemy->m_depth);

	collider.x = 0;
	collider.y = 0;
	collider.w = 130;
	collider.h = 63;
	m_enemy_hit_collider = App->collision->AddCollider(collider, nullptr, collider_type::COMMON_ENEMY_HIT);
	m_enemy_hit_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_hit_collider->m_rect.w / 2, m_enemy->m_depth);*/

	m_enemy = (Enemy*)EntityManager::CreateEntity(graphics, "nora", entity_type::ENEMY, { 1000, 100 }, 100);
	m_enemy->m_state = enemy_state::IDLE;
	m_enemy->m_ai_controller.m_enemy = m_enemy;
	m_enemy->m_ai_controller.m_player = App->player->m_player;

	SDL_Rect collider;
	collider.x = 0;
	collider.y = 0;
	collider.w = 15;
	collider.h = 63;
	m_enemy_grab_collider = App->collision->AddCollider(collider, nullptr, collider_type::COMMON_ENEMY_GRAB);
	m_enemy_grab_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_grab_collider->m_rect.w / 2, m_enemy->m_depth);

	collider.x = 0;
	collider.y = 0;
	collider.w = 100;
	collider.h = 63;
	m_enemy_hit_collider = App->collision->AddCollider(collider, nullptr, collider_type::COMMON_ENEMY_HIT);
	m_enemy_hit_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_hit_collider->m_rect.w / 2, m_enemy->m_depth);



	
	return true;
}

// Unload assets
bool ModuleEnemies::CleanUp()
{
	LOG("Unloading enemies");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleEnemies::Update()
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

	
	for (auto it = App->entities.begin(); it != App->entities.end(); it++)
	{
		if ((*it)->m_type == entity_type::ENEMY)
		{
			m_enemy = (Enemy*)*it;


			if (m_enemy->m_ai_attack)
			{
				if (m_enemy->m_state == enemy_state::WALKING)
					m_enemy->m_state = enemy_state::IDLE;
				
				if( m_enemy->m_state == enemy_state::IDLE )
				{
					if (!strcmp(m_enemy->m_name, "garcia"))
					{
						if (m_enemy->m_punch_hits < 2)
						{
							if (App->player->m_player_collider->CheckCollision(m_enemy_hit_collider->m_rect) == true && m_enemy->m_depth == m_player->m_depth)
							{
								m_enemy->m_state = enemy_state::PUNCH1;
								m_enemy->m_floating_attack = false;
								m_player->m_state = player_state::DAMAGED;
							}
							else
							{
								m_enemy->m_punch_hits = 0;
								m_enemy->m_ai_attack = false;
								m_enemy->m_ai_walk = true;								
								m_enemy->m_state = enemy_state::WALKING;
							}
						}
						if (m_enemy->m_punch_hits == 2)
						{
							if (App->player->m_player_collider->CheckCollision(m_enemy_hit_collider->m_rect) == true && m_enemy->m_depth == m_player->m_depth)
							{
								m_enemy->m_state = enemy_state::PUNCH2;
								m_enemy->m_floating_attack = true;
								m_player->m_state = player_state::DAMAGED;
							}
								
							else
							{
								m_enemy->m_ai_attack = false;
								m_enemy->m_ai_walk = true;								
								m_enemy->m_state = enemy_state::WALKING;
							}
						}
						if (m_enemy->m_punch_hits == 3)
						{
							m_enemy->m_floating_attack = false;
						}
					}
					if (!strcmp(m_enemy->m_name, "garcia_knife"))
					{
						if (m_enemy->m_allow_attack)
						{
							if (App->player->m_player_collider->CheckCollision(m_enemy_hit_collider->m_rect) == true &&	m_enemy->m_depth == m_player->m_depth)
							{
								m_enemy->m_state = enemy_state::KNIFE_ATTACK;
								m_player->m_state = player_state::DAMAGED;
							}
							else
							{
								m_enemy->m_ai_attack = false;
								m_enemy->m_ai_walk = true;
								m_enemy->m_state = enemy_state::WALKING;
							}
						}
					}
					if (!strcmp(m_enemy->m_name, "punky"))
					{
						if (m_enemy->m_allow_attack)
						{
							if (App->player->m_player_collider->CheckCollision(m_enemy_hit_collider->m_rect) == true && m_enemy->m_depth == m_player->m_depth)
							{
								m_enemy->m_state = enemy_state::GROUND_ATTACK;
								m_enemy->m_floating_attack = true;
							}
							else
							{
								m_enemy->m_ai_attack = false;
								m_enemy->m_ai_walk = true;
								m_enemy->m_state = enemy_state::WALKING;
							}
						}
					}
					if (!strcmp(m_enemy->m_name, "nora"))
					{
						if (m_enemy->m_allow_attack)
						{
							if (App->player->m_player_collider->CheckCollision(m_enemy_hit_collider->m_rect) == true && m_enemy->m_depth == m_player->m_depth)
							{
								m_enemy->m_state = enemy_state::WHIP_ATTACK;
								m_enemy->m_floating_attack = true;
							}
							else
							{
								m_enemy->m_ai_attack = false;
								m_enemy->m_ai_walk = true;
								m_enemy->m_state = enemy_state::WALKING;
							}
						}
					}
					if (!strcmp(m_enemy->m_name, "antonio"))
					{
						if (m_enemy->m_carrying_boomerang == false)
							m_enemy->m_state = enemy_state::KICK;
					}
				}
			}

			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{
				if (!strcmp(m_enemy->m_name, "antonio"))
				{
					if(m_enemy->m_carrying_boomerang)
						m_enemy->m_state = enemy_state::THROW_BOOMERANG;
				}
			}
			if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
			{
				if (!strcmp(m_enemy->m_name, "antonio"))
				{
					if (m_enemy->m_carrying_boomerang == false)
						m_enemy->m_state = enemy_state::RECOVER_BOOMERANG;
				}
			}
				
			
			//Inputs will be substituted by AI signals
			if (m_enemy->m_state == enemy_state::IDLE ||
				m_enemy->m_state == enemy_state::WALKING  &&
				App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE &&
				App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE &&
				App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE &&
				App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE &&
				App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE &&
				App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE &&
				App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE &&
				m_enemy->m_ai_walk == false &&
				m_enemy->m_ai_attack == false)
			{
				m_enemy->m_state = enemy_state::IDLE;
			}

			if (m_enemy->m_state == enemy_state::IDLE)
			{

				if (!strcmp(m_enemy->m_name, "garcia"))
				{
					m_enemy->m_current_animation = m_enemy->m_face_right ? &(m_enemy->m_npc_garcia_idle_right) : &(m_enemy->m_npc_garcia_idle_left);
					if (m_enemy->m_punch_hits == 3)
					{
						m_enemy->m_counter++;
						if (m_enemy->m_counter == m_time_to_next_attack)
						{
								m_enemy->m_punch_hits = 0;
								m_enemy->m_counter = 0;
						}
					}

				}
				if (!strcmp(m_enemy->m_name, "garcia_knife"))
				{
					m_enemy->m_current_animation = m_enemy->m_face_right ? &(m_enemy->m_npc_garcia_knife_idle_right) : &(m_enemy->m_npc_garcia_knife_idle_left);
					m_enemy->m_counter++;
					if (m_enemy->m_counter == m_time_to_next_attack)
					{
						m_enemy->m_counter = 0;
						m_enemy->m_allow_attack = true;
					}

				}
				if (!strcmp(m_enemy->m_name, "punky"))
				{
					m_enemy->m_current_animation = m_enemy->m_face_right ? &(m_enemy->m_npc_punky_idle_right) : &(m_enemy->m_npc_punky_idle_left);
					m_enemy->m_counter++;
					if (m_enemy->m_counter == m_time_to_next_attack)
					{
						m_enemy->m_counter = 0;
						m_enemy->m_allow_attack = true;
					}
				}
				if (!strcmp(m_enemy->m_name, "nora"))
				{
					m_enemy->m_current_animation = m_enemy->m_face_right ? &(m_enemy->m_npc_nora_idle_right) : &(m_enemy->m_npc_nora_idle_left);
					m_enemy->m_counter++;
					if (m_enemy->m_counter == m_time_to_next_attack)
					{
						m_enemy->m_counter = 0;
						m_enemy->m_allow_attack = true;
					}
				}
				if (!strcmp(m_enemy->m_name, "antonio"))
				{
					if (m_enemy->m_face_right)
					{
						if (m_enemy->m_carrying_boomerang)
							m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_boomerang_idle_right);
						else
							m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_idle_right);
					}
					else
					{
						if (m_enemy->m_carrying_boomerang)
							m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_boomerang_idle_left);
						else
							m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_idle_left);
					}
				}
			}

			if (m_enemy->m_ai_walk)
			{
				
				if (m_enemy->m_state == enemy_state::IDLE || m_enemy->m_state == enemy_state::WALKING)
				{
					m_enemy->m_state = enemy_state::WALKING;
					
					if (!strcmp(m_enemy->m_name, "garcia"))
					{
						if (m_enemy->m_face_right)
						{
							if (m_enemy->m_current_animation != &(m_enemy->m_npc_garcia_walk_right))
							{
								m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_walk_right);
								m_enemy->m_current_animation->Reset();
							}
						}
						else
						{
							if (m_enemy->m_current_animation != &(m_enemy->m_npc_garcia_walk_left))
							{
								m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_walk_left);
								m_enemy->m_current_animation->Reset();
							}
						}
					}
					if (!strcmp(m_enemy->m_name, "garcia_knife"))
					{
						if (m_enemy->m_face_right)
						{
							if (m_enemy->m_current_animation != &(m_enemy->m_npc_garcia_knife_walk_right))
							{
								m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_knife_walk_right);
								m_enemy->m_current_animation->Reset();
							}
						}
						else
						{
							if (m_enemy->m_current_animation != &(m_enemy->m_npc_garcia_knife_walk_left))
							{
								m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_knife_walk_left);
								m_enemy->m_current_animation->Reset();
							}
						}
							
					}
					if (!strcmp(m_enemy->m_name, "punky"))
					{
						if (m_enemy->m_face_right)
						{
							if (m_enemy->m_current_animation != &(m_enemy->m_npc_punky_walk_right))
							{
								m_enemy->m_current_animation = &(m_enemy->m_npc_punky_walk_right);
								m_enemy->m_current_animation->Reset();
							}
						}
						else
						{
							if (m_enemy->m_current_animation != &(m_enemy->m_npc_punky_walk_left))
							{
								m_enemy->m_current_animation = &(m_enemy->m_npc_punky_walk_left);
								m_enemy->m_current_animation->Reset();
							}
						}		
					}
					if (!strcmp(m_enemy->m_name, "nora"))
					{
						if (m_enemy->m_face_right)
						{
							if (m_enemy->m_current_animation != &(m_enemy->m_npc_nora_walk_right))
							{
								m_enemy->m_current_animation = &(m_enemy->m_npc_nora_walk_right);
								m_enemy->m_current_animation->Reset();
							}
						}
						else
						{
							if (m_enemy->m_current_animation != &(m_enemy->m_npc_nora_walk_left))
							{
								m_enemy->m_current_animation = &(m_enemy->m_npc_nora_walk_left);
								m_enemy->m_current_animation->Reset();
							}
						}		
					}
					if (!strcmp(m_enemy->m_name, "antonio"))
					{
						if (m_enemy->m_carrying_boomerang)
						{
							if (m_enemy->m_face_right)
							{
								if (m_enemy->m_current_animation != &(m_enemy->m_npc_antonio_boomerang_walk_right))
								{
									m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_boomerang_walk_right);
									m_enemy->m_current_animation->Reset();
								}
							}
							else
							{
								if (m_enemy->m_current_animation != &(m_enemy->m_npc_antonio_boomerang_walk_left))
								{
									m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_boomerang_walk_left);
									m_enemy->m_current_animation->Reset();
								}
							}		
						}
						else
						{
							if (m_enemy->m_face_right)
							{
								if (m_enemy->m_current_animation != &(m_enemy->m_npc_antonio_walk_right))
								{
									m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_walk_right);
									m_enemy->m_current_animation->Reset();
								}
							}
							else
							{
								if (m_enemy->m_current_animation != &(m_enemy->m_npc_antonio_walk_left))
								{
									m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_walk_left);
									m_enemy->m_current_animation->Reset();
								}
							}
							
						}
					}
				}
			}

			//Only garcia enters punch1,punch2 states
			if (m_enemy->m_state == enemy_state::PUNCH1)
			{
				if (m_enemy->m_face_right)
				{
					m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_punch_right1);

					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_punch_hits++;
						m_enemy->m_state = enemy_state::IDLE;
						m_enemy->m_current_animation->Reset();
					}
				}
				else
				{
					m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_punch_left1);

					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_punch_hits++;
						m_enemy->m_state = enemy_state::IDLE;
						m_enemy->m_current_animation->Reset();						
					}

				}
			}

			if (m_enemy->m_state == enemy_state::PUNCH2)
			{
				if (m_enemy->m_face_right)
				{
					m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_punch_right2);

					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_punch_hits++;
						m_enemy->m_state = enemy_state::IDLE;
						m_enemy->m_current_animation->Reset();
						m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_idle_right);
					}
				}
				else
				{
					m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_punch_left2);

					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_punch_hits++;
						m_enemy->m_state = enemy_state::IDLE;
						m_enemy->m_current_animation->Reset();
						m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_idle_left);
					}
				}
			}
			//Only garcia_knife enters knife_attack state
			if (m_enemy->m_state == enemy_state::KNIFE_ATTACK)
			{
				if (m_enemy->m_face_right)
					m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_knife_attack_right);
				else
					m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_knife_attack_left);

				if (m_enemy->m_current_animation->Finished())
				{
					m_enemy->m_state = enemy_state::IDLE;
					m_enemy->m_current_animation->Reset();
					m_enemy->m_allow_attack = false;

					if (m_enemy->m_face_right)
						m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_knife_idle_right);
					else
						m_enemy->m_current_animation = &(m_enemy->m_npc_garcia_knife_idle_left);
				}
			}
			//Only punky enters ground_attack state
			if (m_enemy->m_state == enemy_state::GROUND_ATTACK)
			{
				if (m_enemy->m_restart_animation)
				{
					m_enemy->m_timer_count = 0;
					m_enemy->m_restart_animation = false;

					if (m_enemy->m_face_right)
						m_enemy->m_current_animation = &(m_enemy->m_npc_punky_ground_attack_right1);
					else
						m_enemy->m_current_animation = &(m_enemy->m_npc_punky_ground_attack_left1);
				}

				//face right
				if (m_enemy->m_current_animation == &(m_enemy->m_npc_punky_ground_attack_right1) && m_enemy->m_timer_count == 0)
				{
					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_current_animation->Reset();
						m_enemy->m_current_animation = &(m_enemy->m_npc_punky_ground_attack_right2);
					}
				}
				if (m_enemy->m_current_animation == &(m_enemy->m_npc_punky_ground_attack_right2))
				{
					m_enemy->m_position.x += m_enemy->m_ground_attack_speed;
					UpdateColliderPosition();
					m_enemy->m_timer_count++;

					//move grab collider to the feet
					m_enemy_grab_collider->SetPos((m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_grab_collider->m_rect.w / 2) + 50, m_enemy->m_depth);
					if (App->player->m_player_collider->CheckCollision(m_enemy_grab_collider->m_rect))
					{
						if (m_enemy->m_allow_attack) {
							m_player->m_state = player_state::DAMAGED;
							m_enemy->m_allow_attack = false;
						}
					}

					if (m_enemy->m_timer_count >= m_enemy->m_ground_attack_range)
					{
						m_enemy->m_current_animation->Reset();
						m_enemy->m_current_animation = &(m_enemy->m_npc_punky_ground_attack_right1);		
					}
				}
				if (m_enemy->m_current_animation == &(m_enemy->m_npc_punky_ground_attack_right1) && m_enemy->m_timer_count != 0)
				{
					
					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_position.x += 20;
						UpdateColliderPosition();

						m_enemy->m_state = enemy_state::IDLE;
						m_enemy->m_restart_animation = true;
						m_enemy->m_current_animation->Reset();
						m_enemy->m_timer_count = 0;
						m_enemy->m_current_animation = &(m_enemy->m_npc_punky_idle_right);
					}
				}


				//face left
				if (m_enemy->m_current_animation == &(m_enemy->m_npc_punky_ground_attack_left1) && m_enemy->m_timer_count == 0)
				{
					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_current_animation->Reset();
						m_enemy->m_current_animation = &(m_enemy->m_npc_punky_ground_attack_left2);
						
					}
				}
				if (m_enemy->m_current_animation == &(m_enemy->m_npc_punky_ground_attack_left2))
				{
					m_enemy->m_timer_count++;
					m_enemy->m_position.x -= m_enemy->m_ground_attack_speed;
					UpdateColliderPosition();

					//move grab collider to the feet
					m_enemy_grab_collider->SetPos((m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_grab_collider->m_rect.w / 2) - 50, m_enemy->m_depth);
					if (App->player->m_player_collider->CheckCollision(m_enemy_grab_collider->m_rect))
					{
						if (m_enemy->m_allow_attack)
						{
							m_player->m_state = player_state::DAMAGED;
							m_enemy->m_allow_attack = false;
						}
					}

					if (m_enemy->m_timer_count >= m_enemy->m_ground_attack_range)
					{
						m_enemy->m_current_animation->Reset();
						m_enemy->m_current_animation = &(m_enemy->m_npc_punky_ground_attack_left1);
						UpdateColliderPosition();
					}		
				}

				if (m_enemy->m_current_animation == &(m_enemy->m_npc_punky_ground_attack_left1) && m_enemy->m_timer_count != 0)
				{
					
					if (m_player->m_current_animation->Finished())
					{
						m_enemy->m_position.x -= 20;
						UpdateColliderPosition();

						m_enemy->m_state = enemy_state::IDLE;
						m_enemy->m_restart_animation = true;
						m_enemy->m_current_animation->Reset();
						m_enemy->m_timer_count = 0;
						m_enemy->m_current_animation = &(m_enemy->m_npc_punky_idle_left);
					}
				}
			}

			//Only nora enters whip_attack state
			if (m_enemy->m_state == enemy_state::WHIP_ATTACK)
			{
				if (m_enemy->m_restart_animation)
				{
					m_enemy->m_restart_animation = false;

					if (m_enemy->m_face_right)
						m_enemy->m_current_animation = &(m_enemy->m_npc_nora_attack_right1);
					else
						m_enemy->m_current_animation = &(m_enemy->m_npc_nora_attack_left1);
				}

				//Face right
				if (m_enemy->m_current_animation ==  &(m_enemy->m_npc_nora_attack_right1))
				{
					//move grab collider closer to the hit area 
					m_enemy_grab_collider->SetPos((m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_grab_collider->m_rect.w / 2) + 45, m_enemy->m_depth);
					
					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_current_animation->Reset();
						m_enemy->m_current_animation = &(m_enemy->m_npc_nora_attack_right2);	
					}
				}
				if (m_enemy->m_current_animation == &(m_enemy->m_npc_nora_attack_right2))
				{
					if (App->player->m_player_collider->CheckCollision(m_enemy_grab_collider->m_rect))
					{
						if (m_enemy->m_allow_attack) {
							m_player->m_state = player_state::DAMAGED;

						}
					}
					
					if (m_enemy->m_current_animation->Finished())
					{
						UpdateColliderPosition();
						m_enemy->m_state = enemy_state::IDLE;
						m_enemy->m_restart_animation = true;
						m_enemy->m_allow_attack = false;
						m_enemy->m_current_animation->Reset();
						m_enemy->m_current_animation = &(m_enemy->m_npc_nora_idle_right);
					}
				}

				//Face left
				if (m_enemy->m_current_animation == &(m_enemy->m_npc_nora_attack_left1))
				{
					//move grab collider closer to the hit area 
					m_enemy_grab_collider->SetPos((m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_grab_collider->m_rect.w / 2) - 45, m_enemy->m_depth);
					
					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_current_animation->Reset();
						m_enemy->m_current_animation = &(m_enemy->m_npc_nora_attack_left2);
					}
				}
				if (m_enemy->m_current_animation == &(m_enemy->m_npc_nora_attack_left2))
				{
					if (App->player->m_player_collider->CheckCollision(m_enemy_grab_collider->m_rect))
					{
						if (m_enemy->m_allow_attack) {
							m_player->m_state = player_state::DAMAGED;

						}
					}

					if (m_enemy->m_current_animation->Finished())
					{
						UpdateColliderPosition();
						m_enemy->m_state = enemy_state::IDLE;
						m_enemy->m_restart_animation = true;
						m_enemy->m_allow_attack = false;
						m_enemy->m_current_animation->Reset();
						m_enemy->m_current_animation = &(m_enemy->m_npc_nora_idle_left);
					}
				}
	
			}

			//Only antonio enters kick state
			if (m_enemy->m_state == enemy_state::KICK)
			{
				if (m_enemy->m_face_right)
				{
					m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_kick_right);
					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_current_animation->Reset();
						m_enemy->m_state = enemy_state::IDLE;
					}
				}
				else
				{
					m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_kick_left);
					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_current_animation->Reset();
						m_enemy->m_state = enemy_state::IDLE;
					}
				}
			}
			//Only antonio enters throw_boomerang state
			if (m_enemy->m_state == enemy_state::THROW_BOOMERANG)
			{
				if (m_enemy->m_face_right)
				{
					m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_throw_boomerang_right);
					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_current_animation->Reset();
						m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_idle_right);
						m_enemy->m_carrying_boomerang = false;
						m_enemy->m_state = enemy_state::IDLE;
					}
				}
				else
				{
					m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_throw_boomerang_left);
					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_current_animation->Reset();
						m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_idle_left);
						m_enemy->m_carrying_boomerang = false;
						m_enemy->m_state = enemy_state::IDLE;
					}
				}
			}
			//Only antonio enters recover_boomerang state
			if (m_enemy->m_state == enemy_state::RECOVER_BOOMERANG)
			{
				if (m_enemy->m_face_right)
				{
					m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_recover_boomerang_right);
					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_carrying_boomerang = true;
						m_enemy->m_current_animation->Reset();
						m_enemy->m_state = enemy_state::IDLE;
					}
				}
				else
				{
					m_enemy->m_current_animation = &(m_enemy->m_npc_antonio_recover_boomerang_left);
					if (m_enemy->m_current_animation->Finished())
					{
						m_enemy->m_carrying_boomerang = true;
						m_enemy->m_current_animation->Reset();
						m_enemy->m_state = enemy_state::IDLE;
					}
				}
			}
			//Boomerang position update
			if (!strcmp(m_enemy->m_name, "antonio"))
			{
				if (m_enemy->m_dead == false) 
				{
					if (m_enemy->m_carrying_boomerang == false)
					{
						if (m_enemy->m_face_right)
						{
							if (m_boomerang == nullptr) 
							{
								m_boomerang = (Enemy*)EntityManager::CreateEntity(graphics, "boomerang", entity_type::ENEMY, { m_enemy->m_position.x + 30, m_enemy->m_position.y + 59 }, 0);
								m_boomerang->m_current_animation = &(m_enemy->m_npc_item_boomerang_right);
								m_boomerang->m_start_position = m_boomerang->m_position;
								m_boomerang->m_speed = 3.0f;
							}
							if (m_boomerang->m_boomerang_forward)
							{
								if (m_boomerang->m_position.x - m_boomerang->m_start_position.x < 160)
								{
									m_boomerang->m_position.x += (int)m_boomerang->m_speed;
								}
								if (m_boomerang->m_position.x - m_boomerang->m_start_position.x >= 160)
								{
									m_boomerang->m_boomerang_forward = false;
								}
							}
							if (m_boomerang->m_boomerang_forward == false)
							{
								iPoint vector = { m_enemy->m_position.x - m_boomerang->m_position.x, m_enemy->m_position.y + 48 - m_boomerang->m_position.y };
								m_boomerang->m_position.x = (int)(m_boomerang->m_position.x + vector.x * m_boomerang->m_t_acum);
								m_boomerang->m_position.y = (int)(m_boomerang->m_position.y + vector.y * m_boomerang->m_t_acum);
								m_boomerang->m_t_acum += 0.001f;

								//El enemigo recogerá el boomerang cuando éste colisione con él.
							}	
						}							
						if(m_enemy->m_face_right == false)
						{
							if (m_boomerang == nullptr)
							{
								m_boomerang = (Enemy*)EntityManager::CreateEntity(graphics, "boomerang", entity_type::ENEMY, { m_enemy->m_position.x - 40 , m_enemy->m_position.y + 57 }, 0);
								m_boomerang->m_current_animation = &(m_enemy->m_npc_item_boomerang_left);
								m_boomerang->m_start_position = m_boomerang->m_position;
								m_boomerang->m_speed = 3.0f;
							}
							if (m_boomerang->m_boomerang_forward)
							{
								if ( m_boomerang->m_start_position.x - m_boomerang->m_position.x < 160)
								{
									m_boomerang->m_position.x -= (int)m_boomerang->m_speed;
								}
								if (m_boomerang->m_start_position.x - m_boomerang->m_position.x >= 160)
								{
									m_boomerang->m_boomerang_forward = false;
								}
							}
							if (m_boomerang->m_boomerang_forward == false)
							{
								iPoint vector = { m_enemy->m_position.x - m_boomerang->m_position.x, m_enemy->m_position.y + 48 - m_boomerang->m_position.y };
								m_boomerang->m_position.x = (int)(m_boomerang->m_position.x + vector.x * m_boomerang->m_t_acum);
								m_boomerang->m_position.y = (int)(m_boomerang->m_position.y + vector.y * m_boomerang->m_t_acum);
								m_boomerang->m_t_acum += 0.001f;

								//El enemigo recogerá el boomerang cuando éste colisione con él.
							}
						}
					}
					if (m_enemy->m_carrying_boomerang == true)
					{
						if (m_boomerang != nullptr)
						{
							EntityManager::DestroyEntity(m_boomerang);
							m_boomerang = nullptr;
							
						}

					}
				}
				else
				{
					if (m_boomerang != nullptr)
					{
						EntityManager::DestroyEntity(m_boomerang);
						m_boomerang = nullptr;
					}
				}
			}




		}
	}
	}


	//playerCollider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------

	for (auto it = App->entities.begin(); it != App->entities.end(); it++)
	{
		if ((*it)->m_type == entity_type::ENEMY)
		{
			App->renderer->Blit((*it)->m_texture, (*it)->m_position.x, (*it)->m_position.y, &(((Enemy*)(*it))->m_current_animation->GetCurrentFrame()));
		}
	}
	//App->renderer->Blit(enemy->m_texture, enemy->m_position.x, enemy->m_position.y, &(enemy->m_current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModuleEnemies::UpdateColliderPosition()
{
	m_enemy_grab_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_grab_collider->m_rect.w / 2, m_enemy->m_depth);
	m_enemy_hit_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_hit_collider->m_rect.w / 2, m_enemy->m_depth);
}

