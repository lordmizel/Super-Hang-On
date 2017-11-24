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
	SDL_Rect landscapeParis;
	SDL_Rect landscapePlains;

	
};

#endif