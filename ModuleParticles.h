#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Entity.h"
class AIController;
struct SDL_Texture;
struct Collider;


class Particle : public Entity
{

public:
	bool m_to_delete = false;
	bool m_face_right = true;
	bool m_forward = true;
	float m_speed_x = 0.0f;
	float m_speed_y = 0.0f;

	iPoint m_start_position;
	Animation *m_animation_right = nullptr;
	Animation *m_animation_left = nullptr;
	AIController *m_ai_controller = nullptr;
	Entity *m_owner = nullptr;
	Collider *m_collider = nullptr;
	std::list<int*> m_animation_list;

public:
	Particle(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth);
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

	void AddParticle(const Particle& particle, int x, int y, collider_type collider_type); 

private:

	SDL_Texture* graphics = nullptr;
	std::list<Particle*> m_active;

public:

	uint m_hit_sound = 0;
	Particle *m_particle = nullptr;


	//prototype particles
	Particle *m_hit_effect = nullptr;
	Particle *m_boomerang = nullptr;
	
	SDL_Rect anim_R;
	SDL_Rect anim_L;
};

#endif // __MODULEPARTICLES_H__