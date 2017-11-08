#ifndef __MODULESCENEINTRO_H__
#define __MODULESCENEINTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

enum menuNavigation {
	NEW_GAME,
	PASSWORD,
	ARCADE_MODE,
	ORIGINAL_MODE
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool active = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	menuNavigation selectedOption;
	
	SDL_Texture* graphics = nullptr;
	
	SDL_Rect titleLetters[7];
	int letterPositions[7];
	int currentLetterPosition[7];
	int currentMovingLetter = 0;
	int letterSpeed = 8;

	SDL_Rect menuOptions1;
	SDL_Rect menuOptions2;
	SDL_Rect trademark;

	Animation superHangOn;
	Animation segaLogo;
	Animation arrow;

	uint fx = 0;
};

#endif // __MODULESCENEINTRO_H__