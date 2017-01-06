#ifndef __ModuleAI_H__
#define __ModuleAI__

#include "Module.h"

class ModuleAI : public Module {


public:
	ModuleAI();
	~ModuleAI();

	bool Init();
	update_status Update();

	
private:
	Uint32 time = 0;
	Uint32 update_time = 0;
	Uint32 dt = 10;
	bool do_logic = true;
	
	bool *m_walk_left;
	bool *m_walk_right;
	bool *m_walk_up;
	bool *m_walk_down;
	bool *m_hit;
	bool *m_throw_boomerang;


	
};



#endif // __ModuleAI__
