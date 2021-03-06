#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <ctime>
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

enum game_state
{
	BEFORE_RACE,
	RACING,
	CRASHED,
	AFTER_RACE,
	GAME_OVER
};

struct Color {
	int r;
	int g;
	int b;
	int a;
	Color() { r = 255; g = 255; b = 255; a = 255; }
	Color(int red, int green, int blue, int alpha) {
		r = red, g = green, b = blue, a = alpha;
	}
};

#define Green Color(0,255,0,255)

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
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Super Hang-On"

#define ROAD_WIDTH 2000
#define SEGMENT_LENGTH 100
#define CAMERA_DEPTH 0.5

extern time_t g_timer;
#endif //__GLOBALS_H__