#ifndef __MODULESCORE__
#define __MODULESCORE__

#include <map>
#include "Module.h"

class ModuleScore : public Module
{
public:
	ModuleScore(bool active = true);
	~ModuleScore();

	bool Start();
	update_status Update();
	bool CleanUp();

	void ShowScore();

	SDL_Texture* graphics = nullptr;

	SDL_Rect initialEntryCountdown;
	SDL_Rect courseSelected;
	SDL_Rect rankText;
	SDL_Rect scoreText;
	SDL_Rect stageText;
	SDL_Rect nameText;
	SDL_Rect timeText;
	SDL_Rect topRanks[8];

	SDL_Rect numbers[10];
	SDL_Rect blankSpace;
};

#endif