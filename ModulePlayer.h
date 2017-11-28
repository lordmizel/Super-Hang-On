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

	bool Start();
	update_status Update();
	bool CleanUp();

	inline int GetSpeed() const { return speed; }
	int GetXPosition() const { return positionX; }
	void AlterXPosition(int alt) { positionX += alt; }

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

	iPoint position;
	bool destroyed = false;

private:
	void ManageAnimations();
	void ManageSpeed();

	bool braking = false;
	int speed = 0;
	int acceleration = 1;
	int currentMaxSpeed;

	int positionX = 0;
	int movementX = 50;

	int maxSpeedAuto = 90;
	int maxSpeedRunning = 290;
	int maxSpeedNitro = 324;
	int maxSpeedOffTrack = 106;
	int maxSpeedBraking = 85;
	bool offRoad = false;

	

	time_t now;
};

#endif