#pragma once
#include "Globals.h"
//#include "ModuleSceneRace.h"
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

	vector<pair<atrezzo, int>> atrezzos;

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

	void DrawObject(atrezzo object, SDL_Texture* tex, int posX)
	{
		bool behindStuff;
		float scaling = 2 * W / SEGMENT_LENGTH;
		float destY = Y - object.sprite.h * scaling;
		float destX = X + (W * posX);
		int destH = object.sprite.h * (int)scaling;
		float destW;
		
		// Apply clipping only if needed (if the sprite must be cut)
		if (destY + destH > clip) {
			behindStuff = true;
			float clipH = destY + destH - clip;
			object.sprite.h = (int)(object.sprite.h - object.sprite.h * clipH / destH);
		}
		else {
			behindStuff = false;
		}

		if (object.hitBoxWidth != 0) {
			destW = object.hitBoxWidth * scaling;
		}
		else {
			destW = object.sprite.w * scaling;
		}
		
		SDL_Rect hitBox = { (int)destX + object.hitBoxXOffset * scaling, (int)destY + object.sprite.h * scaling - 10,  (int) destW, 10 };
		SDL_RenderFillRect(App->renderer->renderer, &hitBox);		//DEBUG

		App->renderer->Blit(tex, (int)destX, (int)destY, &object.sprite, 0.f, false, false, scaling, scaling);

		if (!behindStuff) {
			App->player->DetectCollision(hitBox, ModulePlayer::collision_types::OBSTACLE);
		}
	}

};