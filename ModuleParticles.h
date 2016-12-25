#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

struct Particle
{
	bool to_delete = false;

	// TODO 1: Fill in the structure with all the properties you need for each particle
	iPoint particlePosition;
	int particleSpeed;
	int lifeTime;
	Animation *animation;
	// TODO 11: Add an optional collider to each particle
	Collider *particleCollider = nullptr;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y, collider_type c_type); // feel free to expand this call

private:

	SDL_Texture* graphics = nullptr;
	std::list<Particle*> active;
	

public:

	uint fxLaser = 0;
	uint fxExplosion = 0;
	Particle *particle;

	// prototype particles go here ...
	Particle *laserParticle;
	Particle *explosionParticle;

};

#endif // __MODULEPARTICLES_H__