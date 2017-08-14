#include "Enemy.h"
#include "JSONDataLoader.h"

Enemy::Enemy(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, curr_anim, name, type, position, depth)
{	
	LoadColliders(name);
}

Enemy::Enemy(const Enemy &enemy) : Entity(enemy.texture, enemy.curr_anim, enemy.name, enemy.type, enemy.position, enemy.depth)
{
	body_rect = enemy.body_rect;
	hit_rect = enemy.hit_rect;
	body_collider_offset_right = enemy.body_collider_offset_right;
	hit_collider_offset_right = enemy.hit_collider_offset_right;
	body_collider_offset_left = enemy.body_collider_offset_left;
	hit_collider_offset_left = enemy.hit_collider_offset_left;
}

Enemy::~Enemy() {}

void Enemy::LoadColliders(const char *name)
{
	JSONDataLoader::LoadColliderRect("assets/json/config.json", name, "body_collider", body_rect);
	JSONDataLoader::LoadColliderRect("assets/json/config.json", name, "hit_collider", hit_rect);
	body_collider_offset_right = JSONDataLoader::GetNumber("assets/json/config.json", name, "body_collider_offset_right");
	hit_collider_offset_right = JSONDataLoader::GetNumber("assets/json/config.json", name, "hit_collider_offset_right");
	body_collider_offset_left = JSONDataLoader::GetNumber("assets/json/config.json", name, "body_collider_offset_left");
	hit_collider_offset_left = JSONDataLoader::GetNumber("assets/json/config.json", name, "hit_collider_offset_left");
}


