#ifndef __SCENARIO_ELEMENT_H__
#define __SCENARIO_ELEMENT_H__

#include "Entity.h"
#include "Point.h"

class Animation;
struct SDL_Texture;
class ScenarioElement : public Entity
{
public:
	
	ScenarioElement(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int depth);
	~ScenarioElement();

};


#endif
