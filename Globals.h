#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "MemLeaks.h"
#include "SDL/include/SDL_rect.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum collider_type
{
	COMMON_ENEMY_HIT,
	COMMON_ENEMY_GRAB,
	BOSS_ENEMY_HIT,
	BOSS_ENEMY_GRAB,
	WEAPON,
	FOOD,
	PLAYER,
	BOSS_BOOMERANG,
	BOSS_BOOMERANG_AREA,
	DESTROYABLE_ITEM,
	
};

// Useful typedefs ---------
typedef unsigned int uint;

// Deletes a buffer
#define RELEASE( x ) \
    {									  \
       if( x != nullptr )   \
       {						      \
         delete x;                  \
	     x = nullptr;             \
       }                      \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{                              \
       if( x != nullptr )              \
       {                            \
           delete[] x;                \
	       x = nullptr;                    \
		 }                            \
                              \
	 }

// Configuration -----------
#define CAMERA_STARTING_POS_X -771
#define SCREEN_SIZE 3
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 224
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Tribute to Streets of Rage"

#endif //__GLOBALS_H__