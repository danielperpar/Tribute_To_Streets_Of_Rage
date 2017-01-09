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
	
	m_hit_effect = new Particle();
	m_hit_effect->m_hit_effect_animation_right = new Animation();
	
	JSONDataLoader::Load("assets/json/sprites_data.json", "playerHitEffectRight", m_hit_effect->m_animation_list, *(m_hit_effect->m_hit_effect_animation_right));
	m_hit_effect->m_hit_effect_animation_right->loop = false;
	m_hit_effect->m_hit_effect_animation_right->speed = 1.0f;
	Utilities::free_list(m_hit_effect->m_animation_list);

	//m_hit_sound = App->audio->LoadFx("rtype/laser.wav");  //cargar sonido puñetazo

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

	RELEASE(m_hit_effect);
	return true;
}

// Update: draw particles
update_status ModuleParticles::Update()
 {
	for (list<Particle*>::iterator it = m_active.begin(); it != m_active.end();)
	{
		Particle* p = *it;

		if(p->Update() == false)
		{
			RELEASE(*it);
			it = m_active.erase(it);
		}
		else
			++it;
	}

	for (list<Particle*>::iterator it = m_active.begin(); it != m_active.end(); ++it)
	{
		App->renderer->Blit(graphics, (*it)->m_position.x, (*it)->m_position.y, &((*it)->m_hit_effect_animation_right->GetCurrentFrame()));
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y)
{
	m_hit_effect = new Particle(particle);
	m_hit_effect->m_position.x = x;
	m_hit_effect->m_position.y = y;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle(){}

Particle::Particle(const Particle& p) 
{
	m_position = p.m_position;
	m_to_delete = p.m_to_delete;
	m_hit_effect_animation_right = p.m_hit_effect_animation_right;
	
}

Particle::~Particle()
{
	RELEASE(m_hit_effect_animation_right);	
}

bool Particle::Update()
{
	bool ret = true;

	if (m_hit_effect_animation_right->Finished())
	{
		m_to_delete = true;
	}
	
	return ret;
}

