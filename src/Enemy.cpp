#include "Enemy.h"
#include "JSONDataLoader.h"

Enemy::Enemy(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, curr_anim, name, type, position, depth)
{	
	LoadColliders(name);
	LoadStats(name);
	LoadCommon();
}

Enemy::Enemy(const Enemy &enemy) : Entity(enemy.texture, enemy.curr_anim, enemy.name, enemy.type, enemy.position, enemy.depth)
{
	max_life = enemy.max_life;
	life = max_life;
	speed = enemy.speed;
	speed_vect = enemy.speed_vect;
	body_rect = enemy.body_rect;
	hit_rect = enemy.hit_rect;
	body_collider_offset_right = enemy.body_collider_offset_right;
	hit_collider_offset_right = enemy.hit_collider_offset_right;
	body_collider_offset_left = enemy.body_collider_offset_left;
	hit_collider_offset_left = enemy.hit_collider_offset_left;
	depth_margin = enemy.depth_margin;
}

Enemy::~Enemy() {}

void Enemy::LoadColliders(const char *name)
{
	JSONDataLoader::LoadColliderRect("assets/json/config.json", name, "body_collider", body_rect);
	JSONDataLoader::LoadColliderRect("assets/json/config.json", name, "hit_collider", hit_rect);
	body_collider_offset_right = JSONDataLoader::GetInt("assets/json/config.json", name, "body_collider_offset_right");
	hit_collider_offset_right = JSONDataLoader::GetInt("assets/json/config.json", name, "hit_collider_offset_right");
	body_collider_offset_left = JSONDataLoader::GetInt("assets/json/config.json", name, "body_collider_offset_left");
	hit_collider_offset_left = JSONDataLoader::GetInt("assets/json/config.json", name, "hit_collider_offset_left");
}

void Enemy::LoadStats(const char *name)
{
	max_life = JSONDataLoader::GetInt("assets/json/config.json", name, "max_life");
	speed = JSONDataLoader::GetInt("assets/json/config.json", name, "speed");
	speed_vect.x = speed;
	speed_vect.y = speed;
}

void Enemy::LoadCommon()
{
	depth_margin = JSONDataLoader::GetInt("assets/json/config.json", "enemy", "depth_margin");
}

