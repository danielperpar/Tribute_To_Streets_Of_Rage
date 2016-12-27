#include "Player.h"
#include "JSONDataLoader.h"
#include "Utilities.h"

Player::Player(SDL_Texture *texture, const char *name, entity_type type, iPoint position, int depth) : Entity(texture, name, type, position, depth), m_dead(false), m_life(100) {
	
	JSONDataLoader::Load("assets/json/sprites_data.json", "playerIdleRight", animation_list, player_idle_right);
	player_idle_right.loop = false;
	player_idle_right.speed = 0.05f;
	Utilities::free_list(animation_list);

}