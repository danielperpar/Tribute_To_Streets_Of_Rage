#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Entity.h"

struct SDL_Texture;
struct Collider;
class Animation;
class Antonio;
class Particle : public Entity
{

public:
	bool to_delete = false;
	bool facing_right = true;
		
	Particle(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	virtual ~Particle();
	virtual void Update();
	
};
//------------------------------------------- BOOMERANG PARTICLE---------------
class Boomerang : public Particle
{
public:
	Animation anim_right;
	Animation anim_left;
	SDL_Rect boomerang_rect;
	Collider *collider = nullptr;
	iPoint speed_vect = { 0,0 };
	int speed = 0;
	bool moving_right = false;
	iPoint start_pos = { 0,0 };
	Antonio *antonio = nullptr;
	iPoint max_range_right = { 0,0 };
	iPoint max_range_left = { 0, 0 };
	int max_range_y = 50; //antonio->offset_cast_y
	int boomerang_damage = 0;

	Boomerang(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	Boomerang(const Boomerang &boomerang);
	virtual ~Boomerang();
	virtual void Update();
	void LoadParticleAnimations();
	void LoadColliders();
	void LoadStats();
	void UpdateColliderPosition();

private:
	std::list<int*> animation_list;
	bool max_distance_reached = false;
	bool start_position_reached = false;
	

	enum class move_stage 
	{
		FORWARD_MOVE_STAGE,
		BACKWARDS_MOVE_STAGE,
		RECOVER_BOOMERANG
	};

	void ForwardStage();
	void BackwardStage();
	void RecoverBoomerang();

	move_stage movement_stage = move_stage::FORWARD_MOVE_STAGE;
};
//------------------------------------------- HIT EFFECT PARTICLE----------------
class HitEffect : public Particle
{
public:
	Animation anim_right;
	Animation anim_left;
	SDL_Rect hit_rect;
	Collider *collider = nullptr;
	uint hit_sound = 0;

	HitEffect(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	HitEffect(const HitEffect &h_effect);
	virtual ~HitEffect();
	virtual void Update();
	void LoadParticleAnimations();
	

private:
	std::list<int*> animation_list;

};
//--------------------------------------------- MODULE PARTICLES--------------
class ModuleParticles : public Module
{
public:

	std::list<Particle*> active;
	//prototype particles
	HitEffect *hit_effect_prototype = nullptr;	
	Boomerang *boomerang_prototype = nullptr;	

	ModuleParticles();
	virtual ~ModuleParticles();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	Particle* GenerateParticle(entity_type type, iPoint position);


private:
	
	SDL_Texture *graphics_hit_effect = nullptr;
	SDL_Texture *graphics_boomerang = nullptr;
	
		
};

#endif // __MODULEPARTICLES_H__