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
#include "Antonio.h"
#include "ModuleWindow.h"
// --------------------------------------- PARTICLE ----------------------

Particle::Particle(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, curr_anim, name, type, position, depth){}
Particle::~Particle(){}
void Particle::Update() {}
//--------------------------------- BOOMERANG ----------------------

Boomerang::Boomerang(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth) : Particle(texture, curr_anim, name, type, position, depth) 
{
	LoadStats();
	LoadColliders();
	LoadSoundFX();
	LoadParticleAnimations();

	max_range_left = { -App->renderer->camera.x * App->renderer->camera_speed / SCREEN_SIZE, max_range_y };
	max_range_right = { -App->renderer->camera.x * App->renderer->camera_speed / SCREEN_SIZE + SCREEN_WIDTH, max_range_y };
}

Boomerang::Boomerang(const Boomerang &boomerang) : Particle(boomerang.texture, boomerang.curr_anim, boomerang.name, boomerang.type, boomerang.position, boomerang.depth)
{
	boomerang_damage = boomerang.boomerang_damage;
	speed_vect = boomerang.speed_vect;
	anim_right = boomerang.anim_right;
	anim_left = boomerang.anim_left;
	boomerang_rect = boomerang.boomerang_rect;
	max_range_left = boomerang.max_range_left;
	max_range_right = boomerang.max_range_right;
}


Boomerang::~Boomerang() {}

void Boomerang::Update()
{
	//boomerang movement behaviour

	switch (movement_stage)
	{
	case move_stage::FORWARD_MOVE_STAGE:
		ForwardStage();
		break;
	case move_stage::BACKWARDS_MOVE_STAGE:
		BackwardStage();
		break;
	case move_stage::RECOVER_BOOMERANG:
		RecoverBoomerang();
		break;
	}
}

void Boomerang::ForwardStage()
{
	if (moving_right)
	{	
		position.x += speed_vect.x;
		if (position.x >= max_range_right.x - boomerang_rect.w)
			movement_stage = move_stage::BACKWARDS_MOVE_STAGE;	
	}
	else
	{	
		position.x -= speed_vect.x;
		if (position.x <= max_range_left.x)
			movement_stage = move_stage::BACKWARDS_MOVE_STAGE;		
	}

	UpdateColliderPosition();
}

void Boomerang::BackwardStage()
{
	if (moving_right)
	{
		position.x -= speed_vect.x;

		if (position.x >= start_pos.x + 2 * (max_range_right.x - boomerang_rect.w - start_pos.x) / 3)
		{
			position.y += speed_vect.y;
		}
		else if (position.x <= start_pos.x + (max_range_right.x - boomerang_rect.w - start_pos.x) / 3)
		{
			position.y -= speed_vect.y;
		}

		if (position.x <= start_pos.x)
		{
			movement_stage = move_stage::RECOVER_BOOMERANG;
		}
	}
	else
	{
		position.x += speed_vect.x;

		if (position.x <= max_range_left.x + (start_pos.x - max_range_left.x) / 3)
		{
			position.y += speed_vect.y;
		}
		else if (position.x >= max_range_left.x + 2 * (start_pos.x - max_range_left.x) / 3)
		{
			position.y -= speed_vect.y;
		}

		if (position.x >= start_pos.x)
		{
			movement_stage = move_stage::RECOVER_BOOMERANG;
		}		
	}

	UpdateColliderPosition();
}

void Boomerang::RecoverBoomerang()
{
	to_delete = true;
	collider->to_delete = true;
	antonio->recover_boomerang = true;
	antonio->carrying_boomerang = true;
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
	speed = JSONDataLoader::GetNumber("assets/json/config.json", "boomerang", "speed");
	speed_vect.x = speed;
	speed_vect.y = speed/2;
	boomerang_damage = JSONDataLoader::GetNumber("assets/json/config.json", "boomerang", "boomerang_damage");
}

void Boomerang::LoadParticleAnimations()
{
	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcItemBoomerangRight", animation_list, anim_right);
	anim_right.loop = true;
	anim_right.speed = 0.2f;
	Utilities::free_list(animation_list);

	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "npcItemBoomerangLeft", animation_list, anim_left);
	anim_left.loop = true;
	anim_left.speed = 0.2f;
	Utilities::free_list(animation_list);
}

void Boomerang::UpdateColliderPosition()
{
	collider->SetPos(position.x, position.y);
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

void HitEffect::Update()
{
	
	//create hit effect behaviour
	
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

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	for (list<Particle*>::iterator it = active.begin(); it != active.end(); ++it)
	{
		RELEASE(*it);
	}
	active.clear();
	RELEASE(hit_effect_prototype);
	RELEASE(boomerang_prototype);

	return true;
}

update_status ModuleParticles::PreUpdate()
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		if ((*it)->to_delete)
		{
			RELEASE(*it);
			it = active.erase(it);
		}
		else
		{
			it++;
		}
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
