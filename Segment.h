#pragma once
#include "Globals.h"
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

	int width = WIDTH;
	int height = HEIGHT;
	int roadW = ROADW;
	int segL = SEGL; //segmentLenght
	float camD = (float)CAMD; //camera depth

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
		W = (float)(scale * roadW * width / 2);
	}

	void DrawObject(SDL_Rect sprite, SDL_Texture* tex)
	{
		int w = sprite.w;
		int h = sprite.h;
		float destX = X + scale * spriteX * width / 2;
		float destY = Y + 4;
		float destW = w * W / 266;
		float destH = h * W / 266;

		destX += destW * spriteX; //offsetX
		destY += destH * (-1);    //offsetY

		float clipH = destY + destH - clip;
		if (clipH<0) clipH = 0;

		X += (W * spriteX);
		if (clipH >= destH) return;

		sprite.h = h - h*clipH / destH;
		App->renderer->Blit(tex, X, destY, &sprite, 0.f, false, false, sprite.w*(destW / w), sprite.h*(destH / h));
	}

};