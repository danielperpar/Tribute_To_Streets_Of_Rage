#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleCollision.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"

class Garcia;
struct SDL_Texture;


class ModuleEnemies : public Module
{
public:
	ModuleEnemies(bool active = true);
	~ModuleEnemies();

	bool Start();
	update_status Update();
	bool CleanUp();
	void UpdateColliderPosition(Enemy *enemy);

	SDL_Texture *graphics;

	Collider* player_collider;
	Player *m_player = nullptr;

	//Enemies
	Garcia *m_garcia1 = nullptr;
	

private:	
	Uint32 m_time = 0;
	Uint32 m_update_time = 0;
	Uint32 m_dt = 10;
	bool m_do_logic = true;
	size_t m_time_to_next_attack = 200;
};

#endif