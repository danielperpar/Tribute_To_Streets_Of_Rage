#include "EntityManager.h"
#include "DestroyableItem.h"
#include "Enemy.h"
#include "Food.h"
#include "Weapon.h"
#include "Player.h"
#include "ModuleParticles.h"
#include "Application.h"


Entity* EntityManager::CreateEntity(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) {
	Entity *ret = nullptr;

	switch (type)
	{
	case entity_type::DESTROYABLE_ITEM:
		ret = new DestroyableItem(texture, name, type, position, depth);
		break;
	case entity_type::ENEMY:
		ret = new Enemy(texture, name, type, position, depth);
		break;
	case entity_type::FOOD:
		ret = new Food(texture, name, type, position, depth);
		break;
	case entity_type::PLAYER:
		ret = new Player(texture, name, type, position, depth);
		break;
	case entity_type::WEAPON:
		ret = new Weapon(texture, name, type, position, depth);
		break;
	}

	if (ret != nullptr)
		App->entities.push_back(ret);

	return ret;
}

void EntityManager::DestroyEntity(Entity *entity)
{
	if (entity != nullptr)
	{
		for (std::list<Entity*>::iterator it = App->entities.begin(); it != App->entities.end();)
		{
			if (entity == *it)
			{
				delete entity;
				it = App->entities.erase(it);
			}
			else {
				++it;
			}
			
		}
	}
}