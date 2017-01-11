#include "Entity.h"
Entity::Entity() {}
Entity::Entity(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : m_texture(texture), m_name(name), m_type(type), m_position(position), m_depth(depth) {
	

}
Entity::~Entity() {}