#ifndef __JSONDATALOADER_H__
#define __JASONDATALOADER_H__

#include <list>

class Animation;
class JSONDataLoader {

public:
	static void Load(const char *json_file, const char *sprite_owner, std::list<int*> &rect_sprites_list, Animation& animation);

};
#endif //__JASONDATALOADER_H__

