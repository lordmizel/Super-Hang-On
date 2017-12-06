#include <string>
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
	string inputString;

	file.open(fileName, std::ifstream::in | std::ifstream::out);

	for (int i = 0; i < 7; i++) {
		file >> inputString;
		LOG("%d", stoi(inputString))
		file >> inputString;
		LOG("%d", stoi(inputString))
		file >> inputString;
		LOG("%s", inputString)
		file >> inputString;
		LOG("%d", stoi(inputString))
	}
	// TODO: Assign actual valid data to Top Score
	topScore = 4000000;

	//TODO: This should happen when race starts, not when this module is initialized
	ResetScore();

	return true;
}


update_status ModuleScore::Update()
{
	//App->renderer->Blit(graphics, 0, 0, &initialEntryCountdown, 0.0f, false, false, 2, 2);

	return UPDATE_CONTINUE;
}

bool ModuleScore::CleanUp()
{
	file.close();
	return true;
}


void ModuleScore::ShowScore() {
	
}

