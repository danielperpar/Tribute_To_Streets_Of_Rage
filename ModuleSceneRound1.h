#ifndef __MODULESCENEROUND1_H__
#define __MODULESCENEROUND1_H__

#include "Module.h"
#include <list>
#include <vector>
#include "Animation.h"
#include "HealthChicken.h"
#include "Point.h"

struct SDL_Texture;
class ScenarioElement;
class Entity;
class GUI;
class Player;
class Garcia;
class HealthBar;
class ModuleSceneRound1 : public Module
{
public:
	ModuleSceneRound1(bool active = true);
	virtual ~ModuleSceneRound1();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	void LoadSceneAssets();
	void GenerateChicken(iPoint position, int depth);
	
	GUI *gui = nullptr;
	GUI *go_sign = nullptr;
	HealthBar *player_HP = nullptr;
	HealthBar *boss_HP = nullptr;
	GUI *boss_white_bar = nullptr;
	GUI *boss_title = nullptr;

	HealthChicken *health_chicken_prototype = nullptr;

	Entity *foreground = nullptr;

	//-------------------- SCENE BOUNDARIES -------------------
	int upper_limit = 90;
	int lower_limit = 160;
	int right_limit = 3840;

	//-------------------- SCENE STOP POINTS -----------------
	int first_stop_x = 1537;
	int second_stop_x = 2306;
	int third_stop_x = 3075;

	bool first_stop_reached = false;
	bool second_stop_reached = false;
	bool third_stop_reached = false;
	bool end_of_scene_reached = false;

	bool first_area_clear = false;
	bool second_area_clear = false;
	bool third_area_clear = false;
	bool end_of_scene_clear = false;

	bool show_go = false;
	bool show_boss_health_bar = false;

	std::list<Entity*> dynamic_entities;
	bool entity_erased = false;

private:
	std::list<int*> animation_list;
	std::vector<Entity*> scenario_entities;
	
	int go_sign_show_frames = 180;
	int go_sign_show_counter = 0;

	SDL_Texture *tx_background = nullptr;
	SDL_Texture *tx_foreground = nullptr;
	SDL_Texture *tx_neons = nullptr;
	SDL_Texture *tx_gui = nullptr;
	SDL_Texture *tx_garcia = nullptr;
	SDL_Texture *tx_ground_items = nullptr;

	Animation neon_pinepot;
	Animation neon_breakfast_dinner;
	Animation neon_ldevo;
	Animation neon_ranch_shop;
	Animation neon_abc_shop;
	Animation neon_cafe_restaurant;
	Animation go_sign_blink;
	Animation go_sign_transparent;

	Animation gui_background;
	Animation anim_player_HP;
	Animation anim_boss_HP;
	Animation anim_boss_white_bar;
	Animation anim_boss_title;
};

#endif // __MODULESCENEROUND1_H__