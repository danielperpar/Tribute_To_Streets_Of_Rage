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
#include "Garcia.h"
#include "GarciaKnife.h"
#include "Punky.h"
#include "Nora.h"
#include "Antonio.h"



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
	m_garcia1 = (Garcia*)EntityManager::CreateEntity(graphics, "garcia", entity_type::ENEMY, { 1000, 100 }, 100);
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
	EntityManager::DestroyEntity(m_garcia1);
	m_garcia1 = nullptr;

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
						Garcia *garcia = (Garcia*)enemy;

						if (garcia->m_punch_hits < 2)
						{
							if (App->player->m_player_collider->CheckCollision(garcia->m_enemy_hit_collider->m_rect) == true && garcia->m_depth == m_player->m_depth)
							{
								garcia->m_state = enemy_state::PUNCH1;
								garcia->m_floating_attack = false;
								m_player->m_state = player_state::DAMAGED;
								m_player->m_enemy_attacking_player = garcia;
							}
							else
							{
								garcia->m_punch_hits = 0;
								garcia->m_ai_attack = false;
								garcia->m_ai_walk = true;
								garcia->m_state = enemy_state::WALKING;
							}
						}
						if (garcia->m_punch_hits == 2)
						{
							if (App->player->m_player_collider->CheckCollision(garcia->m_enemy_hit_collider->m_rect) == true && garcia->m_depth == m_player->m_depth)
							{
								garcia->m_state = enemy_state::PUNCH2;
								garcia->m_floating_attack = true;
								m_player->m_state = player_state::DAMAGED;
								m_player->m_enemy_attacking_player = garcia;
							}
								
							else
							{
								garcia->m_ai_attack = false;
								garcia->m_ai_walk = true;
								garcia->m_state = enemy_state::WALKING;
							}
						}
						if (garcia->m_punch_hits == 3)
						{
							garcia->m_floating_attack = false;
						}
					}
					if (!strcmp(enemy->m_name, "garcia_knife"))
					{
						GarciaKnife *garcia_knife = (GarciaKnife*)enemy;
						if (garcia_knife->m_allow_attack)
						{
							if (App->player->m_player_collider->CheckCollision(garcia_knife->m_enemy_hit_collider->m_rect) == true && garcia_knife->m_depth == m_player->m_depth)
							{
								garcia_knife->m_state = enemy_state::KNIFE_ATTACK;
								m_player->m_state = player_state::DAMAGED;
								m_player->m_enemy_attacking_player = garcia_knife;
							}
							else
							{
								garcia_knife->m_ai_attack = false;
								garcia_knife->m_ai_walk = true;
								garcia_knife->m_state = enemy_state::WALKING;
							}
						}
					}
					if (!strcmp(enemy->m_name, "punky"))
					{
						Punky *punky = (Punky*)enemy;
						if (punky->m_allow_attack)
						{
							if (App->player->m_player_collider->CheckCollision(punky->m_enemy_hit_collider->m_rect) == true && punky->m_depth == m_player->m_depth)
							{
								punky->m_state = enemy_state::GROUND_ATTACK;
								punky->m_floating_attack = true;
							}
							else
							{
								punky->m_ai_attack = false;
								punky->m_ai_walk = true;
								punky->m_state = enemy_state::WALKING;
							}
						}
					}
					if (!strcmp(enemy->m_name, "nora"))
					{
						Nora *nora = (Nora*)enemy;

						if (nora->m_allow_attack)
						{
							if (App->player->m_player_collider->CheckCollision(nora->m_enemy_hit_collider->m_rect) == true && nora->m_depth == m_player->m_depth)
							{
								nora->m_state = enemy_state::WHIP_ATTACK;
								nora->m_floating_attack = true;
							}
							else
							{
								nora->m_ai_attack = false;
								nora->m_ai_walk = true;
								nora->m_state = enemy_state::WALKING;
							}
						}
					}
					if (!strcmp(enemy->m_name, "antonio"))
					{	
						Antonio *antonio = (Antonio*)enemy;

						if (antonio->m_allow_attack)
						{
							if (App->player->m_player_collider->CheckCollision(antonio->m_enemy_hit_collider->m_rect) == true && antonio->m_depth + antonio->m_y_ref == m_player->m_depth)
							{
								antonio->m_state = enemy_state::KICK;
								antonio->m_floating_attack = true;
								antonio->m_carrying_boomerang = false;
							}
							else
							{
								antonio->m_ai_attack = false;
								antonio->m_ai_walk = true;
								antonio->m_state = enemy_state::WALKING;
							}
						}
					}
				}
			}

			/*if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
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
			}*/
				
			
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
					Garcia *garcia = (Garcia*)enemy;

					garcia->m_current_animation = garcia->m_face_right ? &(garcia->m_npc_garcia_idle_right) : &(garcia->m_npc_garcia_idle_left);
					if (garcia->m_punch_hits == 3)
					{
						garcia->m_counter++;
						if (garcia->m_counter == m_time_to_next_attack)
						{
							garcia->m_punch_hits = 0;
							garcia->m_counter = 0;
						}
					}

				}
				if (!strcmp(enemy->m_name, "garcia_knife"))
				{
					GarciaKnife *garcia_knife = (GarciaKnife*)enemy;

					garcia_knife->m_current_animation = garcia_knife->m_face_right ? &(garcia_knife->m_npc_garcia_knife_idle_right) : &(garcia_knife->m_npc_garcia_knife_idle_left);
					garcia_knife->m_counter++;
					if (garcia_knife->m_counter == m_time_to_next_attack)
					{
						garcia_knife->m_counter = 0;
						garcia_knife->m_allow_attack = true;
					}

				}
				if (!strcmp(enemy->m_name, "punky"))
				{
					Punky *punky = (Punky*)enemy;

					punky->m_current_animation = punky->m_face_right ? &(punky->m_npc_punky_idle_right) : &(punky->m_npc_punky_idle_left);
					punky->m_counter++;
					if (punky->m_counter == m_time_to_next_attack)
					{
						punky->m_counter = 0;
						punky->m_allow_attack = true;
					}
				}
				if (!strcmp(enemy->m_name, "nora"))
				{
					Nora *nora = (Nora*)enemy;

					nora->m_current_animation = nora->m_face_right ? &(nora->m_npc_nora_idle_right) : &(nora->m_npc_nora_idle_left);
					nora->m_counter++;
					if (nora->m_counter == m_time_to_next_attack)
					{
						nora->m_counter = 0;
						nora->m_allow_attack = true;
					}
				}
				if (!strcmp(enemy->m_name, "antonio"))
				{
					Antonio *antonio = (Antonio*)enemy;

					if (antonio->m_face_right)
					{
						if (antonio->m_carrying_boomerang)
							antonio->m_current_animation = &(antonio->m_npc_antonio_boomerang_idle_right);
						else
							antonio->m_current_animation = &(antonio->m_npc_antonio_idle_right);
					}
					else
					{
						if (antonio->m_carrying_boomerang)
							antonio->m_current_animation = &(antonio->m_npc_antonio_boomerang_idle_left);
						else
							antonio->m_current_animation = &(antonio->m_npc_antonio_idle_left);
					}

					antonio->m_counter++;
					if (antonio->m_counter == m_time_to_next_attack)
					{
						antonio->m_counter = 0;
						antonio->m_allow_attack = true;
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
						Garcia *garcia = (Garcia*)enemy;

						if (garcia->m_face_right)
						{
							if (garcia->m_current_animation != &(garcia->m_npc_garcia_walk_right))
							{
								garcia->m_current_animation = &(garcia->m_npc_garcia_walk_right);
								garcia->m_current_animation->Reset();
							}
						}
						else
						{
							if (garcia->m_current_animation != &(garcia->m_npc_garcia_walk_left))
							{
								garcia->m_current_animation = &(garcia->m_npc_garcia_walk_left);
								garcia->m_current_animation->Reset();
							}
						}
					}
					if (!strcmp(enemy->m_name, "garcia_knife"))
					{
						GarciaKnife *gacia_knife = (GarciaKnife*)enemy;

						if (gacia_knife->m_face_right)
						{
							if (gacia_knife->m_current_animation != &(gacia_knife->m_npc_garcia_knife_walk_right))
							{
								gacia_knife->m_current_animation = &(gacia_knife->m_npc_garcia_knife_walk_right);
								gacia_knife->m_current_animation->Reset();
							}
						}
						else
						{
							if (gacia_knife->m_current_animation != &(gacia_knife->m_npc_garcia_knife_walk_left))
							{
								gacia_knife->m_current_animation = &(gacia_knife->m_npc_garcia_knife_walk_left);
								gacia_knife->m_current_animation->Reset();
							}
						}
							
					}
					if (!strcmp(enemy->m_name, "punky"))
					{
						Punky *punky = (Punky*)enemy;

						if (punky->m_face_right)
						{
							if (punky->m_current_animation != &(punky->m_npc_punky_walk_right))
							{
								punky->m_current_animation = &(punky->m_npc_punky_walk_right);
								punky->m_current_animation->Reset();
							}
						}
						else
						{
							if (punky->m_current_animation != &(punky->m_npc_punky_walk_left))
							{
								punky->m_current_animation = &(punky->m_npc_punky_walk_left);
								punky->m_current_animation->Reset();
							}
						}		
					}
					if (!strcmp(enemy->m_name, "nora"))
					{
						Nora *nora = (Nora*)enemy;

						if (nora->m_face_right)
						{
							if (nora->m_current_animation != &(nora->m_npc_nora_walk_right))
							{
								nora->m_current_animation = &(nora->m_npc_nora_walk_right);
								nora->m_current_animation->Reset();
							}
						}
						else
						{
							if (nora->m_current_animation != &(nora->m_npc_nora_walk_left))
							{
								nora->m_current_animation = &(nora->m_npc_nora_walk_left);
								nora->m_current_animation->Reset();
							}
						}		
					}
					if (!strcmp(enemy->m_name, "antonio"))
					{
						Antonio *antonio = (Antonio*)enemy;

						if (antonio->m_carrying_boomerang)
						{
							if (antonio->m_face_right)
							{
								if (antonio->m_current_animation != &(antonio->m_npc_antonio_boomerang_walk_right))
								{
									antonio->m_current_animation = &(antonio->m_npc_antonio_boomerang_walk_right);
									antonio->m_current_animation->Reset();
								}
							}
							else
							{
								if (antonio->m_current_animation != &(antonio->m_npc_antonio_boomerang_walk_left))
								{
									antonio->m_current_animation = &(antonio->m_npc_antonio_boomerang_walk_left);
									antonio->m_current_animation->Reset();
								}
							}		
						}
						else
						{
							if (antonio->m_face_right)
							{
								if (antonio->m_current_animation != &(antonio->m_npc_antonio_walk_right))
								{
									antonio->m_current_animation = &(antonio->m_npc_antonio_walk_right);
									antonio->m_current_animation->Reset();
								}
							}
							else
							{
								if (antonio->m_current_animation != &(antonio->m_npc_antonio_walk_left))
								{
									antonio->m_current_animation = &(antonio->m_npc_antonio_walk_left);
									antonio->m_current_animation->Reset();
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
					Garcia *garcia = (Garcia*)enemy;

					garcia->m_ai_walk = false;
					garcia->m_ai_attack = false;

					if (m_player->m_float_attack == false) 
					{
						if (garcia->m_face_right)
							garcia->m_current_animation = &(garcia->m_npc_garcia_damage_received_right);
						else
							garcia->m_current_animation = &(garcia->m_npc_garcia_damage_received_left);

						if (garcia->m_current_animation->Finished())
						{
							garcia->m_current_animation->Reset();
							garcia->m_state = enemy_state::WALKING;
							garcia->m_ai_walk = true;
						}
					}

					if (m_player->m_float_attack == true)
					{
						if (garcia->m_face_right)
							garcia->m_current_animation = &(garcia->m_npc_garcia_down_right);
						else
							garcia->m_current_animation = &(garcia->m_npc_garcia_down_left);
					}
							
					if(garcia->m_current_animation == &(garcia->m_npc_garcia_down_right))
					{
						if (garcia->m_current_animation->Finished())
						{
							if (garcia->m_dead == false)
							{
								garcia->m_current_animation->Reset();
								garcia->m_state = enemy_state::UP;
								garcia->m_current_animation = &(garcia->m_npc_garcia_up_right);
							}
						}
					}
					if (garcia->m_current_animation == &(garcia->m_npc_garcia_down_left))
					{
						if (garcia->m_current_animation->Finished())
						{
							if (garcia->m_dead == false)
							{
								garcia->m_current_animation->Reset();
								garcia->m_state = enemy_state::UP;
								garcia->m_current_animation = &(garcia->m_npc_garcia_up_left);
							}
						}
					}

				}
			}
			

			if (enemy->m_state == enemy_state::UP)
			{
				if (!strcmp(enemy->m_name, "garcia"))
				{
					Garcia *garcia = (Garcia*)enemy;

					if (garcia->m_face_right)
					{
						garcia->m_current_animation = &(garcia->m_npc_garcia_up_right);
						
						if (garcia->m_current_animation->Finished())
						{
							garcia->m_current_animation->Reset();
							garcia->m_state = enemy_state::WALKING;
							garcia->m_ai_walk = true;
							m_player->m_float_attack = false;
						}
					}
					else
					{
						garcia->m_current_animation = &(garcia->m_npc_garcia_up_left);

						if (garcia->m_current_animation->Finished())
						{
							garcia->m_current_animation->Reset();
							garcia->m_state = enemy_state::WALKING;
							garcia->m_ai_walk = true;
							m_player->m_float_attack = false;
						}
					}
				}

			}

			//Only garcia enters punch1,punch2 states
			if (enemy->m_state == enemy_state::PUNCH1)
			{
				Garcia *garcia = (Garcia*)enemy;

				if (garcia->m_face_right)
				{
					garcia->m_current_animation = &(garcia->m_npc_garcia_punch_right1);

					if (garcia->m_current_animation->Finished())
					{
						garcia->m_punch_hits++;
						garcia->m_state = enemy_state::IDLE;
						garcia->m_current_animation->Reset();
					}
				}
				else
				{
					garcia->m_current_animation = &(garcia->m_npc_garcia_punch_left1);

					if (garcia->m_current_animation->Finished())
					{
						garcia->m_punch_hits++;
						garcia->m_state = enemy_state::IDLE;
						garcia->m_current_animation->Reset();
					}

				}
			}

			if (enemy->m_state == enemy_state::PUNCH2)
			{
				Garcia *garcia = (Garcia*)enemy;

				if (garcia->m_face_right)
				{
					garcia->m_current_animation = &(garcia->m_npc_garcia_punch_right2);

					if (garcia->m_current_animation->Finished())
					{
						garcia->m_punch_hits++;
						garcia->m_state = enemy_state::IDLE;
						garcia->m_current_animation->Reset();
						garcia->m_current_animation = &(garcia->m_npc_garcia_idle_right);
					}
				}
				else
				{
					garcia->m_current_animation = &(garcia->m_npc_garcia_punch_left2);

					if (garcia->m_current_animation->Finished())
					{
						garcia->m_punch_hits++;
						garcia->m_state = enemy_state::IDLE;
						garcia->m_current_animation->Reset();
						garcia->m_current_animation = &(garcia->m_npc_garcia_idle_left);
					}
				}
			}
			//Only garcia_knife enters knife_attack state
			if (enemy->m_state == enemy_state::KNIFE_ATTACK)
			{
				GarciaKnife *garcia_knife = (GarciaKnife*)enemy;

				if (garcia_knife->m_face_right)
					garcia_knife->m_current_animation = &(garcia_knife->m_npc_garcia_knife_attack_right);
				else
					garcia_knife->m_current_animation = &(garcia_knife->m_npc_garcia_knife_attack_left);

				if (garcia_knife->m_current_animation->Finished())
				{
					garcia_knife->m_state = enemy_state::IDLE;
					garcia_knife->m_current_animation->Reset();
					garcia_knife->m_allow_attack = false;

					if (garcia_knife->m_face_right)
						garcia_knife->m_current_animation = &(garcia_knife->m_npc_garcia_knife_idle_right);
					else
						garcia_knife->m_current_animation = &(garcia_knife->m_npc_garcia_knife_idle_left);
				}
			}
			//Only punky enters ground_attack state
			if (enemy->m_state == enemy_state::GROUND_ATTACK)
			{
				Punky *punky = (Punky*)enemy;

				if (punky->m_restart_animation)
				{
					punky->m_timer_count = 0;
					punky->m_restart_animation = false;

					if (punky->m_face_right)
						punky->m_current_animation = &(punky->m_npc_punky_ground_attack_right1);
					else
						punky->m_current_animation = &(punky->m_npc_punky_ground_attack_left1);
				}

				//face right
				if (punky->m_current_animation == &(punky->m_npc_punky_ground_attack_right1) && punky->m_timer_count == 0)
				{
					if (punky->m_current_animation->Finished())
					{
						punky->m_current_animation->Reset();
						punky->m_current_animation = &(punky->m_npc_punky_ground_attack_right2);
					}
				}
				if (punky->m_current_animation == &(punky->m_npc_punky_ground_attack_right2))
				{
					punky->m_position.x += punky->m_ground_attack_speed;
					UpdateColliderPosition(punky);
					punky->m_timer_count++;

					//move grab collider to the feet
					punky->m_enemy_grab_collider->SetPos((punky->m_position.x + punky->m_x_ref - punky->m_enemy_grab_collider->m_rect.w / 2) + 50, punky->m_depth);
					if (App->player->m_player_collider->CheckCollision(punky->m_enemy_grab_collider->m_rect))
					{
						if (punky->m_allow_attack) {
							m_player->m_state = player_state::DAMAGED;
							m_player->m_enemy_attacking_player = enemy;
							punky->m_allow_attack = false;
						}
					}

					if (punky->m_timer_count >= punky->m_ground_attack_range)
					{
						punky->m_current_animation->Reset();
						punky->m_current_animation = &(punky->m_npc_punky_ground_attack_right1);
					}
				}
				if (punky->m_current_animation == &(punky->m_npc_punky_ground_attack_right1) && punky->m_timer_count != 0)
				{
					
					if (punky->m_current_animation->Finished())
					{
						punky->m_position.x += 20;
						UpdateColliderPosition(punky);

						punky->m_state = enemy_state::IDLE;
						punky->m_restart_animation = true;
						punky->m_current_animation->Reset();
						punky->m_timer_count = 0;
						punky->m_current_animation = &(punky->m_npc_punky_idle_right);
					}
				}


				//face left
				if (punky->m_current_animation == &(punky->m_npc_punky_ground_attack_left1) && punky->m_timer_count == 0)
				{
					if (punky->m_current_animation->Finished())
					{
						punky->m_current_animation->Reset();
						punky->m_current_animation = &(punky->m_npc_punky_ground_attack_left2);
						
					}
				}
				if (punky->m_current_animation == &(punky->m_npc_punky_ground_attack_left2))
				{
					punky->m_timer_count++;
					punky->m_position.x -= punky->m_ground_attack_speed;
					UpdateColliderPosition(punky);

					//move grab collider to the feet
					punky->m_enemy_grab_collider->SetPos((punky->m_position.x + punky->m_x_ref - punky->m_enemy_grab_collider->m_rect.w / 2) - 50, punky->m_depth);
					if (App->player->m_player_collider->CheckCollision(punky->m_enemy_grab_collider->m_rect))
					{
						if (punky->m_allow_attack)
						{
							m_player->m_state = player_state::DAMAGED;
							punky->m_allow_attack = false;
							m_player->m_enemy_attacking_player = punky;
						}
					}

					if (punky->m_timer_count >= punky->m_ground_attack_range)
					{
						punky->m_current_animation->Reset();
						punky->m_current_animation = &(punky->m_npc_punky_ground_attack_left1);
						UpdateColliderPosition(punky);
					}		
				}

				if (punky->m_current_animation == &(punky->m_npc_punky_ground_attack_left1) && punky->m_timer_count != 0)
				{
					
					if (m_player->m_current_animation->Finished())
					{
						punky->m_position.x -= 20;
						UpdateColliderPosition(punky);

						punky->m_state = enemy_state::IDLE;
						punky->m_restart_animation = true;
						punky->m_current_animation->Reset();
						punky->m_timer_count = 0;
						punky->m_current_animation = &(punky->m_npc_punky_idle_left);
					}
				}
			}

			//Only nora enters whip_attack state
			if (enemy->m_state == enemy_state::WHIP_ATTACK)
			{
				Nora *nora = (Nora*)enemy;

				if (nora->m_restart_animation)
				{
					nora->m_restart_animation = false;

					if (nora->m_face_right)
						nora->m_current_animation = &(nora->m_npc_nora_attack_right1);
					else
						nora->m_current_animation = &(nora->m_npc_nora_attack_left1);
				}

				//Face right
				if (nora->m_current_animation ==  &(nora->m_npc_nora_attack_right1))
				{
					//move grab collider closer to the hit area 
					nora->m_enemy_grab_collider->SetPos((nora->m_position.x + nora->m_x_ref - nora->m_enemy_grab_collider->m_rect.w / 2) + 45, nora->m_depth);
					
					if (nora->m_current_animation->Finished())
					{
						nora->m_current_animation->Reset();
						nora->m_current_animation = &(nora->m_npc_nora_attack_right2);
					}
				}
				if (nora->m_current_animation == &(nora->m_npc_nora_attack_right2))
				{
					if (App->player->m_player_collider->CheckCollision(nora->m_enemy_grab_collider->m_rect))
					{
						if (nora->m_allow_attack) {
							m_player->m_state = player_state::DAMAGED;
							m_player->m_enemy_attacking_player = nora;

						}
					}
					
					if (nora->m_current_animation->Finished())
					{
						UpdateColliderPosition(nora);
						nora->m_state = enemy_state::IDLE;
						nora->m_restart_animation = true;
						nora->m_allow_attack = false;
						nora->m_current_animation->Reset();
						nora->m_current_animation = &(nora->m_npc_nora_idle_right);
					}
				}

				//Face left
				if (nora->m_current_animation == &(nora->m_npc_nora_attack_left1))
				{
					//move grab collider closer to the hit area 
					nora->m_enemy_grab_collider->SetPos((nora->m_position.x + nora->m_x_ref - nora->m_enemy_grab_collider->m_rect.w / 2) - 45, nora->m_depth);
					
					if (nora->m_current_animation->Finished())
					{
						nora->m_current_animation->Reset();
						nora->m_current_animation = &(nora->m_npc_nora_attack_left2);
					}
				}
				if (nora->m_current_animation == &(nora->m_npc_nora_attack_left2))
				{
					if (App->player->m_player_collider->CheckCollision(nora->m_enemy_grab_collider->m_rect))
					{
						if (nora->m_allow_attack) {
							m_player->m_state = player_state::DAMAGED;
							m_player->m_enemy_attacking_player = nora;

						}
					}

					if (nora->m_current_animation->Finished())
					{
						UpdateColliderPosition(nora);
						nora->m_state = enemy_state::IDLE;
						nora->m_restart_animation = true;
						nora->m_allow_attack = false;
						nora->m_current_animation->Reset();
						nora->m_current_animation = &(nora->m_npc_nora_idle_left);
					}
				}
	
			}

			//Only antonio enters kick state
			if (enemy->m_state == enemy_state::KICK)
			{
				Antonio *antonio = (Antonio*)enemy;

				if (antonio->m_face_right)
				{
					antonio->m_current_animation = &(antonio->m_npc_antonio_kick_right);
					if (antonio->m_current_animation->Finished())
					{
						antonio->m_current_animation->Reset();
						antonio->m_state = enemy_state::IDLE;
						antonio->m_allow_attack = false;
						antonio->m_current_animation = &(antonio->m_npc_antonio_idle_right);
						m_player->m_state = player_state::DAMAGED;
					}
				}
				else
				{
					antonio->m_current_animation = &(antonio->m_npc_antonio_kick_left);
					if (antonio->m_current_animation->Finished())
					{
						antonio->m_current_animation->Reset();
						antonio->m_state = enemy_state::IDLE;
						antonio->m_allow_attack = false;
						antonio->m_current_animation = &(antonio->m_npc_antonio_idle_left);
						m_player->m_state = player_state::DAMAGED;
					}
				}
			}
			//Only antonio enters throw_boomerang state
			if (enemy->m_state == enemy_state::THROW_BOOMERANG)
			{
				Antonio *antonio = (Antonio*)enemy;

				if (antonio->m_face_right)
				{
					antonio->m_current_animation = &(antonio->m_npc_antonio_throw_boomerang_right);
					if (antonio->m_current_animation->Finished())
					{
						antonio->m_current_animation->Reset();
						antonio->m_current_animation = &(antonio->m_npc_antonio_idle_right);
						antonio->m_carrying_boomerang = false;
						antonio->m_allow_attack = false;
						antonio->m_state = enemy_state::IDLE;
					}
				}
				else
				{
					antonio->m_current_animation = &(antonio->m_npc_antonio_throw_boomerang_left);
					if (antonio->m_current_animation->Finished())
					{
						antonio->m_current_animation->Reset();
						antonio->m_current_animation = &(antonio->m_npc_antonio_idle_left);
						antonio->m_carrying_boomerang = false;
						antonio->m_allow_attack = false;
						antonio->m_state = enemy_state::IDLE;
					}
				}
			}
			//Only antonio enters recover_boomerang state
			if (enemy->m_state == enemy_state::RECOVER_BOOMERANG)
			{
				Antonio *antonio = (Antonio*)enemy;

				if (antonio->m_face_right)
				{
					antonio->m_current_animation = &(antonio->m_npc_antonio_recover_boomerang_right);
					if (antonio->m_current_animation->Finished())
					{
						antonio->m_carrying_boomerang = true;
						antonio->m_current_animation->Reset();
						antonio->m_state = enemy_state::IDLE;
					}
				}
				else
				{
					antonio->m_current_animation = &(antonio->m_npc_antonio_recover_boomerang_left);
					if (antonio->m_current_animation->Finished())
					{
						antonio->m_carrying_boomerang = true;
						antonio->m_current_animation->Reset();
						antonio->m_state = enemy_state::IDLE;
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

