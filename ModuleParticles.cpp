#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "Animation.h"
#include "JSONDataLoader.h"
#include "Utilities.h"

ModuleParticles::ModuleParticles()
{}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("assets/spritesheets/axel.png");
	
	//m_hit_effect = new Particle(graphics, "hit_effect", entity_type::PARTICLE, { 0,0 }, 0);
	//m_hit_effect->m_animation_right = new Animation();
	//m_hit_effect->m_animation_left = new Animation();
	//
	//JSONDataLoader::Load("assets/json/sprites_data.json", "playerHitEffectRight", m_hit_effect->m_animation_list, *(m_hit_effect->m_animation_right));
	//m_hit_effect->m_animation_right->loop = false;
	//m_hit_effect->m_animation_right->speed = 1.0f;
	//Utilities::free_list(m_hit_effect->m_animation_list);

	//JSONDataLoader::Load("assets/json/sprites_data.json", "playerHitEffectLeft", m_hit_effect->m_animation_list, *(m_hit_effect->m_animation_left));
	//m_hit_effect->m_animation_left->loop = false;
	//m_hit_effect->m_animation_left->speed = 1.0f;
	//Utilities::free_list(m_hit_effect->m_animation_list);

	//m_hit_effect->m_ai_controller = new AIController();
	////m_hit_sound = App->audio->LoadFx("rtype/laser.wav");  //cargar sonido puñetazo


	//m_boomerang = new Particle(graphics, "boomerang", entity_type::PARTICLE, { 0,0 }, 0);
	//m_boomerang->m_animation_right = new Animation();

	//JSONDataLoader::Load("assets/json/sprites_data.json", "npcItemBoomerangRight", m_boomerang->m_animation_list, *(m_boomerang->m_animation_right));
	//m_boomerang->m_animation_right->loop = true;
	//m_boomerang->m_animation_right->speed = 0.1f;
	//Utilities::free_list(m_boomerang->m_animation_list);

	//m_boomerang->m_animation_left = new Animation();

	//JSONDataLoader::Load("assets/json/sprites_data.json", "npcItemBoomerangLeft", m_boomerang->m_animation_list, *(m_boomerang->m_animation_left));
	//m_boomerang->m_animation_left->loop = true;
	//m_boomerang->m_animation_left->speed = 0.1f;
	//Utilities::free_list(m_boomerang->m_animation_list);

	//m_boomerang->m_ai_controller = new AIController();
	//m_boomerang->m_speed_x = 3.0f;
	//m_boomerang->m_speed_y = 3.0f;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (list<Particle*>::iterator it = m_active.begin(); it != m_active.end(); ++it)
	{
		RELEASE(*it);
	}
	m_active.clear();

	return true;
}

// Update: draw particles
update_status ModuleParticles::Update()
 {
	//for (list<Particle*>::iterator it = m_active.begin(); it != m_active.end();)
	//{
	//	Particle* p = *it;

	//	if(p->Update() == false)
	//	{
	//		RELEASE(*it);
	//		it = m_active.erase(it);
	//	}
	//	else
	//		++it;
	//}

	//for (list<Particle*>::iterator it = m_active.begin(); it != m_active.end(); ++it)
	//{
	//	//Debug
	//	anim_R = (*it)->m_animation_right->GetCurrentFrame();
	//	anim_L = (*it)->m_animation_left->GetCurrentFrame();

	//	if((*it)->m_face_right)
	//		App->renderer->Blit(graphics, (*it)->m_position.x, (*it)->m_position.y, &anim_R);
	//	else
	//		App->renderer->Blit(graphics, (*it)->m_position.x, (*it)->m_position.y, &anim_L);
	//}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, collider_type collider_type)
{
	m_particle = new Particle(particle);
	m_particle->m_position.x = x;
	m_particle->m_position.y = y;
	m_particle->m_start_position.x = x;
	m_particle->m_start_position.y = y;
	
	SDL_Rect collider;
	if (collider_type == collider_type::BOSS_BOOMERANG)
	{
		collider.x = 0;
		collider.y = 0;
		collider.w = 20;
		collider.h = 15;
	}

	m_particle->m_collider = App->collision->AddCollider(collider, m_particle, collider_type);
	m_active.push_back(m_particle);

}

// -------------------------------------------------------------
// -------------------------------------------------------------
//Particle(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int m_depth);
Particle::Particle(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, name, type, position, depth){}
Particle::Particle(const Particle& p) 
{
	m_texture = p.m_texture;
	m_name = p.m_name;
	m_type = p.m_type;
	m_position = p.m_position;
	m_start_position = p.m_start_position;
	m_to_delete = p.m_to_delete;
	m_animation_right = p.m_animation_right;
	m_animation_left = p.m_animation_left;
	m_forward = p.m_forward;
	m_depth = p.m_depth;
	m_owner = p.m_owner;
	m_speed_x = p.m_speed_x;
	m_speed_y = p.m_speed_y;
	m_ai_controller = p.m_ai_controller;
	
}

Particle::~Particle()
{
	RELEASE(m_animation_right);	
	RELEASE(m_animation_left);
}

bool Particle::Update()
{
	bool ret = true;

	if (!strcmp(m_name, "hit_effect"))
	{
		if (m_face_right)
		{
			if (m_animation_right->Finished())
			{
				m_to_delete = true;
			}
		}
		else
		{
			if (m_animation_left->Finished())
			{
				m_to_delete = true;
			}
		}
	}

	/*if (!strcmp(m_name, "boomerang"))
	{
		m_ai_controller->UpdateBehaviour(this, m_owner);
		
		if (((Enemy*)m_owner)->m_carrying_boomerang == false)
			m_to_delete = true;
	}*/

	return ret;
}

