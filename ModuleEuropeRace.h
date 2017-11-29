#ifndef __ModuleEuropeRace_H__
#define __ModuleEuropeRace_H__

#include "Animation.h"
#include "ModuleSceneRace.h"

class ModuleEuropeRace : public ModuleSceneRace
{

public:
	ModuleEuropeRace(bool active = true);
	~ModuleEuropeRace();

private:
	biome paris;
	biome coast;
	biome sunset;
	biome alpine;
	biome windmills;
	biome city;

	SDL_Rect landscapeParis;
	SDL_Rect parisBuildings;
	SDL_Rect landscapeSea;
	SDL_Rect seaRocks;
	SDL_Rect landscapeSunset;
	SDL_Rect sunsetBuildings;
	SDL_Rect landscapeAlpine;
	SDL_Rect alpineMountains;
	SDL_Rect landscapeWindmills;
	SDL_Rect windmillVillage;
	SDL_Rect landscapeCity;
	SDL_Rect cityBuildings;

	SDL_Rect landscapeGrassland;

	
};

#endif