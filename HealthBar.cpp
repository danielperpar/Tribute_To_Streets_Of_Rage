#include "HealthBar.h"
#include "Animation.h"
#include "ModuleWindow.h"

HealthBar::HealthBar(
	int starting_width,
	SDL_Texture *texture,
	Animation *curr_anim,
	const char *name,
	entity_type type,
	iPoint position,
	int depth) : starting_width(starting_width), Entity(texture, curr_anim, name, type, position, depth) {}

HealthBar::~HealthBar() {}

void HealthBar::ScaleHPBar(int health, int max_health)
{
	if (health > 0)
	{
		float scale_factor = (float)health / max_health;
		int new_width = (int)(starting_width * scale_factor);
		curr_anim->GetCurrentFrame().w = new_width;	
	}
	else
		curr_anim->GetCurrentFrame().w = 0;
}