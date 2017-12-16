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

	pauseTag = { 5, 929, 52, 8 };
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
	App->font_manager->DigitRendering(App->score->GetTopScore(), 8, SCREEN_WIDTH / 12 * 2, SCREEN_HEIGHT / 17, Color(255, 0, 0, 255));

	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - timeTag.w, SCREEN_HEIGHT / 17 - 4, &timeTag, 0.0f, false, false, 2, 2);
	//TODO: Print time

	App->renderer->Blit(graphics, SCREEN_WIDTH / 12 * 7, SCREEN_HEIGHT / 17 - 4, &scoreTag, 0.0f, false, false, 2, 2);
	App->font_manager->DigitRendering(App->score->GetScore(), 8, SCREEN_WIDTH / 12 * 9 + 8, SCREEN_HEIGHT / 17, Color(0, 255, 0, 255));

	App->renderer->Blit(graphics, SCREEN_WIDTH / 12 - 16, SCREEN_HEIGHT / 17 * 2 - 4, &courseAndStageText, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 12 * 3, SCREEN_HEIGHT / 17 * 2 - 4, &europeText, 0.0f, false, false, 2, 2);
	App->font_manager->DigitRendering(App->score->GetStage(), 2, SCREEN_WIDTH / 12 * 3, SCREEN_HEIGHT / 17 * 2 + 12);
	
	App->renderer->Blit(graphics, SCREEN_WIDTH / 12 * 7, SCREEN_HEIGHT / 17 * 2 - 4, &speedText, 0.0f, false, false, 2, 2);
	if (App->player->GetSpeed() >= App->player->GetMaxSpeedRunning()) 
	{
		App->font_manager->DigitRendering(App->player->GetSpeed(), 3, SCREEN_WIDTH / 12 * 9 + 8, SCREEN_HEIGHT / 17 * 2 - 4, Color(255, 0, 0, 255));
	}
	else 
	{
		App->font_manager->DigitRendering(App->player->GetSpeed(), 3, SCREEN_WIDTH / 12 * 9 + 8, SCREEN_HEIGHT / 17 * 2 - 4);
	}
	App->renderer->Blit(graphics, SCREEN_WIDTH / 12 * 9 + 8 + 16 * 3, SCREEN_HEIGHT / 17 * 2 - 4, &kmText, 0.0f, false, false, 2, 2);

	if (App->player->state == ModulePlayer::PAUSE) {
		App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - pauseTag.w, SCREEN_HEIGHT / 2 - pauseTag.h, &pauseTag, 0.0f, false, false, 2, 2);
	}
}

void ModuleUI::ShowRankings() {

	int rankNumber = 0;

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

		if (i == App->score->entryInScoreTable && App->score->entryInScoreTable != NULL && nameEntered == false) {
			entryColor = { 255, 0, 0, 255 };

			//Rank column
			App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) - topRanks[i].w / 2, posY, &topRanks[i], 0.0f, false, false, 2, 2, entryColor);

			//Score column
			App->font_manager->DigitRendering(App->score->currentScore.score, 8, (SCREEN_WIDTH / 6) * 2 - 54, posY, entryColor);

			// Stage column
			App->font_manager->DigitRendering(App->score->currentScore.stage, 2, (SCREEN_WIDTH / 6) * 3 - stageText.w / 2 + 16, posY, entryColor);

			// Name column
			App->font_manager->StringRendering(App->score->currentScore.name, (SCREEN_WIDTH / 6) * 4 - nameText.w / 2, posY, entryColor);

			// Time column
			App->font_manager->DigitRendering(App->score->currentScore.timeMin, 2, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 - 32, posY, entryColor, true);
			App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 + 32 - 32, posY, &minutesMark, 0.0f, false, false, 2, 2, entryColor);
			App->font_manager->DigitRendering(App->score->currentScore.timeSec, 2, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 + 48 - 32, posY, entryColor, true);
			App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 + 80 - 32, posY, &secondsMark, 0.0f, false, false, 2, 2, entryColor);
			App->font_manager->DigitRendering(App->score->currentScore.timeDec, 2, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 + 96 - 32, posY, entryColor, true);
		}
		else 
		{
			//Rank column
			App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) - topRanks[i].w / 2, posY, &topRanks[i], 0.0f, false, false, 2, 2, entryColor);

			//Score column
			App->font_manager->DigitRendering(App->score->scoreEntries[rankNumber].score, 8, (SCREEN_WIDTH / 6) * 2 - 54, posY, entryColor);

			// Stage column
			App->font_manager->DigitRendering(App->score->scoreEntries[rankNumber].stage, 2, (SCREEN_WIDTH / 6) * 3 - stageText.w / 2 + 16, posY, entryColor);

			// Name column
			App->font_manager->StringRendering(App->score->scoreEntries[rankNumber].name, (SCREEN_WIDTH / 6) * 4 - nameText.w / 2, posY, entryColor);

			// Time column
			App->font_manager->DigitRendering(App->score->scoreEntries[rankNumber].timeMin, 2, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 - 32, posY, entryColor, true);
			App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 + 32 - 32, posY, &minutesMark, 0.0f, false, false, 2, 2, entryColor);
			App->font_manager->DigitRendering(App->score->scoreEntries[rankNumber].timeSec, 2, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 + 48 - 32, posY, entryColor, true);
			App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 + 80 - 32, posY, &secondsMark, 0.0f, false, false, 2, 2, entryColor);
			App->font_manager->DigitRendering(App->score->scoreEntries[rankNumber].timeDec, 2, (SCREEN_WIDTH / 6) * 5 - timeText.w / 2 + 96 - 32, posY, entryColor, true);

			rankNumber++;
		}
		Ymultiplier++;
	}

	if (App->score->entryInScoreTable == NULL && nameEntered == false) {
		App->font_manager->StringRendering("YOU.", (SCREEN_WIDTH / 6) - topRanks[0].w / 2, SCREEN_HEIGHT / 13 * (4 + Ymultiplier), { 255, 0, 0, 255 });
		App->font_manager->DigitRendering(App->score->currentScore.score, 8, (SCREEN_WIDTH / 6) * 2 - 54, SCREEN_HEIGHT / 13 * (4 + Ymultiplier), { 255, 0, 0, 255 });
	}

	//TODO: REMEMBER TO PUT nameEntered TO FALSE AND characterIndex AND nameCharacterIndex TO 0 EVERY TIME A NEW RACE STARTS
	if (App->score->entryInScoreTable != NULL && nameEntered == false) {
		NameEntry();
	}
}

void ModuleUI::NameEntry() {
	
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
			App->score->SaveScoreEntry();
			nameEntered = true;
		}
		else if (characterIndex == nameEntryString.size() - 2)
		{
			if (nameCharacterIndex != 0) {
				App->score->currentScore.name[nameCharacterIndex - 1] = ' ';
				nameCharacterIndex--;
			}
		}
		else
		{
			if (nameCharacterIndex < 3) {
				App->score->currentScore.name[nameCharacterIndex] = nameEntryString[characterIndex];
				nameCharacterIndex++;
			}
		}
	}
}