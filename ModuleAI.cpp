#include "ModuleAI.h"
#include "ModulePlayer.h"
#include "Enemy.h"
#include "Player.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "ModuleEnemies.h"

ModuleAI::ModuleAI(bool active) : Module(active) {}
ModuleAI::~ModuleAI() {}

bool ModuleAI::Start()
{
	return true;
}

update_status ModuleAI::Update()
{
	m_time = SDL_GetTicks();
	if (m_time - m_update_time >= m_dt)
	{
		m_do_logic = true;
	}
	if (m_do_logic)
	{
		m_do_logic = false;
		
		
		for (auto it = App->entities.begin(); it != App->entities.end(); it++)
		{
			if ((*it)->m_type == entity_type::ENEMY)
			{
				((Enemy*)*it)->m_ai_controller.UpdateBehaviour();	
			}
		}
	}
	
	return UPDATE_CONTINUE;
}

