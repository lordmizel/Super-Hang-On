#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	int GetCurrentSegment() const { return currentSegment; }
	int GetSpeed() const { return speed; }

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation forward;
	Animation leaningLeft;
	Animation leanedLeft;
	Animation unLeanLeft;
	Animation leaningRight;
	Animation leanedRight;
	Animation unLeanRight;

	iPoint position;
	bool destroyed = false;

private:
	int currentSegment = 0;		//The segment where the player is currently
	int speed = 0;
};

#endif