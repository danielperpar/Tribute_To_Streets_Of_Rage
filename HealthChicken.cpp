#include "HealthChicken.h"
#include "JSONDataLoader.h"
#include "Utilities.h"

HealthChicken::HealthChicken(SDL_Texture *texture,
	Animation *curr_anim,
	const char *name,
	entity_type type,
	iPoint position,
	int depth) : Entity(texture, curr_anim, name, type, position, depth) 
{
	LoadSprite();
	LoadCollider();
}

HealthChicken::HealthChicken(const HealthChicken &chicken) : Entity(chicken.texture, chicken.curr_anim, chicken.name, chicken.type, chicken.position, chicken.depth)
{
	chicken_collider_rect = chicken.chicken_collider_rect;
	chicken_animation = chicken.chicken_animation;
}

HealthChicken::~HealthChicken() {}

void HealthChicken::LoadSprite()
{
	JSONDataLoader::LoadAnimRect("assets/json/sprites_data.json", "healthChicken", animation_list, chicken_animation);
	chicken_animation.loop = true;
	chicken_animation.speed = 1.0f;
	Utilities::free_list(animation_list);
}

void HealthChicken::LoadCollider()
{
	JSONDataLoader::LoadColliderRect("assets/json/config.json", "healthChicken", "collider", chicken_collider_rect);
}