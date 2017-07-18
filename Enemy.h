#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL.h"

class Animation;
class Enemy : public Entity {

public:
	Enemy(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);

	~Enemy();

	//---------------------------------------- COLLIDERS -----------------------------------------------
	Collider *body_collider = nullptr;
	Collider *hit_collider = nullptr;
	SDL_Rect body_rect;
	SDL_Rect hit_rect;

	//---------------------------------------- X OFFSETS ------------------------
	//int ref_x = 70;
	int body_collider_offset_right = 0;
	int hit_collider_offset_right = 0;
	int body_collider_offset_left = 0;
	int hit_collider_offset_left = 0;

	// ---------------------------------------- COLLISION ----------------------------------------
	bool right_collision = false;
	bool left_collision = false;
	bool up_collision = false;
	bool down_collision = false;

	bool left_blocked = false;
	bool right_blocked = false;
	bool up_blocked = false;
	bool down_blocked = false;

	CollisionInfo hit_collider_status = CollisionInfo(nullptr, contact_direction::LEFT, contact_direction::DOWN);
	virtual void OnCollision(const CollisionInfo &col_info_this, const CollisionInfo &col_info_other) = 0;
	virtual void OnCollisionExit(const CollisionInfo &col_info_other) = 0;


private:
	void LoadColliders(const char *name);

};

#endif // !__ENEMY_H__


