#include "../3rdparty/parson.h"
#include "JSONDataLoader.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include <string>
#include "../3rdparty/SDL/include/SDL.h"

void JSONDataLoader::LoadAnimRect(const char *json_file, const char *sprite_owner, std::list<int*> &rect_sprites_list, Animation& animation) {
	
	JSON_Value *root_value = nullptr;
	JSON_Array *sprites = nullptr;
	JSON_Object *json_object = nullptr;
	JSON_Object *single_sprite = nullptr;
	JSON_Array *coordinates = nullptr;
	JSON_Object *point = nullptr;
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	std::list<JSON_Object*> sprites_list;

	size_t sprites_count = 0;

	root_value = json_parse_file(json_file);
	json_object = json_value_get_object(root_value);
	sprites = json_object_get_array(json_object, sprite_owner);
	sprites_count = json_array_get_count(sprites);

	for (size_t i = 0; i < sprites_count; i++)
	{
		single_sprite = json_array_get_object(sprites, i);
		sprites_list.push_back(single_sprite);
	}

	for (std::list<JSON_Object*>::iterator it = sprites_list.begin(); it != sprites_list.end(); it++)
	{
		coordinates = json_object_get_array(*it, "sprite");

		point = json_array_get_object(coordinates, 0);
		x = (int)json_object_dotget_number(point, "x");

		point = json_array_get_object(coordinates, 1);
		y = (int)json_object_dotget_number(point, "y");

		point = json_array_get_object(coordinates, 2);
		w = (int)json_object_dotget_number(point, "w");

		point = json_array_get_object(coordinates, 3);
		h = (int)json_object_dotget_number(point, "h");

		int *points_array = new int[4]{ x, y, w, h };
		rect_sprites_list.push_back(points_array);

	}

	/* cleanup code */
	json_value_free(root_value);
	

	for (std::list<int*>::iterator it = rect_sprites_list.begin(); it != rect_sprites_list.end(); it++)
	{
		int x = **it;
		int y = *(*it + 1);
		int w = *(*it + 2);
		int h = *(*it + 3);
		animation.frames.push_back({ x, y, w, h });
	}
		
}

bool JSONDataLoader::LoadColliderRect(const char *json_file, const char *entity_name, const char *collider_name, SDL_Rect &rect)
{

	JSON_Value *root_value = nullptr;
	JSON_Object *root_object = nullptr;
	JSON_Array *coordinates = nullptr;
	JSON_Object *point = nullptr;

	root_value = json_parse_file(json_file);
	if (root_value == NULL)
		return false;

	root_object = json_value_get_object(root_value);
	std::string identifier = std::string(entity_name) + "." + std::string(collider_name);

	coordinates = json_object_dotget_array(root_object, identifier.c_str());

	point = json_array_get_object(coordinates, 0);
	rect.x = (int)json_object_dotget_number(point, "x");

	point = json_array_get_object(coordinates, 1);
	rect.y = (int)json_object_dotget_number(point, "y");

	point = json_array_get_object(coordinates, 2);
	rect.w = (int)json_object_dotget_number(point, "w");

	point = json_array_get_object(coordinates, 3);
	rect.h = (int)json_object_dotget_number(point, "h");

	json_value_free(root_value);
	return true;
}

int JSONDataLoader::GetInt(const char *json_file, const char *entity_name, const char *property_name)
{
	JSON_Value *root_value = nullptr;
	JSON_Object *root_object = nullptr;

	root_value = json_parse_file(json_file);
	if (root_value == NULL)
		return false;

	root_object = json_value_get_object(root_value);
	std::string identifier = std::string(entity_name) + "." + std::string(property_name);
	int ret = (int)json_object_dotget_number(root_object, identifier.c_str());

	json_value_free(root_value);
	return ret;
}

float JSONDataLoader::GetFloat(const char *json_file, const char *entity_name, const char *property_name)
{
	JSON_Value *root_value = nullptr;
	JSON_Object *root_object = nullptr;

	root_value = json_parse_file(json_file);
	if (root_value == NULL)
		return false;

	root_object = json_value_get_object(root_value);
	std::string identifier = std::string(entity_name) + "." + std::string(property_name);
	float ret = (float)json_object_dotget_number(root_object, identifier.c_str());

	json_value_free(root_value);
	return ret;
}

bool JSONDataLoader::GetPoint(const char *json_file, const char *entity_name, const char *property_name, iPoint &ipoint)
{
	JSON_Value *root_value = nullptr;
	JSON_Object *root_object = nullptr;
	JSON_Array *coordinates = nullptr;
	JSON_Object *point = nullptr;

	root_value = json_parse_file(json_file);
	if (root_value == NULL)
		return false;

	root_object = json_value_get_object(root_value);
	std::string identifier = std::string(entity_name) + "." + std::string(property_name);

	coordinates = json_object_dotget_array(root_object, identifier.c_str());

	point = json_array_get_object(coordinates, 0);
	ipoint.x = (int)json_object_dotget_number(point, "x");

	point = json_array_get_object(coordinates, 1);
	ipoint.y = (int)json_object_dotget_number(point, "y");

	json_value_free(root_value);
	return true;
}