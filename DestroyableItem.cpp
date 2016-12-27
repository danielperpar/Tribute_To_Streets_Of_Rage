#include "DestroyableItem.h"

DestroyableItem::DestroyableItem(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, name, type, position, depth),  m_destroyed(false) {}