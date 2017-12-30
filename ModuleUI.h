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
	void ShowLapTimes();
	void ShowBonusPoints(int time);

	SDL_Texture* graphics;

	SDL_Rect topRanks[7];

private:
	/*const int scoreScreenDivision = SCREEN_WIDTH / 7 - 16;*/

	void NameEntry();

	SDL_Rect blankSpace;

	//Racing UI
	SDL_Rect topTag;
	SDL_Rect timeTag;
	SDL_Rect scoreTag;
	SDL_Rect courseAndStageText;
	SDL_Rect speedText;
	SDL_Rect kmText;
	SDL_Rect europeText;

	SDL_Rect pauseTag;
	SDL_Rect gameOverTag;
	SDL_Rect lapTimesTag;
	SDL_Rect bonusPointsTag;

	//Score screen
	SDL_Rect initialEntryCountdown;
	SDL_Rect courseSelected;
	SDL_Rect rankText;
	SDL_Rect scoreText;
	SDL_Rect stageText;
	SDL_Rect nameText;
	SDL_Rect timeText;
	SDL_Rect minutesMark;
	SDL_Rect secondsMark;
	
	bool nameEntered = false;
	unsigned int characterIndex = 0;
	unsigned int nameCharacterIndex = 0;

	bool readyToCloseScreen;
};

#endif