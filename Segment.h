#pragma once

#include "Globals.h"
//#include "ModuleSceneRace.h"
#include "ModuleEuropeRace.h"
#include "SDL\include\SDL.h"
//#include "Rival.h"
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

	vector<pair<atrezzo, float>> atrezzos;

	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;
	int roadWidth = ROAD_WIDTH;
	float camD = (float)CAMERA_DEPTH; //camera depth

	Segment() {
		curve = x = y = z = 0; 
		X = 0; 
		Y = SCREEN_HEIGHT; 
		W = 0;
		spriteX = -1; 
		clip = 0; 
		scale = 0;
	}

	//from world to scene
	void project(int camX, int camY, int camZ)
	{
		scale = camD / (z - camZ);
		X = (float)((1 + scale*(x - camX)) * width / 2);
		Y = (float)((1 - scale*(y - camY)) * height *0.55);
		W = (float)(scale * roadWidth * width / 2);
	}

	void DrawObject(atrezzo object, SDL_Texture* tex, float posX)
	{
		bool behindStuff;
		float scaling;
		if (object.small) {
			scaling = W / SEGMENT_LENGTH *  0.65f;
		}
		else {
			scaling = W / SEGMENT_LENGTH * 2;
		}
		float destY = Y - object.sprite.h * scaling;
		float destX = X + (W * posX);
		int destH = (int)(object.sprite.h * scaling);
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
		
		SDL_Rect hitBox = { static_cast<int>(destX + object.hitBoxXOffset * scaling), 
			static_cast<int>(destY + object.sprite.h * scaling - 10),
			static_cast<int>(destW),
			10 };
		
		App->renderer->Blit(tex, (int)destX, (int)destY, &object.sprite, 0.f, false, false, scaling, scaling);

		if (scaling >= 1) {
			App->player->DetectCollision(hitBox, ModulePlayer::collision_types::OBSTACLE);
		}
	}

	void DrawRival(rival* racer, SDL_Texture* tex)
	{
		bool behindStuff;
		float virtualW = W;
		if (virtualW > SCREEN_WIDTH / 2) {
			virtualW = SCREEN_WIDTH / 2;
		}
		float scaling = virtualW / SEGMENT_LENGTH * 0.65f;

		float destY = Y - 72/*racer->currentAnimation->GetCurrentFrame().h*/ * scaling;
		float destX = X + (W * racer->x);
		int destH = (int)(/*racer->currentAnimation->GetCurrentFrame().h*/72 * scaling);
		float destW;


		// Apply clipping only if needed (if the sprite must be cut)
		if (destY + destH > clip) {
			behindStuff = true;
			float clipH = destY + destH - clip;
			//object.sprite.h = (int)(object.sprite.h - object.sprite.h * clipH / destH);
			//racer->currentAnimation->GetCurrentFrame().h = (int)(/*racer->currentAnimation->GetCurrentFrame().h*/72 - 72/*racer->currentAnimation->GetCurrentFrame().h*/ * clipH / destH);
		}
		else {
			behindStuff = false;
		}

		if (racer->hitBoxWidth != 0) {
			destW = racer->hitBoxWidth * scaling;
		}
		else {
			destW = racer->currentAnimation->GetCurrentFrame().w * scaling;
		}
		/*SDL_Rect drawSprite = { racer->currentAnimation->GetCurrentFrame().x,  }*/

		SDL_Rect hitBox = { static_cast<int>(destX + racer->hitBoxXOffset * scaling),
			static_cast<int>(destY + racer->currentAnimation->GetCurrentFrame().h * scaling - 10),
			static_cast<int>(destW),
			10 };


		
		if(clip > destY)
			App->renderer->Blit(tex, (int)destX, (int)destY, &racer->currentAnimation->GetCurrentFrame(), 0.f, false, false, scaling, scaling);

		if (scaling >= 0.65) {
			App->player->DetectCollision(hitBox, ModulePlayer::collision_types::RIVAL, destX + racer->currentAnimation->GetCurrentFrame().w * scaling);
		}
	}
	
};