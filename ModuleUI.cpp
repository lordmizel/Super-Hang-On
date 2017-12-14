#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleFontManager.h"
#include "ModuleScore.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include <string>


ModuleUI::ModuleUI(bool active) : Module(active)
{
	blankSpace = { 508, 270, 8, 8 };

	//Racing UI
	topTag = { 17, 219, 30, 12 };
	timeTag = { 49, 219, 37, 12 };
	scoreTag = { 88, 219, 48, 12 };
	courseAndStageText = { 314, 241, 48, 16 };
	speedText = { 138, 221, 40, 8 };
	kmText = { 184, 221, 16, 8 };
	europeText = { 325, 264, 48, 8 };
	
	//Score screen
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

	minutesMark = { 521, 280, 8, 8 };
	secondsMark = { 521, 289, 8, 8 };
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
	if (App->player->GetSpeed() >= App->player->GetMaxSpeedRunning()) 
	{
		DigitRendering(App->player->GetSpeed(), 3, SCREEN_WIDTH / 12 * 9 + 8, SCREEN_HEIGHT / 17 * 2 - 4, Color(255, 0, 0, 255));
	}
	else 
	{
		DigitRendering(App->player->GetSpeed(), 3, SCREEN_WIDTH / 12 * 9 + 8, SCREEN_HEIGHT / 17 * 2 - 4);
	}
	App->renderer->Blit(graphics, SCREEN_WIDTH / 12 * 9 + 8 + 16 * 3, SCREEN_HEIGHT / 17 * 2 - 4, &kmText, 0.0f, false, false, 2, 2);
}

void ModuleUI::DigitRendering(int numberToRender, int numDigits, int x, int y, Color color, bool fillWithZero)
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
			if (!fillWithZero) {
				App->renderer->Blit(graphics, x + digitPositionX, y, &blankSpace, 0.0f, false, false, 2, 2);
			}
			else {
				App->font_manager->PrintDigit(0, x + digitPositionX, y, color);
			}
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

void ModuleUI::StringRendering(string stringToRender, int x, int y, Color color) {
	int digitPositionX = 0;
	for (int c = 0; c < stringToRender.size(); c++) {
		App->font_manager->PrintChar(stringToRender.at(c), x + digitPositionX, y, color);
		digitPositionX += 16;
	}
}

void ModuleUI::ShowRankings() {

	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - initialEntryCountdown.w * 2 / 2, SCREEN_HEIGHT / 13, &initialEntryCountdown, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - courseSelected.w * 2 / 2, SCREEN_HEIGHT / 13 * 2, &courseSelected, 0.0f, false, false, 2, 2);

	App->renderer->Blit(graphics, SCREEN_WIDTH / 6 - rankText.w / 2, SCREEN_HEIGHT / 13 * 3, &rankText, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 2 - scoreText.w / 2, SCREEN_HEIGHT / 13 * 3, &scoreText, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 3 - stageText.w / 2, SCREEN_HEIGHT / 13 * 3, &stageText, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 4 - nameText.w / 2, SCREEN_HEIGHT / 13 * 3, &nameText, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2, SCREEN_HEIGHT / 13 * 3, &timeText, 0.0f, false, false, 2, 2);

	int Ymultiplier = 0;
	int maxNumOfScoreDigits = 8;

	for (int i = 0; i < sizeof(topRanks) / sizeof(topRanks[0]); i++)
	{
		int posY = SCREEN_HEIGHT / 13 * (4 + Ymultiplier);
		Color entryColor = { 255, 255, 255, 255 };

		if (i == App->score->entryInScoreTable && App->score->entryInScoreTable != NULL) {
			entryColor = { 255, 0, 0, 255 };
		}

		//Rank column
		App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) - topRanks[i].w / 2, posY, &topRanks[i], 0.0f, false, false, 2, 2, entryColor);

		//Score column
		DigitRendering(App->score->scoreEntries[i].score, 8, (SCREEN_WIDTH / 6) * 2 -54, posY, entryColor);

		// Stage column
		DigitRendering(App->score->scoreEntries[i].stage, 2, (SCREEN_WIDTH / 6) * 3 - stageText.w / 2 + 16, posY, entryColor);

		// Name column
		StringRendering(App->score->scoreEntries[i].name, (SCREEN_WIDTH / 6) * 4 - nameText.w / 2, posY, entryColor);

		// Time column
		DigitRendering(App->score->scoreEntries[i].timeMin, 2, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 - 32, posY, entryColor, true);
		App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 + 32 - 32, posY, &minutesMark, 0.0f, false, false, 2, 2, entryColor);
		DigitRendering(App->score->scoreEntries[i].timeSec, 2, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 + 48 - 32, posY, entryColor, true);
		App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 + 80 - 32, posY, &secondsMark, 0.0f, false, false, 2, 2, entryColor);
		DigitRendering(App->score->scoreEntries[i].timeDec, 2, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 + 96 - 32, posY, entryColor, true);

		Ymultiplier++;
	}

	if (App->score->entryInScoreTable == NULL && nameEntered == false) {
		StringRendering("YOU.", (SCREEN_WIDTH / 6) - topRanks[0].w / 2, SCREEN_HEIGHT / 13 * (4 + Ymultiplier), { 255, 0, 0, 255 });
		DigitRendering(App->score->currentScore.score, 8, (SCREEN_WIDTH / 6) * 2 - 54, SCREEN_HEIGHT / 13 * (4 + Ymultiplier), { 255, 0, 0, 255 });
	}

	//TODO: REMEMBER TO PUT nameEntered TO FALSE AND characterIndex AND nameCharacterIndex TO 0 EVERY TIME A NEW RACE STARTS
	if (App->score->entryInScoreTable != NULL && nameEntered == false) {
		Color color;
		int positionX = 0;
		string nameEntryString = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.</";

		for (int i = 0; i < nameEntryString.size(); i++) {
			if (i == characterIndex) {
				color = { 255, 0, 0, 255 };
			}
			else
			{
				color = { 255, 255, 255, 255 };
			}
			App->font_manager->PrintChar(nameEntryString[i], positionX, SCREEN_HEIGHT / 13 * 12, color);
			positionX += 16;
		}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
		{
			characterIndex++;
			if (characterIndex >= nameEntryString.size()) {
				characterIndex = 0;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
		{
			characterIndex--;
			if (characterIndex < 0) {
				characterIndex = nameEntryString.size() - 1;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			if (characterIndex == nameEntryString.size() - 1) 
			{
				nameEntered = true;
			} 
			else if (characterIndex == nameEntryString.size() - 2) 
			{
				if (nameCharacterIndex != 0) {
					App->score->scoreEntries[App->score->entryInScoreTable].name[nameCharacterIndex - 1] = ' ';
					//App->score->currentScore.name[nameCharacterIndex] = ' ';
					nameCharacterIndex--;
				}
			}
			else
			{
				if (nameCharacterIndex < 3) {
					App->score->scoreEntries[App->score->entryInScoreTable].name[nameCharacterIndex] = nameEntryString[characterIndex];
					//App->score->currentScore.name[nameCharacterIndex] = nameEntryString[characterIndex];
					nameCharacterIndex++;
				}
			}
		}
	}
}