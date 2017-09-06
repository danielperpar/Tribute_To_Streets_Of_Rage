#ifndef __GUI_H__
#define __GUI_H__

#include "Entity.h"

class GUI : public Entity
{
public:
	GUI(SDL_Texture *texture, Animation *curr_anim, const char *name, entity_type type, iPoint position, int m_depth);
	virtual ~GUI();


};
#endif
