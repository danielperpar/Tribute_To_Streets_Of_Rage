#include <math.h>
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"
#include "Animation.h"

ModuleParticles::ModuleParticles()
{}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("rtype/particles.png");


	// TODO 2: Create a prototype for the laser particle
	// audio: rtype/laser.wav
	// coords: {232, 103, 16, 12}; {249, 103, 16, 12};
	laserParticle = new Particle();
	laserParticle->lifeTime = 80;
	laserParticle->particleSpeed = 3;
	laserParticle->animation = new Animation();
	laserParticle->animation->speed = 0.07f;
	laserParticle->animation->frames.push_back({ 232, 103, 16, 12 });
	laserParticle->animation->frames.push_back({ 249, 103, 16, 12 });
	fxLaser = App->audio->LoadFx("rtype/laser.wav");

	// TODO 12: Create a new "Explosion" particle 
	// audio: rtype/explosion.wav
	// coords: {274, 296, 33, 30}; {313, 296, 33, 30}; {346, 296, 33, 30}; {382, 296, 33, 30}; {419, 296, 33, 30}; {457, 296, 33, 30};
	explosionParticle = new Particle();
	explosionParticle->lifeTime = 35;
	explosionParticle->particleSpeed = 0;
	explosionParticle->animation = new Animation();
	explosionParticle->animation->speed = 0.07f;
	explosionParticle->animation->frames.push_back({ 274, 296, 33, 30 });
	explosionParticle->animation->frames.push_back({ 313, 296, 33, 30 });
	explosionParticle->animation->frames.push_back({ 346, 296, 33, 30 });
	explosionParticle->animation->frames.push_back({ 382, 296, 33, 30 });
	explosionParticle->animation->frames.push_back({ 419, 296, 33, 30 });
	explosionParticle->animation->frames.push_back({ 457, 296, 33, 30 });
	fxExplosion = App->audio->LoadFx("rtype/explosion.wav");


	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (list<Particle*>::iterator it = active.begin(); it != active.end(); ++it)
	{
		RELEASE(*it);
	}
	active.clear();

	RELEASE(laserParticle);
	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
 {
	for (list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		Particle* p = *it;

		if(p->Update() == false)
		{
			RELEASE(*it);
			it = active.erase(it);
		}
		else
			++it;
	}

	for (list<Particle*>::iterator it = active.begin(); it != active.end(); ++it)
	{
		App->renderer->Blit(graphics, (*it)->particlePosition.x, (*it)->particlePosition.y, &((*it)->animation->GetCurrentFrame()));
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, collider_type c_type)
{
	// TODO 4: Fill in a method to create an instance of a prototype particle
	this->particle = new Particle(particle);
	Animation *animation = new Animation();
	animation->speed = particle.animation->speed;
	animation->frames = particle.animation->frames;

	this->particle->animation = animation;
	this->particle->particlePosition.x = x;
	this->particle->particlePosition.y = y;

	SDL_Rect colliderRect = SDL_Rect();

	if (c_type == collider_type::LASER)
	{
		colliderRect.x = x;
		colliderRect.y = y;
		colliderRect.w = 16;
		colliderRect.h = 12;

		this->particle->particleCollider = App->collision->AddCollider(colliderRect, this->particle, c_type);
	}

	
	active.push_back(this->particle);

}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
}

// TODO 3: Fill in a copy constructor
Particle::Particle(const Particle& p) 
{
	particlePosition = p.particlePosition;
	particleSpeed = p.particleSpeed;
	lifeTime = p.lifeTime;
	to_delete = p.to_delete;
	animation = p.animation;

}

Particle::~Particle()
{
	RELEASE(animation);
}

bool Particle::Update()
{
	bool ret = true;

	// TODO 5: This is the core of the particle functionality.
	// Return false if the particle must be destroyed
	particlePosition.x += particleSpeed;
	--lifeTime;
	if (particleCollider != nullptr)
		particleCollider->SetPos(particlePosition.x, particlePosition.y);

	if (lifeTime <= 0)
	{
		to_delete = true;
		if (particleCollider != nullptr)
			particleCollider->to_delete = true;
		ret = false;
	}
	//particle deleted on collision
	if (this->to_delete)
		ret = false;
		
	return ret;
}

