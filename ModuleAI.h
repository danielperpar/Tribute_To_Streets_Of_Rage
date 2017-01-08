#ifndef __ModuleAI_H__
#define __ModuleAI__

#include "Module.h"

class ModuleEnemies;
class Player;
class Enemy;
class ModuleAI : public Module {


public:
	ModuleAI(bool active = true);
	~ModuleAI();

	bool Start();
	update_status Update();
	
private:
	Uint32 m_time = 0;
	Uint32 m_update_time = 0;
	Uint32 m_dt = 10;
	bool m_do_logic = true;	
	
};



#endif // __ModuleAI__
