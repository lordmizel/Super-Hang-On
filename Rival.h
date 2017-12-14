#ifndef __RIVAL_H__
#define __RIVAL_H__

#include "Globals.h"
#include "SDL\include\SDL.h"
#include "Segment.h"
#include <vector>

class Segment;

class Rival {
public:

	Rival() {}
	~Rival() {}

	SDL_Rect sprite;
	float z;
	int speed = 50;
	float x = 0;
	int hitBoxXOffset = 0;
	int hitBoxWidth = 0;

	//Segment containedIn;

	void Advance() {
		z += speed;
	}


};

#endif