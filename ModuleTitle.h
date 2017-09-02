#ifndef __MODULE_TITLE_H__
#define __MODULE_TITLE_H__

#include "Module.h"
#include "GUI.h"
#include <list>
#include "Animation.h"

struct SDL_Texture;
class ModuleTitle : public Module
{
public:
	ModuleTitle(bool active = true);
	~ModuleTitle();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

private:
	std::list<int*> animation_list;

	GUI *title_screen = nullptr;
	GUI *press_enter = nullptr;

	void LoadSceneAssets();

	SDL_Texture *tx_title_screen = nullptr;

	Animation anim_title_screen;
	Animation anim_press_enter;
};




#endif
