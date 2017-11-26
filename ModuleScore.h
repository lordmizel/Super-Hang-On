#ifndef __MODULESCORE__
#define __MODULESCORE__

#include <map>
#include "Module.h"

class ModuleScore : public Module
{
public:
	ModuleScore(bool active = true);
	~ModuleScore();

	bool Start();
	update_status Update();
	bool CleanUp();

	/**
	 - Compute where the new score will be inserted moving the following ranks
	 - Show the list
	 - Store the new ranking*/
	void ShowScore();

	// Call every time a race begins
	void resetScore() {
		current_time = 0;
		current_score = 0;
		current_player = "";
	}

	void setName(std::string playerName) {
		current_player = playerName;
	}

	void setTime(int64_t t) {
		current_time = t;
	}

	void updateScore(int deltaScore) {
		current_score += deltaScore;
	}

	// Loads the score file, use on start()
	void loadSavedScores();

	// Saves the score ranking, use on showScore()
	void saveCurrentScore();

	SDL_Texture* graphics = nullptr;

	SDL_Rect initialEntryCountdown;
	SDL_Rect courseSelected;
	SDL_Rect rankText;
	SDL_Rect scoreText;
	SDL_Rect stageText;
	SDL_Rect nameText;
	SDL_Rect timeText;
	SDL_Rect topRanks[7];

	SDL_Rect numbers[10];
	SDL_Rect blankSpace;

private:
	int current_score;
	int64_t current_time;
	std::string current_player;
};

#endif