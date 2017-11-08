#ifndef __MODULESCENESPACE_H__
#define __MODULESCENESPACE_H__

#include <vector>
#include "Module.h"

struct SDL_Texture;

class ModuleRoad;

class ModuleSceneSpace : public Module
{
public:
	ModuleSceneSpace(bool active = true);
	~ModuleSceneSpace();

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