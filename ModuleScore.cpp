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

	//TODO: DELETE THIS, ONLY FOR DEBUG
	currentScore.score = 1400000;
	currentScore.stage = 2;
	currentScore.time = 12345;
	currentScore.timeMin = (currentScore.time / 100) / 60;
	currentScore.timeSec = (currentScore.time / 100) % 60;
	currentScore.timeDec = currentScore.time % 100;

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

void ModuleScore::ValidateScoreEntry() {
	bool validEntry = false;
	//Recorrer lista de puntuaciones y ver si supera las puntuaciones guardadas
	for (unsigned int i = 0; i < scoreEntries.size(); i++) {
		if (currentScore.score > scoreEntries[i].score) {
			entryInScoreTable = i;
			validEntry = true;
			break;
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
	currentScore.score = 0;
	currentScore.stage = 1;
	currentScore.name = "   ";
	currentScore.time = 0;
}

