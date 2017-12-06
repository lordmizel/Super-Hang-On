#ifndef __MODULEUI__
#define __MODULEUI__

#include "Module.h"

struct SDL_Texture;

class ModuleUI : public Module
{
public:
	ModuleUI(bool active = true);
	~ModuleUI();

	bool Start();
	bool CleanUp();

	void ShowUI();
	void ShowRankings();
	void DigitRendering(int numberToRender, int numDigits, int x, int y, Color color = Color(255, 255, 255, 255));

	SDL_Texture* graphics;

	SDL_Rect topRanks[7];

private:
	SDL_Rect blankSpace;

	//Racing UI
	SDL_Rect topTag;
	SDL_Rect timeTag;
	SDL_Rect scoreTag;
	SDL_Rect courseAndStageText;
	SDL_Rect speedText;
	SDL_Rect kmText;
	SDL_Rect europeText;

	//Score screen
	SDL_Rect initialEntryCountdown;
	SDL_Rect courseSelected;
	SDL_Rect rankText;
	SDL_Rect scoreText;
	SDL_Rect stageText;
	SDL_Rect nameText;
	SDL_Rect timeText;
	
};

#endif