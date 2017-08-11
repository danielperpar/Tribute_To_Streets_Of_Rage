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

// --------------------------------------- PARTICLE ----------------------

Particle::Particle(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, curr_anim, name, type, position, depth){}
Particle::~Particle(){}

//--------------------------------- BOOMERANG ----------------------

Boomerang::Boomerang(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth) : Particle(texture, curr_anim, name, type, position, depth) 
{
	LoadStats();
	LoadColliders();
	LoadSoundFX();
	LoadParticleAnimations();
}

Boomerang::Boomerang(const Boomerang &boomerang) : Particle(boomerang.texture, boomerang.curr_anim, boomerang.name, boomerang.type, boomerang.position, boomerang.depth)
{
	speed = boomerang.speed;
	anim_right = boomerang.anim_right;
	anim_left = boomerang.anim_left;
}


Boomerang::~Boomerang() {}

bool Boomerang::Update()
{
	bool ret = true;
	//create boomerang movement behaviour
	return ret;
}

void Boomerang::LoadSoundFX()
{
	//m_hit_effect->m_ai_controller = new AIController();
	////m_hit_sound = App->audio->LoadFx("rtype/laser.wav");  //cargar sonido boomerang
}

void Boomerang::LoadColliders()
{
	JSONDataLoader::LoadColliderRect("assets/json/config.json", "boomerang", "collider", boomerang_rect);
}

void Boomerang::LoadStats()
{
	speed = JSONDataLoader::GetNumber("assets/json/config.json", "antonio", "speed");
	speed_vect.x = speed;
	speed_vect.y = speed;
}

void Boomerang::LoadParticleAnimations()
{
	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcItemBoomerangRight", animation_list, anim_right);
	anim_right.loop = true;
	anim_right.speed = 0.1f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcItemBoomerangLeft", animation_list, anim_left);
	anim_left.loop = true;
	anim_left.speed = 0.1f;
	Utilities::free_list(animation_list);
}


//--------------------------------- HIT EFFECT --------------
HitEffect::HitEffect(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth) : Particle(texture, curr_anim, name, type, position, depth) 
{
	LoadSoundFX();
	LoadParticleAnimations();
}

HitEffect::HitEffect(const HitEffect &effect) : Particle(effect.texture, effect.curr_anim, effect.name, effect.type, effect.position, effect.depth)
{
	anim_right = effect.anim_right;
	anim_left = effect.anim_left;
}

HitEffect::~HitEffect() {}

bool HitEffect::Update()
{
	bool ret = true;
	//create hit effect behaviour
	return ret;
}

void HitEffect::LoadSoundFX()
{
	//m_hit_effect->m_ai_controller = new AIController();
	////m_hit_sound = App->audio->LoadFx("rtype/laser.wav");  //cargar sonido puñetazo
}

void HitEffect::LoadParticleAnimations()
{
	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerHitEffectRight", animation_list, anim_right);
	anim_right.loop = false;
	anim_right.speed = 1.0f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "playerHitEffectLeft", animation_list, anim_left);
	anim_left.loop = false;
	anim_left.speed = 1.0f;
	Utilities::free_list(animation_list);
}


//-------------------------------------MODULE PARTICLES-----------------
ModuleParticles::ModuleParticles()
{}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics_hit_effect = App->textures->Load("assets/spritesheets/axel.png");
	graphics_boomerang = App->textures->Load("assets/spritesheets/enemies.png");

	hit_effect_prototype = new HitEffect(graphics_hit_effect, nullptr, "hit_effect", entity_type::PARTICLE_HIT_EFFECT, { 0,0 }, 0);
	boomerang_prototype = new Boomerang(graphics_boomerang, nullptr, "boomerang", entity_type::PARTICLE_BOOMERANG, { 0,0 }, 0);

	//------------------------------------------------------------------------------------------  Code to use when instantiating the boomerang in the scene
	/*LOG("Adding boomerang collider to ModuleCollision");
	boomerang_prototype->collider = App->collision->AddCollider(boomerang_prototype->boomerang_rect, boomerang_prototype, collider_type::BOOMERANG);*/

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics_hit_effect);
	App->textures->Unload(graphics_boomerang);

	for (list<Particle*>::iterator it = active.begin(); it != active.end(); ++it)
	{
		RELEASE(*it);
	}
	active.clear();

	return true;
}

update_status ModuleParticles::PreUpdate()
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		if ((*it)->to_delete)
		{
			RELEASE(*it);
			active.erase(it);
		}
		else
			it++;
	}

	return UPDATE_CONTINUE;
}

// Update: draw particles
update_status ModuleParticles::Update()
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end();it++)
	{
		(*it)->Update();
	}

	return UPDATE_CONTINUE;
}

Particle* ModuleParticles::GenerateParticle(entity_type type, iPoint position)
{
	Particle *particle = nullptr;

	switch (type)
	{
		case entity_type::PARTICLE_BOOMERANG:
		{
			Particle *boomerang = new Boomerang(*boomerang_prototype);
			boomerang->position = position;
			active.push_back(boomerang);
			particle = boomerang;
			break;
		}
		case entity_type::PARTICLE_HIT_EFFECT:
		{
			Particle *hit_effect = new HitEffect(*hit_effect_prototype);
			hit_effect->position = position;
			active.push_back(hit_effect);
			particle = hit_effect;
			break;
		}
	}

	return particle;
}
