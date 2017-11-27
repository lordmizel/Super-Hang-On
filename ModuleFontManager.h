#ifndef __MODULEFONTMANAGER_H__
#define __MODULEFONTMANAGER_H__

#include "Module.h"

struct SDL_Texture;

class ModuleFontManager : public Module
{
public:
	ModuleFontManager(bool start_enabled = true);
	~ModuleFontManager();

	bool Start();
	bool CleanUp();

	void PrintDigit(int digit, int x, int y, Color color);

private:
	SDL_Texture* graphics = nullptr;

	SDL_Rect blankSpace;
	SDL_Rect numbers[10];
};

#endif