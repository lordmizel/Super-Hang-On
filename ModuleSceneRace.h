#ifndef __MODULESCENERACE_H__
#define __MODULESCENERACE_H__

#include <vector>
#include "Module.h"

struct SDL_Texture;

class ModuleRoad;
class ModuleScore;

class ModuleSceneRace : public Module
{
public:
	const static int ROAD_INIT_OFFSET = 40;	//Distance between camera and first segment to draw

	ModuleSceneRace(bool active = true);
	~ModuleSceneRace();

	bool Start();
	update_status Update();
	bool CleanUp();

	ModuleScore* scoreBoard;

	SDL_Texture* graphics = nullptr;

	SDL_Rect backdrop;

private:

	std::vector<ModuleRoad> roads;
};

#endif // __MODULESCENESPACE_H__