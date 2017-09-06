#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "MemLeaks.h"
#include "../3rdparty/SDL/include/SDL_rect.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

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


enum audio_fx
{
	PLAYER_JUMP,
	PLAYER_LAND,
	PLAYER_ATTACK_MISS,
	PLAYER_ATTACK_HIT,
	PLAYER_ATTACK_HIT_HARD,
	PLAYER_VOICE_AXEL,
	PLAYER_DEAD,
	ENEMY_ATTACK,
	ENEMY_DEAD,
	HEALTH_ITEM,
	GO_ARROW,
	GROUND_HIT
};




#endif //__GLOBALS_H__