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

	LOG("Loading enemies");
	graphics = App->textures->Load("assets/spritesheets/enemies.png");
	m_player = App->player->m_player;

	//Enemy1
	m_garcia1 = (Enemy*)EntityManager::CreateEntity(graphics, "garcia", entity_type::GARCIA, { 1000, 100 }, 100);
	m_garcia1->m_state = enemy_state::IDLE;
	m_garcia1->m_ai_controller.m_ai_owner_enemy = m_garcia1;
	m_garcia1->m_ai_controller.m_player = App->player->m_player;
	
	SDL_Rect grab_rect_garcia1;
	grab_rect_garcia1.x = 0;
	grab_rect_garcia1.y = 0;
	grab_rect_garcia1.w = 15;
	grab_rect_garcia1.h = 63;
	
	Collider *grab_collider_garcia1 = App->collision->AddCollider(grab_rect_garcia1, m_garcia1, collider_type::COMMON_ENEMY_GRAB);
	grab_collider_garcia1->SetPos(m_garcia1->m_position.x + m_garcia1->m_x_ref - grab_collider_garcia1->m_rect.w / 2, m_garcia1->m_depth);
	m_garcia1->m_enemy_grab_collider = grab_collider_garcia1;
	
	SDL_Rect hit_rect_garcia1;
	hit_rect_garcia1.x = 0;
	hit_rect_garcia1.y = 0;
	hit_rect_garcia1.w = 30;
	hit_rect_garcia1.h = 63;

	Collider *hit_collider_garcia1 = App->collision->AddCollider(hit_rect_garcia1, m_garcia1, collider_type::COMMON_ENEMY_HIT);
	hit_collider_garcia1->SetPos(m_garcia1->m_position.x + m_garcia1->m_x_ref - hit_collider_garcia1->m_rect.w / 2, m_garcia1->m_depth);
	m_garcia1->m_enemy_hit_collider = hit_collider_garcia1;



	//Enemy2
	/*m_enemy2 = (Enemy*)EntityManager::CreateEntity(graphics, "garcia_knife", entity_type::ENEMY, { 700, 100 }, 100);
	m_enemy2->m_state = enemy_state::IDLE;
	m_enemy2->m_ai_controller.m_ai_owner_enemy = m_enemy2;
	m_enemy2->m_ai_controller.m_player = App->player->m_player;

	SDL_Rect grab_rect_enemy2;
	grab_rect_enemy2.x = 0;
	grab_rect_enemy2.y = 0;
	grab_rect_enemy2.w = 15;
	grab_rect_enemy2.h = 63;
	Collider *m_enemy2_grab_collider = App->collision->AddCollider(grab_rect_enemy2, m_enemy2, collider_type::COMMON_ENEMY_GRAB);
	m_enemy2_grab_collider->SetPos(m_enemy2->m_position.x + m_enemy2->m_x_ref - m_enemy2_grab_collider->m_rect.w / 2, m_enemy2->m_depth);
	m_enemy2->m_enemy_grab_collider = m_enemy2_grab_collider;

	SDL_Rect hit_rect_enemy_2;
	hit_rect_enemy_2.x = 0;
	hit_rect_enemy_2.y = 0;
	hit_rect_enemy_2.w = 35;
	hit_rect_enemy_2.h = 63;
	Collider *m_enemy2_hit_collider = App->collision->AddCollider(hit_rect_enemy_2, m_enemy2, collider_type::COMMON_ENEMY_HIT);
	m_enemy2_hit_collider->SetPos(m_enemy2->m_position.x + m_enemy2->m_x_ref - m_enemy2_hit_collider->m_rect.w / 2, m_enemy2->m_depth);
	m_enemy2->m_enemy_hit_collider = m_enemy2_hit_collider;*/


	//Enemy3
	/*m_punky1 = (Enemy*)EntityManager::CreateEntity(graphics, "punky", entity_type::ENEMY, { 1000, 100 }, 100);
	m_punky1->m_state = enemy_state::IDLE;
	m_punky1->m_ai_controller.m_ai_owner_enemy = m_punky1;
	m_punky1->m_ai_controller.m_player = App->player->m_player;

	SDL_Rect grab_rect_punky1;
	grab_rect_punky1.x = 0;
	grab_rect_punky1.y = 0;
	grab_rect_punky1.w = 15;
	grab_rect_punky1.h = 63;
	Collider *grab_collider_punky1 = App->collision->AddCollider(grab_rect_punky1, nullptr, collider_type::COMMON_ENEMY_GRAB);
	grab_collider_punky1->SetPos(m_punky1->m_position.x + m_punky1->m_x_ref - grab_collider_punky1->m_rect.w / 2, m_punky1->m_depth);
	m_punky1->m_enemy_grab_collider = grab_collider_punky1;


	SDL_Rect hit_rect_punky1;
	hit_rect_punky1.x = 0;
	hit_rect_punky1.y = 0;
	hit_rect_punky1.w = 35;
	hit_rect_punky1.h = 63;
	Collider *hit_collider_punky1 = App->collision->AddCollider(hit_rect_punky1, nullptr, collider_type::COMMON_ENEMY_HIT);
	hit_collider_punky1->SetPos(m_punky1->m_position.x + m_punky1->m_x_ref - hit_collider_punky1->m_rect.w / 2, m_punky1->m_depth);
	m_punky1->m_enemy_hit_collider = hit_collider_punky1;


	SDL_Rect ranged_attack_rect_punky1;
	ranged_attack_rect_punky1.x = 0;
	ranged_attack_rect_punky1.y = 0;
	ranged_attack_rect_punky1.w = 130;
	ranged_attack_rect_punky1.h = 63;
	Collider *ranged_attack_collider_punky1 = App->collision->AddCollider(ranged_attack_rect_punky1, nullptr, collider_type::COMMON_ENEMY_RANGED_ATTACK);
	ranged_attack_collider_punky1->SetPos(m_punky1->m_position.x + m_punky1->m_x_ref - ranged_attack_collider_punky1->m_rect.w / 2, m_punky1->m_depth);
	m_punky1->m_enemy_ranged_attack_collider;*/
	


	//Enemy4
	/*m_enemy = (Enemy*)EntityManager::CreateEntity(graphics, "nora", entity_type::ENEMY, { 1000, 100 }, 100);
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
	m_enemy_hit_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_hit_collider->m_rect.w / 2, m_enemy->m_depth);*/


	//Enemy5
	/*m_enemy = (Enemy*)EntityManager::CreateEntity(graphics, "antonio", entity_type::ENEMY, { 1000, 100 }, 100);
	m_enemy->m_state = enemy_state::IDLE;
	m_enemy->m_ai_controller.m_enemy = m_enemy;
	m_enemy->m_ai_controller.m_player = App->player->m_player;

	SDL_Rect collider;
	collider.x = 0;
	collider.y = 0;
	collider.w = 10;
	collider.h = 63;
	m_enemy_grab_collider = App->collision->AddCollider(collider, nullptr, collider_type::COMMON_ENEMY_GRAB);
	m_enemy_grab_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_grab_collider->m_rect.w / 2, m_enemy->m_depth + 40);

	collider.x = 0;
	collider.y = 0;
	collider.w = 30;
	collider.h = 63;
	m_enemy_hit_collider = App->collision->AddCollider(collider, nullptr, collider_type::COMMON_ENEMY_HIT);
	m_enemy_hit_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_hit_collider->m_rect.w / 2, m_enemy->m_depth + 40);*/

	/*collider.x = 0;
	collider.y = 0;
	collider.w = 200;
	collider.h = 63;
	m_enemy_boss_special_attack_collider = App->collision->AddCollider(collider, nullptr, collider_type::BOSS_BOOMERANG_AREA);
	m_enemy_boss_special_attack_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_boss_special_attack_collider->m_rect.w / 2, m_enemy->m_depth);*/


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
			Enemy *enemy = (Enemy*)*it;


			if (enemy->m_ai_attack)
			{
				if (enemy->m_state == enemy_state::WALKING)
					enemy->m_state = enemy_state::IDLE;
				
				if( enemy->m_state == enemy_state::IDLE )
				{
					if (!strcmp(enemy->m_name, "garcia"))
					{
						if (enemy->m_punch_hits < 2)
						{
							if (App->player->m_player_collider->CheckCollision(enemy->m_enemy_hit_collider->m_rect) == true && enemy->m_depth == m_player->m_depth)
							{
								enemy->m_state = enemy_state::PUNCH1;
								enemy->m_floating_attack = false;
								m_player->m_state = player_state::DAMAGED;
								m_player->m_enemy_attacking_player = enemy;
							}
							else
							{
								enemy->m_punch_hits = 0;
								enemy->m_ai_attack = false;
								enemy->m_ai_walk = true;								
								enemy->m_state = enemy_state::WALKING;
							}
						}
						if (enemy->m_punch_hits == 2)
						{
							if (App->player->m_player_collider->CheckCollision(enemy->m_enemy_hit_collider->m_rect) == true && enemy->m_depth == m_player->m_depth)
							{
								enemy->m_state = enemy_state::PUNCH2;
								enemy->m_floating_attack = true;
								m_player->m_state = player_state::DAMAGED;
								m_player->m_enemy_attacking_player = enemy;
							}
								
							else
							{
								enemy->m_ai_attack = false;
								enemy->m_ai_walk = true;								
								enemy->m_state = enemy_state::WALKING;
							}
						}
						if (enemy->m_punch_hits == 3)
						{
							enemy->m_floating_attack = false;
						}
					}
					if (!strcmp(enemy->m_name, "garcia_knife"))
					{
						if (enemy->m_allow_attack)
						{
							if (App->player->m_player_collider->CheckCollision(enemy->m_enemy_hit_collider->m_rect) == true &&	enemy->m_depth == m_player->m_depth)
							{
								enemy->m_state = enemy_state::KNIFE_ATTACK;
								m_player->m_state = player_state::DAMAGED;
								m_player->m_enemy_attacking_player = enemy;
							}
							else
							{
								enemy->m_ai_attack = false;
								enemy->m_ai_walk = true;
								enemy->m_state = enemy_state::WALKING;
							}
						}
					}
					if (!strcmp(enemy->m_name, "punky"))
					{
						if (enemy->m_allow_attack)
						{
							if (App->player->m_player_collider->CheckCollision(enemy->m_enemy_hit_collider->m_rect) == true && enemy->m_depth == m_player->m_depth)
							{
								enemy->m_state = enemy_state::GROUND_ATTACK;
								enemy->m_floating_attack = true;
							}
							else
							{
								enemy->m_ai_attack = false;
								enemy->m_ai_walk = true;
								enemy->m_state = enemy_state::WALKING;
							}
						}
					}
					if (!strcmp(enemy->m_name, "nora"))
					{
						if (enemy->m_allow_attack)
						{
							if (App->player->m_player_collider->CheckCollision(enemy->m_enemy_hit_collider->m_rect) == true && enemy->m_depth == m_player->m_depth)
							{
								enemy->m_state = enemy_state::WHIP_ATTACK;
								enemy->m_floating_attack = true;
							}
							else
							{
								enemy->m_ai_attack = false;
								enemy->m_ai_walk = true;
								enemy->m_state = enemy_state::WALKING;
							}
						}
					}
					if (!strcmp(enemy->m_name, "antonio"))
					{	
						if (enemy->m_allow_attack)
						{
							if (App->player->m_player_collider->CheckCollision(enemy->m_enemy_hit_collider->m_rect) == true && enemy->m_depth + enemy->m_y_ref == m_player->m_depth)
							{
								enemy->m_state = enemy_state::KICK;
								enemy->m_floating_attack = true;
								enemy->m_carrying_boomerang = false;  
							}
							else
							{
								enemy->m_ai_attack = false;
								enemy->m_ai_walk = true;
								enemy->m_state = enemy_state::WALKING;
							}
						}
					}
				}
			}

			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{
				if (!strcmp(enemy->m_name, "antonio"))
				{
					if(enemy->m_carrying_boomerang)
						enemy->m_state = enemy_state::THROW_BOOMERANG;
				}
			}
			if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
			{
				if (!strcmp(enemy->m_name, "antonio"))
				{
					if (enemy->m_carrying_boomerang == false)
						enemy->m_state = enemy_state::RECOVER_BOOMERANG;
				}
			}
				
			
			//Inputs will be substituted by AI signals
			if (enemy->m_state == enemy_state::IDLE ||
				enemy->m_state == enemy_state::WALKING  &&
				enemy->m_ai_walk == false &&
				enemy->m_ai_attack == false)
			{
				enemy->m_state = enemy_state::IDLE;
			}

			if (enemy->m_state == enemy_state::IDLE)
			{

				if (!strcmp(enemy->m_name, "garcia"))
				{
					enemy->m_current_animation = enemy->m_face_right ? &(enemy->m_npc_garcia_idle_right) : &(enemy->m_npc_garcia_idle_left);
					if (enemy->m_punch_hits == 3)
					{
						enemy->m_counter++;
						if (enemy->m_counter == m_time_to_next_attack)
						{
								enemy->m_punch_hits = 0;
								enemy->m_counter = 0;
						}
					}

				}
				if (!strcmp(enemy->m_name, "garcia_knife"))
				{
					enemy->m_current_animation = enemy->m_face_right ? &(enemy->m_npc_garcia_knife_idle_right) : &(enemy->m_npc_garcia_knife_idle_left);
					enemy->m_counter++;
					if (enemy->m_counter == m_time_to_next_attack)
					{
						enemy->m_counter = 0;
						enemy->m_allow_attack = true;
					}

				}
				if (!strcmp(enemy->m_name, "punky"))
				{
					enemy->m_current_animation = enemy->m_face_right ? &(enemy->m_npc_punky_idle_right) : &(enemy->m_npc_punky_idle_left);
					enemy->m_counter++;
					if (enemy->m_counter == m_time_to_next_attack)
					{
						enemy->m_counter = 0;
						enemy->m_allow_attack = true;
					}
				}
				if (!strcmp(enemy->m_name, "nora"))
				{
					enemy->m_current_animation = enemy->m_face_right ? &(enemy->m_npc_nora_idle_right) : &(enemy->m_npc_nora_idle_left);
					enemy->m_counter++;
					if (enemy->m_counter == m_time_to_next_attack)
					{
						enemy->m_counter = 0;
						enemy->m_allow_attack = true;
					}
				}
				if (!strcmp(enemy->m_name, "antonio"))
				{
					if (enemy->m_face_right)
					{
						if (enemy->m_carrying_boomerang)
							enemy->m_current_animation = &(enemy->m_npc_antonio_boomerang_idle_right);
						else
							enemy->m_current_animation = &(enemy->m_npc_antonio_idle_right);
					}
					else
					{
						if (enemy->m_carrying_boomerang)
							enemy->m_current_animation = &(enemy->m_npc_antonio_boomerang_idle_left);
						else
							enemy->m_current_animation = &(enemy->m_npc_antonio_idle_left);
					}

					enemy->m_counter++;
					if (enemy->m_counter == m_time_to_next_attack)
					{
						enemy->m_counter = 0;
						enemy->m_allow_attack = true;
					}
				}
			}

			if (enemy->m_ai_walk)
			{
				
				if (enemy->m_state == enemy_state::IDLE || enemy->m_state == enemy_state::WALKING)
				{
					enemy->m_state = enemy_state::WALKING;
					
					if (!strcmp(enemy->m_name, "garcia"))
					{
						if (enemy->m_face_right)
						{
							if (enemy->m_current_animation != &(enemy->m_npc_garcia_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_garcia_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
						else
						{
							if (enemy->m_current_animation != &(enemy->m_npc_garcia_walk_left))
							{
								enemy->m_current_animation = &(enemy->m_npc_garcia_walk_left);
								enemy->m_current_animation->Reset();
							}
						}
					}
					if (!strcmp(enemy->m_name, "garcia_knife"))
					{
						if (enemy->m_face_right)
						{
							if (enemy->m_current_animation != &(enemy->m_npc_garcia_knife_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_garcia_knife_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
						else
						{
							if (enemy->m_current_animation != &(enemy->m_npc_garcia_knife_walk_left))
							{
								enemy->m_current_animation = &(enemy->m_npc_garcia_knife_walk_left);
								enemy->m_current_animation->Reset();
							}
						}
							
					}
					if (!strcmp(enemy->m_name, "punky"))
					{
						if (enemy->m_face_right)
						{
							if (enemy->m_current_animation != &(enemy->m_npc_punky_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_punky_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
						else
						{
							if (enemy->m_current_animation != &(enemy->m_npc_punky_walk_left))
							{
								enemy->m_current_animation = &(enemy->m_npc_punky_walk_left);
								enemy->m_current_animation->Reset();
							}
						}		
					}
					if (!strcmp(enemy->m_name, "nora"))
					{
						if (enemy->m_face_right)
						{
							if (enemy->m_current_animation != &(enemy->m_npc_nora_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_nora_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
						else
						{
							if (enemy->m_current_animation != &(enemy->m_npc_nora_walk_left))
							{
								enemy->m_current_animation = &(enemy->m_npc_nora_walk_left);
								enemy->m_current_animation->Reset();
							}
						}		
					}
					if (!strcmp(enemy->m_name, "antonio"))
					{
						if (enemy->m_carrying_boomerang)
						{
							if (enemy->m_face_right)
							{
								if (enemy->m_current_animation != &(enemy->m_npc_antonio_boomerang_walk_right))
								{
									enemy->m_current_animation = &(enemy->m_npc_antonio_boomerang_walk_right);
									enemy->m_current_animation->Reset();
								}
							}
							else
							{
								if (enemy->m_current_animation != &(enemy->m_npc_antonio_boomerang_walk_left))
								{
									enemy->m_current_animation = &(enemy->m_npc_antonio_boomerang_walk_left);
									enemy->m_current_animation->Reset();
								}
							}		
						}
						else
						{
							if (enemy->m_face_right)
							{
								if (enemy->m_current_animation != &(enemy->m_npc_antonio_walk_right))
								{
									enemy->m_current_animation = &(enemy->m_npc_antonio_walk_right);
									enemy->m_current_animation->Reset();
								}
							}
							else
							{
								if (enemy->m_current_animation != &(enemy->m_npc_antonio_walk_left))
								{
									enemy->m_current_animation = &(enemy->m_npc_antonio_walk_left);
									enemy->m_current_animation->Reset();
								}
							}
							
						}
					}
				}
			}


			if (enemy->m_state == enemy_state::DAMAGED)
			{
				if (!strcmp(enemy->m_name, "garcia"))
				{
					enemy->m_ai_walk = false;
					enemy->m_ai_attack = false;

					if (m_player->m_float_attack == false) 
					{
						if (enemy->m_face_right)
							enemy->m_current_animation = &(enemy->m_npc_garcia_damage_received_right);
						else
							enemy->m_current_animation = &(enemy->m_npc_garcia_damage_received_left);

						if (enemy->m_current_animation->Finished())
						{
							enemy->m_current_animation->Reset();
							enemy->m_state = enemy_state::WALKING;
							enemy->m_ai_walk = true;
						}
					}

					if (m_player->m_float_attack == true)
					{
						if (enemy->m_face_right)
							enemy->m_current_animation = &(enemy->m_npc_garcia_down_right);
						else
							enemy->m_current_animation = &(enemy->m_npc_garcia_down_left);
					}
							
					if(enemy->m_current_animation == &(enemy->m_npc_garcia_down_right))
					{
						if (enemy->m_current_animation->Finished())
						{
							if (enemy->m_dead == false)
							{
								enemy->m_current_animation->Reset();
								enemy->m_state = enemy_state::UP;
								enemy->m_current_animation = &(enemy->m_npc_garcia_up_right);
							}
						}
					}
					if (enemy->m_current_animation == &(enemy->m_npc_garcia_down_left))
					{
						if (enemy->m_current_animation->Finished())
						{
							if (enemy->m_dead == false)
							{
								enemy->m_current_animation->Reset();
								enemy->m_state = enemy_state::UP;
								enemy->m_current_animation = &(enemy->m_npc_garcia_up_left);
							}
						}
					}

				}
			}
			

			if (enemy->m_state == enemy_state::UP)
			{
				if (!strcmp(enemy->m_name, "garcia"))
				{
					if (enemy->m_face_right)
					{
						enemy->m_current_animation = &(enemy->m_npc_garcia_up_right);
						
						if (enemy->m_current_animation->Finished())
						{
							enemy->m_current_animation->Reset();
							enemy->m_state = enemy_state::WALKING;
							enemy->m_ai_walk = true;
							m_player->m_float_attack = false;
						}
					}
					else
					{
						enemy->m_current_animation = &(enemy->m_npc_garcia_up_left);

						if (enemy->m_current_animation->Finished())
						{
							enemy->m_current_animation->Reset();
							enemy->m_state = enemy_state::WALKING;
							enemy->m_ai_walk = true;
							m_player->m_float_attack = false;
						}
					}
				}

			}

			//Only garcia enters punch1,punch2 states
			if (enemy->m_state == enemy_state::PUNCH1)
			{
				if (enemy->m_face_right)
				{
					enemy->m_current_animation = &(enemy->m_npc_garcia_punch_right1);

					if (enemy->m_current_animation->Finished())
					{
						enemy->m_punch_hits++;
						enemy->m_state = enemy_state::IDLE;
						enemy->m_current_animation->Reset();
					}
				}
				else
				{
					enemy->m_current_animation = &(enemy->m_npc_garcia_punch_left1);

					if (enemy->m_current_animation->Finished())
					{
						enemy->m_punch_hits++;
						enemy->m_state = enemy_state::IDLE;
						enemy->m_current_animation->Reset();						
					}

				}
			}

			if (enemy->m_state == enemy_state::PUNCH2)
			{
				if (enemy->m_face_right)
				{
					enemy->m_current_animation = &(enemy->m_npc_garcia_punch_right2);

					if (enemy->m_current_animation->Finished())
					{
						enemy->m_punch_hits++;
						enemy->m_state = enemy_state::IDLE;
						enemy->m_current_animation->Reset();
						enemy->m_current_animation = &(enemy->m_npc_garcia_idle_right);
					}
				}
				else
				{
					enemy->m_current_animation = &(enemy->m_npc_garcia_punch_left2);

					if (enemy->m_current_animation->Finished())
					{
						enemy->m_punch_hits++;
						enemy->m_state = enemy_state::IDLE;
						enemy->m_current_animation->Reset();
						enemy->m_current_animation = &(enemy->m_npc_garcia_idle_left);
					}
				}
			}
			//Only garcia_knife enters knife_attack state
			if (enemy->m_state == enemy_state::KNIFE_ATTACK)
			{
				if (enemy->m_face_right)
					enemy->m_current_animation = &(enemy->m_npc_garcia_knife_attack_right);
				else
					enemy->m_current_animation = &(enemy->m_npc_garcia_knife_attack_left);

				if (enemy->m_current_animation->Finished())
				{
					enemy->m_state = enemy_state::IDLE;
					enemy->m_current_animation->Reset();
					enemy->m_allow_attack = false;

					if (enemy->m_face_right)
						enemy->m_current_animation = &(enemy->m_npc_garcia_knife_idle_right);
					else
						enemy->m_current_animation = &(enemy->m_npc_garcia_knife_idle_left);
				}
			}
			//Only punky enters ground_attack state
			if (enemy->m_state == enemy_state::GROUND_ATTACK)
			{
				if (enemy->m_restart_animation)
				{
					enemy->m_timer_count = 0;
					enemy->m_restart_animation = false;

					if (enemy->m_face_right)
						enemy->m_current_animation = &(enemy->m_npc_punky_ground_attack_right1);
					else
						enemy->m_current_animation = &(enemy->m_npc_punky_ground_attack_left1);
				}

				//face right
				if (enemy->m_current_animation == &(enemy->m_npc_punky_ground_attack_right1) && enemy->m_timer_count == 0)
				{
					if (enemy->m_current_animation->Finished())
					{
						enemy->m_current_animation->Reset();
						enemy->m_current_animation = &(enemy->m_npc_punky_ground_attack_right2);
					}
				}
				if (enemy->m_current_animation == &(enemy->m_npc_punky_ground_attack_right2))
				{
					enemy->m_position.x += enemy->m_ground_attack_speed;
					UpdateColliderPosition(enemy);
					enemy->m_timer_count++;

					//move grab collider to the feet
					enemy->m_enemy_grab_collider->SetPos((enemy->m_position.x + enemy->m_x_ref - enemy->m_enemy_grab_collider->m_rect.w / 2) + 50, enemy->m_depth);
					if (App->player->m_player_collider->CheckCollision(enemy->m_enemy_grab_collider->m_rect))
					{
						if (enemy->m_allow_attack) {
							m_player->m_state = player_state::DAMAGED;
							m_player->m_enemy_attacking_player = enemy;
							enemy->m_allow_attack = false;
						}
					}

					if (enemy->m_timer_count >= enemy->m_ground_attack_range)
					{
						enemy->m_current_animation->Reset();
						enemy->m_current_animation = &(enemy->m_npc_punky_ground_attack_right1);		
					}
				}
				if (enemy->m_current_animation == &(enemy->m_npc_punky_ground_attack_right1) && enemy->m_timer_count != 0)
				{
					
					if (enemy->m_current_animation->Finished())
					{
						enemy->m_position.x += 20;
						UpdateColliderPosition(enemy);

						enemy->m_state = enemy_state::IDLE;
						enemy->m_restart_animation = true;
						enemy->m_current_animation->Reset();
						enemy->m_timer_count = 0;
						enemy->m_current_animation = &(enemy->m_npc_punky_idle_right);
					}
				}


				//face left
				if (enemy->m_current_animation == &(enemy->m_npc_punky_ground_attack_left1) && enemy->m_timer_count == 0)
				{
					if (enemy->m_current_animation->Finished())
					{
						enemy->m_current_animation->Reset();
						enemy->m_current_animation = &(enemy->m_npc_punky_ground_attack_left2);
						
					}
				}
				if (enemy->m_current_animation == &(enemy->m_npc_punky_ground_attack_left2))
				{
					enemy->m_timer_count++;
					enemy->m_position.x -= enemy->m_ground_attack_speed;
					UpdateColliderPosition(enemy);

					//move grab collider to the feet
					enemy->m_enemy_grab_collider->SetPos((enemy->m_position.x + enemy->m_x_ref - enemy->m_enemy_grab_collider->m_rect.w / 2) - 50, enemy->m_depth);
					if (App->player->m_player_collider->CheckCollision(enemy->m_enemy_grab_collider->m_rect))
					{
						if (enemy->m_allow_attack)
						{
							m_player->m_state = player_state::DAMAGED;
							enemy->m_allow_attack = false;
							m_player->m_enemy_attacking_player = enemy;
						}
					}

					if (enemy->m_timer_count >= enemy->m_ground_attack_range)
					{
						enemy->m_current_animation->Reset();
						enemy->m_current_animation = &(enemy->m_npc_punky_ground_attack_left1);
						UpdateColliderPosition(enemy);
					}		
				}

				if (enemy->m_current_animation == &(enemy->m_npc_punky_ground_attack_left1) && enemy->m_timer_count != 0)
				{
					
					if (m_player->m_current_animation->Finished())
					{
						enemy->m_position.x -= 20;
						UpdateColliderPosition(enemy);

						enemy->m_state = enemy_state::IDLE;
						enemy->m_restart_animation = true;
						enemy->m_current_animation->Reset();
						enemy->m_timer_count = 0;
						enemy->m_current_animation = &(enemy->m_npc_punky_idle_left);
					}
				}
			}

			//Only nora enters whip_attack state
			if (enemy->m_state == enemy_state::WHIP_ATTACK)
			{
				if (enemy->m_restart_animation)
				{
					enemy->m_restart_animation = false;

					if (enemy->m_face_right)
						enemy->m_current_animation = &(enemy->m_npc_nora_attack_right1);
					else
						enemy->m_current_animation = &(enemy->m_npc_nora_attack_left1);
				}

				//Face right
				if (enemy->m_current_animation ==  &(enemy->m_npc_nora_attack_right1))
				{
					//move grab collider closer to the hit area 
					enemy->m_enemy_grab_collider->SetPos((enemy->m_position.x + enemy->m_x_ref - enemy->m_enemy_grab_collider->m_rect.w / 2) + 45, enemy->m_depth);
					
					if (enemy->m_current_animation->Finished())
					{
						enemy->m_current_animation->Reset();
						enemy->m_current_animation = &(enemy->m_npc_nora_attack_right2);	
					}
				}
				if (enemy->m_current_animation == &(enemy->m_npc_nora_attack_right2))
				{
					if (App->player->m_player_collider->CheckCollision(enemy->m_enemy_grab_collider->m_rect))
					{
						if (enemy->m_allow_attack) {
							m_player->m_state = player_state::DAMAGED;
							m_player->m_enemy_attacking_player = enemy;

						}
					}
					
					if (enemy->m_current_animation->Finished())
					{
						UpdateColliderPosition(enemy);
						enemy->m_state = enemy_state::IDLE;
						enemy->m_restart_animation = true;
						enemy->m_allow_attack = false;
						enemy->m_current_animation->Reset();
						enemy->m_current_animation = &(enemy->m_npc_nora_idle_right);
					}
				}

				//Face left
				if (enemy->m_current_animation == &(enemy->m_npc_nora_attack_left1))
				{
					//move grab collider closer to the hit area 
					enemy->m_enemy_grab_collider->SetPos((enemy->m_position.x + enemy->m_x_ref - enemy->m_enemy_grab_collider->m_rect.w / 2) - 45, enemy->m_depth);
					
					if (enemy->m_current_animation->Finished())
					{
						enemy->m_current_animation->Reset();
						enemy->m_current_animation = &(enemy->m_npc_nora_attack_left2);
					}
				}
				if (enemy->m_current_animation == &(enemy->m_npc_nora_attack_left2))
				{
					if (App->player->m_player_collider->CheckCollision(enemy->m_enemy_grab_collider->m_rect))
					{
						if (enemy->m_allow_attack) {
							m_player->m_state = player_state::DAMAGED;
							m_player->m_enemy_attacking_player = enemy;

						}
					}

					if (enemy->m_current_animation->Finished())
					{
						UpdateColliderPosition(enemy);
						enemy->m_state = enemy_state::IDLE;
						enemy->m_restart_animation = true;
						enemy->m_allow_attack = false;
						enemy->m_current_animation->Reset();
						enemy->m_current_animation = &(enemy->m_npc_nora_idle_left);
					}
				}
	
			}

			//Only antonio enters kick state
			if (enemy->m_state == enemy_state::KICK)
			{
				if (enemy->m_face_right)
				{
					enemy->m_current_animation = &(enemy->m_npc_antonio_kick_right);
					if (enemy->m_current_animation->Finished())
					{
						enemy->m_current_animation->Reset();
						enemy->m_state = enemy_state::IDLE;
						enemy->m_allow_attack = false;
						enemy->m_current_animation = &(enemy->m_npc_antonio_idle_right);
						m_player->m_state = player_state::DAMAGED;
					}
				}
				else
				{
					enemy->m_current_animation = &(enemy->m_npc_antonio_kick_left);
					if (enemy->m_current_animation->Finished())
					{
						enemy->m_current_animation->Reset();
						enemy->m_state = enemy_state::IDLE;
						enemy->m_allow_attack = false;
						enemy->m_current_animation = &(enemy->m_npc_antonio_idle_left);
						m_player->m_state = player_state::DAMAGED;
					}
				}
			}
			//Only antonio enters throw_boomerang state
			if (enemy->m_state == enemy_state::THROW_BOOMERANG)
			{
				if (enemy->m_face_right)
				{
					enemy->m_current_animation = &(enemy->m_npc_antonio_throw_boomerang_right);
					if (enemy->m_current_animation->Finished())
					{
						enemy->m_current_animation->Reset();
						enemy->m_current_animation = &(enemy->m_npc_antonio_idle_right);
						enemy->m_carrying_boomerang = false;
						enemy->m_allow_attack = false;
						enemy->m_state = enemy_state::IDLE;
					}
				}
				else
				{
					enemy->m_current_animation = &(enemy->m_npc_antonio_throw_boomerang_left);
					if (enemy->m_current_animation->Finished())
					{
						enemy->m_current_animation->Reset();
						enemy->m_current_animation = &(enemy->m_npc_antonio_idle_left);
						enemy->m_carrying_boomerang = false;
						enemy->m_allow_attack = false;
						enemy->m_state = enemy_state::IDLE;
					}
				}
			}
			//Only antonio enters recover_boomerang state
			if (enemy->m_state == enemy_state::RECOVER_BOOMERANG)
			{
				if (enemy->m_face_right)
				{
					enemy->m_current_animation = &(enemy->m_npc_antonio_recover_boomerang_right);
					if (enemy->m_current_animation->Finished())
					{
						enemy->m_carrying_boomerang = true;
						enemy->m_current_animation->Reset();
						enemy->m_state = enemy_state::IDLE;
					}
				}
				else
				{
					enemy->m_current_animation = &(enemy->m_npc_antonio_recover_boomerang_left);
					if (enemy->m_current_animation->Finished())
					{
						enemy->m_carrying_boomerang = true;
						enemy->m_current_animation->Reset();
						enemy->m_state = enemy_state::IDLE;
					}
				}
			}
			//Boomerang instantiation
			/*if (!strcmp(m_enemy->m_name, "antonio"))
			{				
				if (m_enemy->m_carrying_boomerang == false)
				{
					if (m_enemy->m_boomerang == nullptr)
					{	if (m_enemy->m_face_right)
						{
							App->particles->AddParticle(*(App->particles->m_boomerang), m_enemy->m_position.x + 30, m_enemy->m_position.y + 59, collider_type::BOSS_BOOMERANG);
							App->particles->m_particle->m_owner = m_enemy;
							App->particles->m_particle->m_face_right = true;
							m_enemy->m_boomerang = App->particles->m_particle;
						}
						else
						{
							App->particles->AddParticle(*(App->particles->m_boomerang), m_enemy->m_position.x - 40, m_enemy->m_position.y + 59, collider_type::BOSS_BOOMERANG);
							App->particles->m_particle->m_owner = m_enemy;
							App->particles->m_particle->m_face_right = false;
							m_enemy->m_boomerang = App->particles->m_particle;
						}
					}
				}
					
			}*/
	
		}
	}
	}

	// Draw everything --------------------------------------

	for (auto it = App->entities.begin(); it != App->entities.end(); it++)
	{
		if ((*it)->m_type == entity_type::ENEMY)
		{
			App->renderer->Blit((*it)->m_texture, (*it)->m_position.x, (*it)->m_position.y, &(((Enemy*)(*it))->m_current_animation->GetCurrentFrame()));
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleEnemies::UpdateColliderPosition(Enemy* enemy)
{
	
	if (strcmp(enemy->m_name, "antonio"))
	{
		enemy->m_enemy_grab_collider->SetPos(enemy->m_position.x + enemy->m_x_ref - enemy->m_enemy_grab_collider->m_rect.w / 2, enemy->m_depth);
		enemy->m_enemy_hit_collider->SetPos(enemy->m_position.x + enemy->m_x_ref - enemy->m_enemy_hit_collider->m_rect.w / 2, enemy->m_depth);
		
	}
	//boss anntonio
	if (!strcmp(enemy->m_name, "antonio"))
	{
		enemy->m_enemy_grab_collider->SetPos(enemy->m_position.x + enemy->m_x_ref - enemy->m_enemy_grab_collider->m_rect.w / 2, enemy->m_depth + enemy->m_y_ref);
		enemy->m_enemy_hit_collider->SetPos(enemy->m_position.x + enemy->m_x_ref - enemy->m_enemy_hit_collider->m_rect.w / 2, enemy->m_depth + enemy->m_y_ref);
		//m_enemy_boss_special_attack_collider->SetPos(m_enemy->m_position.x + m_enemy->m_x_ref - m_enemy_boss_special_attack_collider->m_rect.w / 2, m_enemy->m_depth + m_enemy->m_y_ref);
	}

}

