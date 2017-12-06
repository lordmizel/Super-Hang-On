#ifndef __MODULESCORE__
#define __MODULESCORE__

#include "Module.h"
#include <fstream>
#include <iostream>
#include <vector>

struct SDL_Texture;

class ModuleScore : public Module
{
public:
	struct scoreEntry {
		int score;
		int stage;
		std::string name;
		int time;
	};

	ModuleScore(bool active = true);
	~ModuleScore();

	bool Start();
	update_status Update();
	bool CleanUp();

	int GetTopScore() { return topScore; }

	/**
	 - Compute where the new score will be inserted moving the following ranks
	 - Show the list
	 - Store the new ranking*/
	void ShowScore();

	// Call every time a race begins
	void ResetScore() {
		current_time = 0;
		stage = 1;
		currentScore = 0;
		current_player = "";
	}

	void setName(std::string playerName) {
		current_player = playerName;
	}

	void setTime(int64_t t) {
		current_time = t;
	}

	void UpdateScore(int deltaScore) { currentScore += deltaScore; }

	int GetScore() { return currentScore; }
	int GetStage() { return stage; }

	int savedScores[7] = { 57170640, 34, 43543, 2, 10087, 9876542, 1234567 };

	// Loads the score file, use on start()
	void loadSavedScores();

	// Saves the score ranking, use on showScore()
	void saveCurrentScore();

	std::vector<scoreEntry> scoreEntries;

private:
	int topScore;
	int currentScore;
	int stage;
	int64_t current_time;
	std::string current_player;

	std::string fileName = "scores.txt";
	std::ifstream file;
};

#endif