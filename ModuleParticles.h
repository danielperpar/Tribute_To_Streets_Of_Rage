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
	bool m_to_delete = false;
	// TODO 1: Fill in the structure with all the properties you need for each particle
	iPoint m_position;
	Animation *m_hit_effect_animation_right;
	std::list<int*> m_animation_list;
	// TODO 11: Add an optional collider to each particle

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

	void AddParticle(const Particle& particle, int x, int y); 

private:

	SDL_Texture* graphics = nullptr;
	std::list<Particle*> m_active;

public:

	uint m_hit_sound = 0;
	Particle *m_hit_effect = nullptr;

};

#endif // __MODULEPARTICLES_H__