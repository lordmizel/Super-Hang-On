#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Timer.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	enum player_state {
		BEFORE_RACE,
		RACING,
		CRASHING,
		RECOVERING,
		OUT_OF_CONTROL,
		GAME_OVER,
		PAST_GOAL,
		GOING_TO_END,
		END_SCENE,
		SCORE_SCREEN,
		PAUSE
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
	void CenterMaxX(float max);

	void DetectCollision(SDL_Rect r, collision_types typeOfCollision, float x = 0.0f);
	void Pause();
	
	player_state state;

	iPoint position;
	bool destroyed = false;

	SDL_Rect collider;

	Timer timeWaitingAtStart;
	Timer timeLeftInRace;
	Timer timePastGoal;

private:

	void ManageAnimations();
	void ManageSpeed();

	void ResetPlayer();

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
	int maxXPosition;

	int maxSpeedAuto = 90;
	int maxSpeedRunning = 290;
	int maxSpeedNitro = 324;
	int maxSpeedOffTrack = 106;
	int maxSpeedBraking = 85;
	bool offRoad = false;

	bool deviateRight;
	Timer timeOutOfControl;
	Timer gameOverTimer;

	//PAUSE PARAMETERS
	player_state previousState;
	float previousAnimationSpeed;
};

#endif