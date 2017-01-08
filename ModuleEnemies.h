#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleCollision.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"

struct SDL_Texture;


class ModuleEnemies : public Module
{
public:
	ModuleEnemies(bool active = true);
	~ModuleEnemies();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* collider1, Collider* collider2);

	SDL_Texture *graphics;
	Enemy *m_enemy = nullptr; 
	Collider* playerCollider;
	Player *m_player = nullptr;
	Enemy *m_boomerang = nullptr;
	
	
private:	
	Uint32 m_time = 0;
	Uint32 m_update_time = 0;
	Uint32 m_dt = 10;
	bool m_do_logic = true;



};

#endif