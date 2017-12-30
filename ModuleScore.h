#ifndef __MODULESCORE__
#define __MODULESCORE__

#include "Module.h"
#include <fstream>
#include <iostream>
#include <vector>

struct SDL_Texture;

struct scoreEntry {
	int score;
	int stage;
	std::string name;
	int time;

	int timeMin;
	int timeSec;
	int timeDec;
};

class ModuleScore : public Module
{
public:
	ModuleScore(bool active = true);
	~ModuleScore();

	bool Start();
	update_status Update();
	bool CleanUp();

	int GetTopScore() { return scoreEntries[0].score; }
	int GetScore() { return currentScore.score; }
	int GetStage() { return currentScore.stage; }

	void setTime(int64_t t) { current_time = t; }

	void UpdateScore(int deltaScore) { currentScore.score += deltaScore; }

	void ValidateScoreEntry(double totalTime);
	void SaveScoreEntry();
	void ResetScore();

	std::vector<scoreEntry> scoreEntries;
	int entryInScoreTable = NULL;

	scoreEntry currentScore;

	bool scoreIsHighEnough;

private:
	int topScore;
	int64_t current_time;

	std::string fileName = "scores.txt";
	std::ifstream readFile;
	std::ofstream writeFile;
};

#endif