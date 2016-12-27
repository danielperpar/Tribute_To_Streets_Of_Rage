#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include <list>
#include "Entity.h"
#include "Point.h"



struct SDL_Texture;
class Player : public Entity{

public:
	Player(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth);


public:
	
	bool m_dead;
	int m_life;
	Animation player_idle_right;
	Animation player_walk_right;
	Animation player_jump_right;
	Animation player_punch_combo_right;
	Animation player_back_punch_right;
	Animation player_air_kick_right;
	Animation player_grab_kick_head_combo_right;
	Animation player_grab_air_combo_right;

	Animation player_idle_left;
	Animation player_walk_left;
	Animation player_jump_left;
	Animation player_punch_combo_left;
	Animation player_back_punch_left;
	Animation player_air_kick_left;
	Animation player_grab_kick_head_combo_left;
	Animation player_grab_air_combo_left;

	Animation *current_animation;
	
private:
	std::list<int*> animation_list;

};

#endif // !__PLAYER_H__

