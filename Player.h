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
	
	bool m_dead = false;
	int m_life = 100;
	bool m_face_right = true;
	float m_speed = 1.0f;
	bool m_jumping = false;
	bool m_attacking = false;
	bool m_jump_up = true;
	iPoint m_jump_start_pos;
	int m_jump_speed = 1;
	int m_max_jump_height = 36;
	
	bool m_timer_activated = false;
	float m_timer_count = 0.0f;
	float m_timer_speed = 1.0f;
	float m_timer_now = -1.0f;
	bool m_refresh_now1 = true;
	bool m_refresh_now2 = true;

	bool m_continue_animation1 = false;
	bool m_continue_animation2 = false;

	Animation m_player_idle_right;
	Animation m_player_walk_right;
	Animation m_player_jump_right1;
	Animation m_player_jump_right2;
	Animation m_player_jump_left1;
	Animation m_player_jump_left2;
	Animation m_player_punch_combo_right;
	Animation m_player_back_punch_right;
	Animation m_player_air_kick_right;
	Animation m_player_grab_kick_head_combo_right;
	Animation m_player_grab_air_combo_right;

	Animation m_player_idle_left;
	Animation m_player_walk_left;
	Animation m_player_jump_left;
	Animation m_player_punch_combo_left;
	Animation m_player_back_punch_left;
	Animation m_player_air_kick_left;
	Animation m_player_grab_kick_head_combo_left;
	Animation m_player_grab_air_combo_left;

	Animation *m_current_animation;
	
private:
	std::list<int*> m_animation_list;

};

#endif // !__PLAYER_H__

