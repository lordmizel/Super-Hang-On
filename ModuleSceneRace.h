#ifndef __MODULESCENERACE_H__
#define __MODULESCENERACE_H__

#include <vector>
#include "Module.h"

struct SDL_Texture;

class ModuleRoad;

class ModuleSceneRace : public Module
{
public:
	ModuleSceneRace(bool active = true);
	~ModuleSceneRace();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* background = nullptr;
	SDL_Texture* stars = nullptr;

private:

	std::vector<ModuleRoad> roads;
};

#endif // __MODULESCENESPACE_H__