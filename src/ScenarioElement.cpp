#include "ScenarioElement.h"
#include "Globals.h"

ScenarioElement::ScenarioElement(
	SDL_Texture *texture,
	Animation *curr_anim,
	const char *name,
	entity_type type,
	iPoint position,
	int depth) : Entity(texture, curr_anim, name, type, position, depth) {}

ScenarioElement::~ScenarioElement() {}
