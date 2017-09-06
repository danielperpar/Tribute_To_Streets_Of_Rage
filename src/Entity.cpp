#include "Entity.h"

Entity::Entity() {}

Entity::Entity(SDL_Texture *texture,
	Animation *curr_anim,
	const char *name, 
	entity_type type, 
	iPoint position, 
	int depth) : texture(texture), curr_anim(curr_anim), name(name), type(type), position(position), depth(depth) {}

Entity::~Entity() {}
void Entity::UpdateFSM() {}