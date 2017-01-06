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


ModuleEnemies::ModuleEnemies(bool active) : Module(active) {}


ModuleEnemies::~ModuleEnemies()
{}

// Load assets
bool ModuleEnemies::Start()
{
	LOG("Loading enemy");

	graphics = App->textures->Load("assets/spritesheets/enemies.png");

	//Debug test
	enemy = (Enemy*)EntityManager::CreateEntity(graphics, "nora", entity_type::ENEMY, { 800, 100 }, 0);
	enemy->m_state = enemy_state::IDLE;


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
bool ModuleEnemies::CleanUp()
{
	LOG("Unloading enemies");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleEnemies::Update()
{

	time = SDL_GetTicks();
	if (time - update_time >= dt)
	{
		do_logic = true;
	}
	if (do_logic)
	{
		do_logic = false;
		update_time = SDL_GetTicks();

	
		for (auto it = App->entities.begin(); it != App->entities.end(); it++)
	{
		if ((*it)->m_type == entity_type::ENEMY)
		{
			enemy = (Enemy*)*it;

			if (enemy->m_state == enemy_state::IDLE)
			{
				//Inputs will be substituted by AI signals
				
				if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
				{
					if (enemy->m_player_to_hit)
					{
						if (!strcmp(enemy->m_name, "garcia"))
						{
							if (enemy->m_punch_hits < 2)
							{
								enemy->m_state = enemy_state::PUNCH1;
							}
							if (enemy->m_punch_hits == 2)
							{
								enemy->m_state = enemy_state::PUNCH2;
							}
							if (enemy->m_punch_hits > 2)
							{
								enemy->m_punch_hits = 0;
								enemy->m_state = enemy_state::PUNCH1;
							}
						}
						if (!strcmp(enemy->m_name, "garcia_knife"))
						{
							enemy->m_state = enemy_state::KNIFE_ATTACK;
						}
						if (!strcmp(enemy->m_name, "punky"))
						{
							enemy->m_state = enemy_state::GROUND_ATTACK;
						}
						if (!strcmp(enemy->m_name, "nora"))
						{
							enemy->m_state = enemy_state::WHIP_ATTACK;
						}
						if (!strcmp(enemy->m_name, "antonio"))
						{
							enemy->m_state = enemy_state::KICK;
						}

					}
					else
					{
						enemy->m_state = enemy_state::IDLE;
					}
				}
				
			}

			//Inputs will be substituted by AI signals
			if (enemy->m_state == enemy_state::IDLE ||
				enemy->m_state == enemy_state::WALKING  &&
				App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE &&
				App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE &&
				App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE &&
				App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE &&
				App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE &&
				App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE &&
				App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE)
			{
				enemy->m_state = enemy_state::IDLE;
			}

			if (enemy->m_state == enemy_state::IDLE)
			{

				if (!strcmp(enemy->m_name, "garcia"))
				{
					enemy->m_current_animation = enemy->m_face_right ? &(enemy->m_npc_garcia_idle_right) : &(enemy->m_npc_garcia_idle_left);

				}
				if (!strcmp(enemy->m_name, "garcia_knife"))
				{
					enemy->m_current_animation = enemy->m_face_right ? &(enemy->m_npc_garcia_knife_idle_right) : &(enemy->m_npc_garcia_knife_idle_left);

				}
				if (!strcmp(enemy->m_name, "punky"))
				{
					enemy->m_current_animation = enemy->m_face_right ? &(enemy->m_npc_punky_idle_right) : &(enemy->m_npc_punky_idle_left);
				}
				if (!strcmp(enemy->m_name, "nora"))
				{
					enemy->m_current_animation = enemy->m_face_right ? &(enemy->m_npc_nora_idle_right) : &(enemy->m_npc_nora_idle_left);
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
				}
			}

			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			{
				if (enemy->m_face_right)
					enemy->m_face_right = false;

				enemy->m_position.x -= (int)enemy->m_speed;

				if (enemy->m_state == enemy_state::IDLE || enemy->m_state == enemy_state::WALKING)
				{
					enemy->m_state = enemy_state::WALKING;
					
					if (!strcmp(enemy->m_name, "garcia"))
					{
						if (enemy->m_current_animation != &(enemy->m_npc_garcia_walk_left))
						{
							enemy->m_current_animation = &(enemy->m_npc_garcia_walk_left);
							enemy->m_current_animation->Reset();
						}
					}
					if (!strcmp(enemy->m_name, "garcia_knife"))
					{
						if (enemy->m_current_animation != &(enemy->m_npc_garcia_knife_walk_left))
						{
							enemy->m_current_animation = &(enemy->m_npc_garcia_knife_walk_left);
							enemy->m_current_animation->Reset();
						}
					}
					if (!strcmp(enemy->m_name, "punky"))
					{
						if (enemy->m_current_animation != &(enemy->m_npc_punky_walk_left))
						{
							enemy->m_current_animation = &(enemy->m_npc_punky_walk_left);
							enemy->m_current_animation->Reset();
						}
					}
					if (!strcmp(enemy->m_name, "nora"))
					{
						if (enemy->m_current_animation != &(enemy->m_npc_nora_walk_left))
						{
							enemy->m_current_animation = &(enemy->m_npc_nora_walk_left);
							enemy->m_current_animation->Reset();
						}
					}
					if (!strcmp(enemy->m_name, "antonio"))
					{
						if (enemy->m_carrying_boomerang)
						{
							if (enemy->m_current_animation != &(enemy->m_npc_antonio_boomerang_walk_left))
							{
								enemy->m_current_animation = &(enemy->m_npc_antonio_boomerang_walk_left);
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

			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			{
				if (enemy->m_face_right == false)
					enemy->m_face_right = true;

				enemy->m_position.x += (int)enemy->m_speed;

				if (enemy->m_state == enemy_state::IDLE || enemy->m_state == enemy_state::WALKING)
				{
					enemy->m_state = enemy_state::WALKING;

					if (!strcmp(enemy->m_name, "garcia"))
					{
						if (enemy->m_current_animation != &(enemy->m_npc_garcia_walk_right))
						{
							enemy->m_current_animation = &(enemy->m_npc_garcia_walk_right);
							enemy->m_current_animation->Reset();
						}
					}
					if (!strcmp(enemy->m_name, "garcia_knife"))
					{
						if (enemy->m_current_animation != &(enemy->m_npc_garcia_knife_walk_right))
						{
							enemy->m_current_animation = &(enemy->m_npc_garcia_knife_walk_right);
							enemy->m_current_animation->Reset();
						}
					}
					if (!strcmp(enemy->m_name, "punky"))
					{
						if (enemy->m_current_animation != &(enemy->m_npc_punky_walk_right))
						{
							enemy->m_current_animation = &(enemy->m_npc_punky_walk_right);
							enemy->m_current_animation->Reset();
						}
					}
					if (!strcmp(enemy->m_name, "nora"))
					{
						if (enemy->m_current_animation != &(enemy->m_npc_nora_walk_right))
						{
							enemy->m_current_animation = &(enemy->m_npc_nora_walk_right);
							enemy->m_current_animation->Reset();
						}
					}
					if (!strcmp(enemy->m_name, "antonio"))
					{
						if (enemy->m_carrying_boomerang)
						{
							if (enemy->m_current_animation != &(enemy->m_npc_antonio_boomerang_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_antonio_boomerang_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
						else
						{
							if (enemy->m_current_animation != &(enemy->m_npc_antonio_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_antonio_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
					}
				}
			}

			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			{
				if (enemy->m_state == enemy_state::WALKING || enemy->m_state == enemy_state::IDLE)
				{
					enemy->m_position.y -= (int)enemy->m_speed;

					if (enemy->m_face_right)
					{

						if (!strcmp(enemy->m_name, "garcia"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_garcia_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_garcia_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "garcia_knife"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_garcia_knife_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_garcia_knife_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "punky"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_punky_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_punky_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "nora"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_nora_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_nora_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "antonio"))
						{
							if (enemy->m_carrying_boomerang)
							{
								if (enemy->m_current_animation != &(enemy->m_npc_antonio_boomerang_walk_right))
								{
									enemy->m_current_animation = &(enemy->m_npc_antonio_boomerang_walk_right);
									enemy->m_current_animation->Reset();
								}
							}
							else
							{
								if (enemy->m_current_animation != &(enemy->m_npc_antonio_walk_right))
								{
									enemy->m_current_animation = &(enemy->m_npc_antonio_walk_right);
									enemy->m_current_animation->Reset();
								}
							}
						}
					}
					else
					{
						if (!strcmp(enemy->m_name, "garcia"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_garcia_walk_left))
							{
								enemy->m_current_animation = &(enemy->m_npc_garcia_walk_left);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "garcia_knife"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_garcia_knife_walk_left))
							{
								enemy->m_current_animation = &(enemy->m_npc_garcia_knife_walk_left);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "punky"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_punky_walk_left))
							{
								enemy->m_current_animation = &(enemy->m_npc_punky_walk_left);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "nora"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_nora_walk_left))
							{
								enemy->m_current_animation = &(enemy->m_npc_nora_walk_left);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "antonio"))
						{
							if (enemy->m_carrying_boomerang)
							{
								if (enemy->m_current_animation != &(enemy->m_npc_antonio_boomerang_walk_left))
								{
									enemy->m_current_animation = &(enemy->m_npc_antonio_boomerang_walk_left);
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

			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			{
				if (enemy->m_state == enemy_state::WALKING || enemy->m_state == enemy_state::IDLE)
				{
					enemy->m_position.y += (int)enemy->m_speed;

					if (enemy->m_face_right)
					{
						if (!strcmp(enemy->m_name, "garcia"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_garcia_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_garcia_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "garcia_knife"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_garcia_knife_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_garcia_knife_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "punky"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_punky_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_punky_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "nora"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_nora_walk_right))
							{
								enemy->m_current_animation = &(enemy->m_npc_nora_walk_right);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "antonio"))
						{
							if (enemy->m_carrying_boomerang)
							{
								if (enemy->m_current_animation != &(enemy->m_npc_antonio_boomerang_walk_right))
								{
									enemy->m_current_animation = &(enemy->m_npc_antonio_boomerang_walk_right);
									enemy->m_current_animation->Reset();
								}
							}
							else
							{
								if (enemy->m_current_animation != &(enemy->m_npc_antonio_walk_right))
								{
									enemy->m_current_animation = &(enemy->m_npc_antonio_walk_right);
									enemy->m_current_animation->Reset();
								}
							}
						}
					}
					else
					{
						if (!strcmp(enemy->m_name, "garcia"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_garcia_walk_left))
							{
								enemy->m_current_animation = &(enemy->m_npc_garcia_walk_left);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "garcia_knife"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_garcia_knife_walk_left))
							{
								enemy->m_current_animation = &(enemy->m_npc_garcia_knife_walk_left);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "punky"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_punky_walk_left))
							{
								enemy->m_current_animation = &(enemy->m_npc_punky_walk_left);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "nora"))
						{
							if (enemy->m_current_animation != &(enemy->m_npc_nora_walk_left))
							{
								enemy->m_current_animation = &(enemy->m_npc_nora_walk_left);
								enemy->m_current_animation->Reset();
							}
						}
						if (!strcmp(enemy->m_name, "antonio"))
						{
							if (enemy->m_carrying_boomerang)
							{
								if (enemy->m_current_animation != &(enemy->m_npc_antonio_boomerang_walk_left))
								{
									enemy->m_current_animation = &(enemy->m_npc_antonio_boomerang_walk_left);
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
				}
			}
			//Only punky enters ground_attack state
			if (enemy->m_state == enemy_state::GROUND_ATTACK)
			{
				if (enemy->m_restart_animation)
				{
					enemy->m_timer_count = 0;
					enemy->m_restart_animation = false;

				}

				enemy->m_timer_count++;

				if (enemy->m_face_right)
				{
					enemy->m_current_animation = &(enemy->m_npc_punky_ground_attack_right);
					enemy->m_position.x += enemy->m_ground_attack_speed;
				}
				else
				{
					enemy->m_current_animation = &(enemy->m_npc_punky_ground_attack_left);
					enemy->m_position.x -= enemy->m_ground_attack_speed;
				}

				if (enemy->m_timer_count >= enemy->m_ground_attack_range)
				{
					if (enemy->m_face_right)
						enemy->m_position.x += 20;
					else
						enemy->m_position.x -= 20;

					enemy->m_state = enemy_state::IDLE;
					enemy->m_restart_animation = true;
					enemy->m_current_animation->Reset();
					enemy->m_timer_count = 0;
				}
			}

			//Only nora enters whip_attack state
			if (enemy->m_state == enemy_state::WHIP_ATTACK)
			{
				if (enemy->m_face_right)
					enemy->m_current_animation = &(enemy->m_npc_nora_attack_right);
				else
					enemy->m_current_animation = &(enemy->m_npc_nora_attack_left);

				if (enemy->m_current_animation->Finished())
				{
					enemy->m_state = enemy_state::IDLE;
					enemy->m_current_animation->Reset();
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
					}
				}
				else
				{
					enemy->m_current_animation = &(enemy->m_npc_antonio_kick_left);
					if (enemy->m_current_animation->Finished())
					{
						enemy->m_current_animation->Reset();
						enemy->m_state = enemy_state::IDLE;
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

// TODO 13: Make so is the laser collides, it is removed and create an explosion particle at its position

// TODO 14: Make so if the player collides, it is removed and create few explosions at its positions
// then fade away back to the first screen (use the "destroyed" bool already created 
// You will need to create, update and destroy the collider with the player

void ModuleEnemies::OnCollision(Collider* collider1, Collider* collider2)
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
