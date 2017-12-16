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

	vector<pair<atrezzo, int>> atrezzos;

	/*vector<pair<Rival, int>> rivals;*/

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
		//SDL_RenderFillRect(App->renderer->renderer, &hitBox);		//DEBUG

		App->renderer->Blit(tex, (int)destX, (int)destY, &object.sprite, 0.f, false, false, scaling, scaling);

		if (scaling >= 1) {
			App->player->DetectCollision(hitBox, ModulePlayer::collision_types::OBSTACLE);
		}
	}

	void DrawRival(rival* racer, SDL_Texture* tex, float posX)
	{
		bool behindStuff;

		float scaling = W / SEGMENT_LENGTH;
		if (scaling >= 1) scaling = 1;

		float destY = Y - racer->currentAnimation->GetCurrentFrame().h * scaling;
		float destX = X + (W * racer->x);
		int destH = racer->currentAnimation->GetCurrentFrame().h * (int)scaling;
		float destW;

		// Apply clipping only if needed (if the sprite must be cut)
		if (destY + destH > clip) {
			behindStuff = true;
			float clipH = destY + destH - clip;
			//racer->currentAnimation->GetCurrentFrame().h = (int)(racer->currentAnimation->GetCurrentFrame().h - racer->currentAnimation->GetCurrentFrame().h * clipH / destH);
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

		SDL_Rect hitBox = { (int)destX + racer->hitBoxXOffset * scaling, (int)destY + racer->currentAnimation->GetCurrentFrame().h * scaling - 10,  (int)destW, 10 };
		//SDL_RenderFillRect(App->renderer->renderer, &hitBox);		//DEBUG

		//LOG("Scaling %f", scaling)
		//	LOG("Sprite height %d", racer->currentAnimation->GetCurrentFrame().h)
		//	LOG("Sprite width %d", racer->currentAnimation->GetCurrentFrame().w)
		//	LOG("Sprite X %f", destX)
		//	LOG("Sprite Y %f", destY)
		//	LOG("Sprite H %d", destH)
			if (destX < 0 || destY > SCREEN_HEIGHT) {
				return;
			}
			if (racer->currentAnimation->GetCurrentFrame().h< 0) {
				racer->currentAnimation->GetCurrentFrame().h = 0;
			}
		App->renderer->Blit(tex, (int)destX, (int)destY, &racer->currentAnimation->GetCurrentFrame(), 0.f, false, false, scaling, scaling);

		if (scaling >= 1) {
			App->player->DetectCollision(hitBox, ModulePlayer::collision_types::RIVAL);
		}
	}
	
};