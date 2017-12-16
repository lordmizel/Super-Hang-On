#ifndef __MODULESCENEMAP_H__
#define __MODULESCENEMAP_H__

#include "Module.h"
#include "Animation.h"
#include "Timer.h"

struct SDL_Texture;

enum courseSelect {
	AFRICA,
	ASIA,
	AMERICA,
	EUROPE
};

class ModuleSceneMap : public Module
{
public:
	ModuleSceneMap(bool active = true);
	~ModuleSceneMap();

	bool Start();
	update_status Update();
	bool CleanUp();

	SDL_Texture* graphics = nullptr;

	SDL_Rect backdrop;
	SDL_Rect worldMap;
	SDL_Rect chooseClass;
	SDL_Rect courseAfrica;
	SDL_Rect courseAsia;
	SDL_Rect courseAmerica;
	SDL_Rect courseEurope;

	Animation africa;
	Animation asia;
	Animation america;
	Animation europe;
	Animation pressButton;

	Timer timer_;

	int courseSelect = AFRICA;
	uint fx = 0;
};

#endif