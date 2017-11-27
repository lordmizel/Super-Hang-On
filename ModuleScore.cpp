#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFontManager.h"
#include "ModuleScore.h"

int savedScores[7] = { 57170640, 34, 43543, 2, 10087, 9876542, 1234567 };

ModuleScore::ModuleScore(bool active) : Module(active)
{
	initialEntryCountdown = { 6, 915, 210, 8 };
	courseSelected = { 432, 941, 104, 8 };
	rankText = { 17, 208, 32, 8 };
	scoreText = { 76, 208, 40, 8 };
	stageText = { 138, 208, 40, 8 };
	nameText = { 226, 221, 32, 8 };
	timeText = { 226, 232, 32, 8 };
	
	topRanks[0] = { 508, 549, 24, 8 };
	topRanks[1] = { 508, 558, 24, 8 };
	topRanks[2] = { 508, 567, 24, 8 };
	topRanks[3] = { 508, 576, 24, 8 };
	topRanks[4] = { 508, 585, 24, 8 };
	topRanks[5] = { 508, 594, 24, 8 };
	topRanks[6] = { 508, 603, 24, 8 };
	topRanks[7] = { 508, 612, 24, 8 };

	blankSpace = { 525, 280, 8, 8 };
}

ModuleScore::~ModuleScore()
{
}

bool ModuleScore::Start()
{
	LOG("Loading score module");

	//graphics = App->textures->Load("bikes.png", 255, 0, 204);

	// TODO: Assign actual valid data to Top Score
	topScore = 4000000;

	return true;
}

// UnLoad assets
bool ModuleScore::CleanUp()
{
	LOG("Unloading race scene");

	App->textures->Unload(graphics);

	return true;
}


update_status ModuleScore::Update()
{
	App->renderer->Blit(graphics, 0, 0, &initialEntryCountdown, 0.0f, false, false, 2, 2);

	return UPDATE_CONTINUE;
}


void ModuleScore::ShowScore() {
	LOG("Top score: %d", topScore);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - initialEntryCountdown.w/2, 30, &initialEntryCountdown, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - courseSelected.w / 2, 46, &courseSelected, 0.0f, false, false, 2, 2);

	App->renderer->Blit(graphics, SCREEN_WIDTH / 6 - rankText.w / 2, 62, &rankText, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 2 - scoreText.w / 2, 62, &scoreText, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 3 - stageText.w / 2, 62, &stageText, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 4 - nameText.w / 2, 62, &nameText, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2, 62, &timeText, 0.0f, false, false, 2, 2);

	int posY = 78;
	int maxNumOfScoreDigits = 8;

	for (int i = 0; i < sizeof(topRanks) / sizeof(topRanks[0]); i++)
	{
		//Rank column
		App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) - topRanks[i].w / 2, posY + 16 * i, &topRanks[i], 0.0f, false, false, 2, 2);

		//Score column
		int numberThreshold = 10000000;
		int scoreToWorkWith = savedScores[i];
		int digitPositionX = -32;
		bool numberInRange = false;

		for (int dig = maxNumOfScoreDigits; dig > 0; dig--) {
			if (scoreToWorkWith < numberThreshold && !numberInRange) {
				App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 2 + digitPositionX, posY + 16 * i, &blankSpace, 0.0f, false, false, 2, 2);
			}
			else
			{
				App->font_manager->PrintDigit(scoreToWorkWith / numberThreshold, (SCREEN_WIDTH / 6) * 2 + digitPositionX, posY + 32 * i, Color(255, 255, 255, 255));
				numberInRange = true;
			}

			scoreToWorkWith = scoreToWorkWith % numberThreshold;
			numberThreshold = numberThreshold / 10;
			digitPositionX += 16;
		}

		// Stage column

		// Name column
		
		// Time column

	}
}