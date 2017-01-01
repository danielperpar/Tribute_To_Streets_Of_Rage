#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include <list>
#include "Entity.h"
#include "Point.h"


enum class state
{
	START,
	IDLE,
	IDLE_S_PRESSED,
	WALKING,
	JUMPING,
	PUNCHING,
	BACK_PUNCHING
};




struct SDL_Texture;
class Player : public Entity{

public:
	Player(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth);

public:
	
	bool m_dead = false;
	int m_life = 100;
	bool m_face_right = true;
	float m_speed = 1.0f;

	bool m_jump_up = true;
	iPoint m_jump_start_pos;
	float m_jump_speed = 1.5f;
	int m_max_jump_height = 36;
	
	float m_timer_count = 0.0f;
	float m_timer_speed = 1.0f;

	bool m_continue_combo = false;
	bool m_allow_punch = true;
	bool m_allow_back_punch = true;
	bool m_restart_animation = true;
	
	bool m_jumping = false;
	bool m_punching = false;
	bool m_back_punching = false;
	bool m_idle = false;
	bool m_walking = false;
	state m_state = state::START;

	Animation m_idle_right1;
	Animation m_idle_right2;
	Animation m_idle_right3;
	Animation m_idle_left1;
	Animation m_idle_left2;
	Animation m_idle_left3;
	size_t m_idle1_duration = 150;
	size_t m_idle2_duration = 25;
	size_t m_idle3_duration = 25;

	Animation m_walk_right;
	Animation m_walk_left;

	Animation m_jump_right1;
	Animation m_jump_right2;
	Animation m_jump_left1;
	Animation m_jump_left2;
	size_t m_jump1_duration = 10;
	size_t m_jump2_duration = 10;

	Animation m_air_kick_right;
	Animation m_air_kick_left;

	Animation m_punch_combo_right1;
	Animation m_punch_combo_right2;
	Animation m_punch_combo_right3;
	Animation m_punch_combo_left1;
	Animation m_punch_combo_left2;
	Animation m_punch_combo_left3;

	size_t m_punch_combo1_duration = 10;
	size_t m_punch_combo2_duration = 10;
	size_t m_punch_combo3_duration = 10;

	Animation m_back_punch_right1;
	Animation m_back_punch_right2;
	
	Animation m_back_punch_left1;
	Animation m_back_punch_left2;

	size_t m_back_punch1_duration = 10;
	size_t m_back_punch2_duration = 10;


	Animation m_grab_kick_head_combo_right;
	Animation m_grab_kick_head_combo_left;
	Animation m_grab_air_combo_right;
	Animation m_grab_air_combo_left;

	Animation *m_current_animation;

	void AdvanceAnimation(size_t initial_sprite_duration,  Animation *next_anim_sprite, bool restart_animation);
	
private:
	std::list<int*> m_animation_list;

};

#endif // !__PLAYER_H__

