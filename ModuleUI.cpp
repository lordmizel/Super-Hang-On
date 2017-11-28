#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleFontManager.h"
#include "ModuleScore.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"


ModuleUI::ModuleUI(bool active) : Module(active)
{
	blankSpace = { 525, 280, 8, 8 };

	topTag = { 17, 219, 30, 12 };
	timeTag = { 49, 219, 37, 12 };
	scoreTag = { 88, 219, 48, 12 };
	courseAndStageText = { 314, 241, 48, 16 };
	speedText = { 138, 221, 40, 8 };
	kmText = { 184, 221, 16, 8 };
	europeText = { 325, 264, 48, 8 };
	
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start() {
	LOG("Loading UI");

	graphics = App->textures->Load("bikes.png", 255, 0, 204);

	return true;
}

bool ModuleUI::CleanUp() {
	LOG("Unloading score graphics");

	App->textures->Unload(graphics);

	return true;
}

void ModuleUI::ShowUI() {
	App->renderer->Blit(graphics, SCREEN_WIDTH / 12 - 16, SCREEN_HEIGHT / 17 - 4, &topTag, 0.0f, false, false, 2, 2);
	DigitRendering(App->score->GetTopScore(), 8, SCREEN_WIDTH / 12 * 2, SCREEN_HEIGHT / 17, Color(255, 0, 0, 255));

	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - timeTag.w, SCREEN_HEIGHT / 17 - 4, &timeTag, 0.0f, false, false, 2, 2);
	//TODO: Print time

	App->renderer->Blit(graphics, SCREEN_WIDTH / 12 * 7, SCREEN_HEIGHT / 17 - 4, &scoreTag, 0.0f, false, false, 2, 2);
	DigitRendering(App->score->GetScore(), 8, SCREEN_WIDTH / 12 * 9 + 8, SCREEN_HEIGHT / 17, Color(0, 255, 0, 255));

	App->renderer->Blit(graphics, SCREEN_WIDTH / 12 - 16, SCREEN_HEIGHT / 17 * 2 - 4, &courseAndStageText, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 12 * 3, SCREEN_HEIGHT / 17 * 2 - 4, &europeText, 0.0f, false, false, 2, 2);
	DigitRendering(App->score->GetStage(), 2, SCREEN_WIDTH / 12 * 3, SCREEN_HEIGHT / 17 * 2 + 12);
	
	App->renderer->Blit(graphics, SCREEN_WIDTH / 12 * 7, SCREEN_HEIGHT / 17 * 2 - 4, &speedText, 0.0f, false, false, 2, 2);
	DigitRendering(App->player->GetSpeed(), 3, SCREEN_WIDTH / 12 * 9 + 8, SCREEN_HEIGHT / 17 * 2 - 4);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 12 * 9 + 8 + 16 * 3, SCREEN_HEIGHT / 17 * 2 - 4, &kmText, 0.0f, false, false, 2, 2);
}

void ModuleUI::DigitRendering(int numberToRender, int numDigits, int x, int y, Color color)
{
	int numberThreshold = 1;

	for (int i = 0; i < numDigits - 1; i++) {
		numberThreshold *= 10;
	}
	
	int helper = numberToRender;
	int digitPositionX = 0;
	bool numberInRange = false;

	for (int dig = numDigits; dig > 0; dig--) {
		if (helper < numberThreshold && !numberInRange) {
			App->renderer->Blit(graphics, x + digitPositionX, y, &blankSpace, 0.0f, false, false, 2, 2);
		}
		else
		{
			App->font_manager->PrintDigit(helper / numberThreshold, x + digitPositionX, y, color);
			numberInRange = true;
		}

		helper = helper % numberThreshold;
		numberThreshold = numberThreshold / 10;
		digitPositionX += 16;
	}
}

//void ModuleUI::ShowRankings() {
//	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - initialEntryCountdown.w / 2, 30, &initialEntryCountdown, 0.0f, false, false, 2, 2);
//	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - courseSelected.w / 2, 46, &courseSelected, 0.0f, false, false, 2, 2);
//
//	App->renderer->Blit(graphics, SCREEN_WIDTH / 6 - rankText.w / 2, 62, &rankText, 0.0f, false, false, 2, 2);
//	App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 2 - scoreText.w / 2, 62, &scoreText, 0.0f, false, false, 2, 2);
//	App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 3 - stageText.w / 2, 62, &stageText, 0.0f, false, false, 2, 2);
//	App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 4 - nameText.w / 2, 62, &nameText, 0.0f, false, false, 2, 2);
//	App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2, 62, &timeText, 0.0f, false, false, 2, 2);
//
//	int posY = 78;
//	int maxNumOfScoreDigits = 8;
//
//	for (int i = 0; i < sizeof(topRanks) / sizeof(topRanks[0]); i++)
//	{
//		//Rank column
//		App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) - topRanks[i].w / 2, posY + 16 * i, &topRanks[i], 0.0f, false, false, 2, 2);
//
//		//Score column
//		int numberThreshold = 10000000;
//		int scoreToWorkWith = savedScores[i];
//		int digitPositionX = -32;
//		bool numberInRange = false;
//
//		for (int dig = maxNumOfScoreDigits; dig > 0; dig--) {
//			if (scoreToWorkWith < numberThreshold && !numberInRange) {
//				App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 2 + digitPositionX, posY + 16 * i, &blankSpace, 0.0f, false, false, 2, 2);
//			}
//			else
//			{
//				App->font_manager->PrintDigit(scoreToWorkWith / numberThreshold, (SCREEN_WIDTH / 6) * 2 + digitPositionX, posY + 32 * i, Color(255, 255, 255, 255));
//				numberInRange = true;
//			}
//
//			scoreToWorkWith = scoreToWorkWith % numberThreshold;
//			numberThreshold = numberThreshold / 10;
//			digitPositionX += 16;
//		}
//
//		// Stage column
//
//		// Name column
//
//		// Time column
//
//	}
//}