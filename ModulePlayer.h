#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;



class ModulePlayer : public Module
{
public:
	enum player_state {
		BEFORE_RACE,
		RACING,
		CRASHING,
		RECOVERING,
		AFTER_RACE
	};

	enum collision_types {
		OBSTACLE,
		RIVAL
	};

	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	inline int GetSpeed() const { return speed; }
	inline int GetMaxSpeedRunning() const { return maxSpeedRunning; }
	int GetXPosition() const { return positionX; }
	inline int GetAbsoluteX() const { return absoluteX; }

	void AlterXPosition(int alt) { positionX += alt; }

	void DetectCollision(SDL_Rect r, collision_types typeOfCollision);
	
	player_state state;

	iPoint position;
	bool destroyed = false;

	SDL_Rect collider;

private:

	void ManageAnimations();
	void ManageSpeed();

	SDL_Texture* graphics = nullptr;
	SDL_Texture* crashes = nullptr;
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
	Animation smallCrash;
	Animation bigCrash;

	bool braking = false;
	int speed = 0;
	int acceleration = 1;
	int currentMaxSpeed;

	int positionX = 0;
	int movementX = 50;
	int absoluteX = 0;

	int maxSpeedAuto = 90;
	int maxSpeedRunning = 290;
	int maxSpeedNitro = 324;
	int maxSpeedOffTrack = 106;
	int maxSpeedBraking = 85;
	bool offRoad = false;

	time_t now;
};

#endif