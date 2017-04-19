#ifndef __JSONDATALOADER_H__
#define __JASONDATALOADER_H__

#include <list>

class Animation;
struct SDL_Rect;
class JSONDataLoader {

public:
	static void LoadAnimRect(const char *json_file, const char *sprite_owner, std::list<int*> &rect_sprites_list, Animation& animation);
	static bool LoadColliderRect(const char *json_file, const char *entity_name, const char *collider_name, SDL_Rect &rect);
	static int GetNumber(const char *json_file, const char *entity_name, const char *property_name);
};
#endif //__JASONDATALOADER_H__

