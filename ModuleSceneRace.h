#ifndef __ModuleSceneRace_H__
#define __ModuleSceneRace_H__

#include "Module.h"
#include "Animation.h"

class Segment;
class ModuleEnemy;

class ModuleSceneRace : public Module
{

public:
	ModuleSceneRace(bool active = true);
	~ModuleSceneRace();

	bool Start();
	update_status Update(/*float deltaTime*/);
	bool CleanUp();

public:
	vector<Segment> lines;
	
	int N = 0;
	int pos;
	int playerX;

protected:
	vector<SDL_Rect> backgrounds;

	Color grass1;
	Color grass2;
	Color rumble1;
	Color rumble2;
	Color color_road;
	Color color_line;

private:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* decoration = nullptr;

	Animation sempahor;

	SDL_Rect road;
	SDL_Rect limit;
	SDL_Rect midLine;

	int landscapePosition = 0;

	void DrawRoad();
	int stage;
	float time_;

	SDL_Rect landscapeParis;
};

#endif