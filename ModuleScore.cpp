#include <string>
#include <vector>
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFontManager.h"
#include "ModuleScore.h"

using namespace std;


ModuleScore::ModuleScore(bool active) : Module(active)
{
}

ModuleScore::~ModuleScore()
{
}

bool ModuleScore::Start()
{
	LOG("Loading score module");

	ResetScore();

	string inputString;

	readFile.open(fileName);

	while (!readFile.eof()) {
		scoreEntry entry;
		
		getline(readFile, inputString, ';');
		entry.score = stoi(inputString);
		getline(readFile, inputString, ';');
		entry.stage = stoi(inputString);
		getline(readFile, inputString, ';');
		entry.name = inputString.c_str();
		getline(readFile, inputString, ';');
		entry.time = stoi(inputString);

		entry.timeMin = (entry.time / 100) / 60;
		entry.timeSec = (entry.time / 100) % 60;
		entry.timeDec = entry.time % 100;

		scoreEntries.push_back(entry);
	}

	readFile.close();

	return true;
}


update_status ModuleScore::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleScore::CleanUp()
{
	return true;
}

void ModuleScore::ValidateScoreEntry(double totalTime) {
	App->score->currentScore.time = (int)(totalTime * 100);
	currentScore.timeMin = (currentScore.time / 100) / 60;
	currentScore.timeSec = (currentScore.time / 100) % 60;
	currentScore.timeDec = currentScore.time % 100;

	for (unsigned int i = 0; i < scoreEntries.size(); i++) {
		if (currentScore.score > scoreEntries[i].score) 
		{
			entryInScoreTable = i;
			scoreIsHighEnough = true;
			break;
		}
		else {
			scoreIsHighEnough = false;
		}
	}
}

void ModuleScore::SaveScoreEntry() {
	scoreEntries.pop_back();
	scoreEntries.insert(scoreEntries.begin() + entryInScoreTable, currentScore);

	writeFile.open(fileName, std::ios::out | std::ios::trunc);

	for (int i = 0; i < 7; i++) {
		writeFile << scoreEntries[i].score;
		writeFile << ";";
		writeFile << scoreEntries[i].stage;
		writeFile << ";";
		writeFile << scoreEntries[i].name;
		writeFile << ";";
		writeFile << scoreEntries[i].time;
		if (i < 6) {
			writeFile << ";" << endl;
		}
	}

	writeFile.close();
}

void ModuleScore::ResetScore()
{
	scoreIsHighEnough = false;

	currentLaps.clear();
	storedLaps.clear();
	reductionTime = 0;
	checkPointsPassed = 0;

	currentScore.score = 1400000;
	currentScore.stage = 1;
	currentScore.name = "   ";
	currentScore.time = 0;
}

void ModuleScore::OpenLapData(std::string & file)
{
	string inputString;
	lapFileName = file;

	readLapFile.open(lapFileName);

	while (!readLapFile.eof()) {
		getline(readLapFile, inputString, ';');
		storedLaps.push_back(stoi(inputString));
	}
	readLapFile.close();
}

void ModuleScore::SaveLapData()
{
	writeLapFile.open(lapFileName, std::ios::out | std::ios::trunc);

	for (int i = 0; i < storedLaps.size(); i++) {
		writeLapFile << storedLaps[i];
		if (i < storedLaps.size() - 1) {
			writeLapFile << ";";
		}
	}

	writeLapFile.close();
}

void ModuleScore::CompareLapTime(int currentTime)
{
	int actualLapTime = currentTime - reductionTime;
	currentLaps.push_back(actualLapTime);

	if (actualLapTime < storedLaps[checkPointsPassed] || storedLaps[checkPointsPassed] == 0) {
		storedLaps[checkPointsPassed] = actualLapTime;
	}

	reductionTime = currentTime;
	checkPointsPassed++;
}

