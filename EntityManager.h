#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Entity.h"

struct SDL_Texture;
class EntityManager {
public:
	static Entity* CreateEntity(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth);
	static void DestroyEntity(Entity *entity);
};



#endif // !__ENTITYMANAGER_H__

