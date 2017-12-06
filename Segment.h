#pragma once
#include "Globals.h"
#include "SDL\include\SDL.h"
#include <vector>

using namespace std;

class Segment

{
public:
	float x, y, z; //3d center of line
	float X, Y, W; //screen coords
	float scale;
	float curve;

	float spriteX;
	float clip;
	float cover;

	vector<pair<SDL_Rect, int>> atrezzos;

	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;
	int roadWidth = ROAD_WIDTH;
	float camD = (float)CAMERA_DEPTH; //camera depth

	Segment() {
		curve = x = y = z = 0; X = 0; Y = SCREEN_HEIGHT; W = 0;
		spriteX = -1; clip = 0; scale = 0;
	}

	//from world to scene
	void project(int camX, int camY, int camZ)
	{
		scale = camD / (z - camZ);
		X = (float)((1 + scale*(x - camX)) * width / 2);
		Y = (float)((1 - scale*(y - camY)) * height *0.55);
		W = (float)(scale * roadWidth * width / 2);
	}

	void DrawObject(SDL_Rect sprite, SDL_Texture* tex, int posX)
	{
		float scaling = 2 * W / SEGMENT_LENGTH;
		float destY = Y - sprite.h * scaling;
		float destX = X + (W * posX);
		int destH = sprite.h * scaling;
		
		// Apply clipping only if needed (if the sprite must be cut)
		if (destY + destH > clip) {
			float clipH = destY + destH - clip;
			sprite.h = (int)(sprite.h - sprite.h * clipH / destH);
		}

		App->renderer->Blit(tex, (int)destX, (int)destY, &sprite, 0.f, false, false, scaling, scaling);
	}

};