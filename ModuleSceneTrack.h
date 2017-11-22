#ifndef __ModuleSceneTrack_H__
#define __ModuleSceneTrack_H__

#include "Module.h"
#include "Animation.h"

class Line;
class ModuleEnemy;

class ModuleSceneTrack : public Module
{

public:
	ModuleSceneTrack(bool active = true);
	~ModuleSceneTrack();

	bool Start();
	update_status Update(/*float deltaTime*/);
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* decoration = nullptr;
	SDL_Texture* gui = nullptr;

	Animation sempahor;
	SDL_Rect startSign;
	SDL_Rect background;
	SDL_Rect backgroundParalax;
	SDL_Rect backgroundTop;
	SDL_Rect backgroundTime;
	SDL_Rect backgroundScore;
	SDL_Rect backgroundStage;
	SDL_Rect backgroundStageProces;
	SDL_Rect backgroundCourse;
	SDL_Rect backgroundSpeed;
	SDL_Rect backgroundKm;
	SDL_Rect backgroundTrackName;
	SDL_Rect deadTree;

	SDL_Rect obejct;

	SDL_Rect road;
	SDL_Rect limit;
	SDL_Rect midLine;

	Color grass1;
	Color grass2;
	Color rumble1;
	Color rumble2;
	Color color_road;
	Color color_line;

	vector<Line> lines;

	int N = 0;
	int pos;
	int playerX;
private:
	void PrintTrack();
	void PrintGui();
	int maxPuntuation;
	int stage;
	float time;
	int score;
	int speed;
};

#endif // __ModuleSceneTrack_H__