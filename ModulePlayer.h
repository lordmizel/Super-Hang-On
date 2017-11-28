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

	inline int GetSpeed() const { return speed; }
	void PrintSpeed();

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
	Animation forwardBraking;
	Animation leaningLeftBraking;
	Animation leanedLeftBraking;
	Animation unLeanLeftBraking;
	Animation leaningRightBraking;
	Animation leanedRightBraking;
	Animation unLeanRightBraking;
	
	SDL_Rect speedDigits[3];
	SDL_Rect kmText;

	SDL_Rect blankSpace;

	iPoint position;
	bool destroyed = false;

private:
	bool braking = false;
	int speed = 0;
	int acceleration = 1;
	int currentMaxSpeed;

	int maxSpeedAuto = 90;
	int maxSpeedRunning = 290;
	int maxSpeedNitro = 324;
	int maxSpeedOffTrack = 106;
	int maxSpeedBraking = 85;
	bool offRoad = false;

	void ManageAnimations();
	void ManageSpeed();

	time_t now;
};

#endif