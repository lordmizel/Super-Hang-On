#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"


ModuleSceneIntro::ModuleSceneIntro(bool active) : Module(active)
{
	// SegaLogo
	segaLogo.frames.push_back({ 8, 63, 74, 25 });
	segaLogo.frames.push_back({ 8, 92, 74, 25 });
	segaLogo.frames.push_back({ 8, 121, 74, 25 });
	segaLogo.frames.push_back({ 8, 151, 74, 25 });
	segaLogo.frames.push_back({ 8, 182, 74, 25 });
	segaLogo.frames.push_back({ 8, 213, 74, 25 });
	segaLogo.frames.push_back({ 8, 244, 74, 25 });
	segaLogo.frames.push_back({ 8, 276, 74, 25 });
	segaLogo.frames.push_back({ 8, 306, 74, 25 });
	segaLogo.frames.push_back({ 9, 337, 74, 25 });
	segaLogo.frames.push_back({ 9, 367, 74, 25 });
	segaLogo.frames.push_back({ 9, 397, 74, 25 });
	segaLogo.frames.push_back({ 9, 427, 74, 25 });
	segaLogo.frames.push_back({ 9, 457, 74, 25 });
	segaLogo.speed = 0.3f;

	// HangOn Animation
	superHangOn.frames.push_back({ 125, 20, 266, 72 });
	superHangOn.frames.push_back({ 125, 96, 266, 72 });
	superHangOn.frames.push_back({ 125, 172, 266, 72 });
	superHangOn.frames.push_back({ 125, 249, 266, 72 });
	superHangOn.frames.push_back({ 125, 326, 266, 72 });
	superHangOn.frames.push_back({ 125, 403, 266, 72 });
	superHangOn.frames.push_back({ 125, 480, 266, 72 });
	superHangOn.frames.push_back({ 432, 20, 266, 72 });
	superHangOn.frames.push_back({ 432, 96, 266, 72 });
	superHangOn.frames.push_back({ 432, 172, 266, 72 });
	superHangOn.frames.push_back({ 432, 249, 266, 72 });
	superHangOn.frames.push_back({ 432, 326, 266, 72 });
	superHangOn.frames.push_back({ 432, 403, 266, 72 });
	superHangOn.speed = 0.2f;

	// Arrow animation
	arrow.frames.push_back({ 4, 4, 4, 6 });
	arrow.frames.push_back({ 1, 1, 1, 1 });
	arrow.speed = 0.1;

	// HangOn Letters
	titleLetters[0].x = 733;
	titleLetters[0].y = 253;
	titleLetters[0].w = 49;
	titleLetters[0].h = 42;
	titleLetters[1].x = 733;
	titleLetters[1].y = 294;
	titleLetters[1].w = 46;
	titleLetters[1].h = 42;
	titleLetters[2].x = 733;
	titleLetters[2].y = 335;
	titleLetters[2].w = 47;
	titleLetters[2].h = 42;
	titleLetters[3].x = 733;
	titleLetters[3].y = 376;
	titleLetters[3].w = 35;
	titleLetters[3].h = 42;
	titleLetters[4].x = 733;
	titleLetters[4].y = 417;
	titleLetters[4].w = 10;
	titleLetters[4].h = 42;
	titleLetters[5].x = 733;
	titleLetters[5].y = 458;
	titleLetters[5].w = 42;
	titleLetters[5].h = 42;
	titleLetters[6].x = 733;
	titleLetters[6].y = 499;
	titleLetters[6].w = 48;
	titleLetters[6].h = 42;

	// Title letter positions in X
	letterPositions[0] = SCREEN_WIDTH / 2 - 133;
	letterPositions[1] = letterPositions[0] + titleLetters[0].w - 9;
	letterPositions[2] = letterPositions[1] + titleLetters[1].w + 1;
	letterPositions[3] = letterPositions[2] + titleLetters[2].w - 4;
	letterPositions[4] = letterPositions[3] + titleLetters[3].w + 3;
	letterPositions[5] = letterPositions[4] + titleLetters[4].w - 1;
	letterPositions[6] = letterPositions[5] + titleLetters[5].w - 8;

	fill_n(currentLetterPosition, 7, SCREEN_WIDTH);

	// Trademark
	trademark.x = 128;
	trademark.y = 5;
	trademark.w = 89;
	trademark.h = 10;

	// Menu options
	menuOptions1.x = 16;
	menuOptions1.y = 3;
	menuOptions1.w = 62;
	menuOptions1.h = 22;
	menuOptions2.x = 15;
	menuOptions2.y = 35;
	menuOptions2.w = 102;
	menuOptions2.h = 22;

	selectedOption = NEW_GAME;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading space intro");
	
	graphics = App->textures->Load("menu.png", 0, 0, 0);

	//App->audio->PlayMusic("rtype/intro.ogg", 1.0f);
	if(fx == 0)
		fx = App->audio->LoadFx("rtype/starting.wav");

	App->renderer->camera.x = App->renderer->camera.y = 0;
	
	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading scene");

	App->textures->Unload(graphics);
	
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if (currentMovingLetter < 7) {
		for (int i = 0; i < 7; i++) {
			App->renderer->Blit(graphics, currentLetterPosition[i], 71, &titleLetters[i]);
		}
		currentLetterPosition[currentMovingLetter] -= letterSpeed;
		if (currentLetterPosition[currentMovingLetter] < letterPositions[currentMovingLetter]) {
			currentLetterPosition[currentMovingLetter] = letterPositions[currentMovingLetter];
			currentMovingLetter++;
		}
	}
	else
	{
		App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 133, 40, &(superHangOn.GetCurrentFrame()));

		if (selectedOption == NEW_GAME || selectedOption == PASSWORD) {
			App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 31, 150, &menuOptions1);
			if (selectedOption == NEW_GAME) {
				App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 40, 150, &(arrow.GetCurrentFrame()));
			}
			else if (selectedOption == PASSWORD) 
			{
				App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 40, 166, &(arrow.GetCurrentFrame()));
			}
		}
		else if (selectedOption == ARCADE_MODE || selectedOption == ORIGINAL_MODE)
		{
			App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 51, 150, &menuOptions2);
			if (selectedOption == ARCADE_MODE) {
				App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 60, 150, &(arrow.GetCurrentFrame()));
			}
			else if (selectedOption == ORIGINAL_MODE)
			{
				App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 60, 166, &(arrow.GetCurrentFrame()));
			}
		}

		App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 37, SCREEN_HEIGHT / 2 + 75, &(segaLogo.GetCurrentFrame()));
		App->renderer->Blit(graphics, SCREEN_WIDTH - trademark.w, SCREEN_HEIGHT - trademark.h, &trademark);

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN /*&& App->fade->isFading() == false*/)
		{
			switch (selectedOption) {
			case NEW_GAME:
				selectedOption = ARCADE_MODE;
				break;
			case PASSWORD:
				App->audio->PlayFx(fx);
				break;
			case ARCADE_MODE:
				App->fade->FadeToBlack((Module*)App->scene_map, this);
				break;
			case ORIGINAL_MODE:
				App->audio->PlayFx(fx);
				break;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		{
			switch (selectedOption) {
			case NEW_GAME:
				selectedOption = PASSWORD;
				break;
			case PASSWORD:
				selectedOption = NEW_GAME;
				break;
			case ARCADE_MODE:
				selectedOption = ORIGINAL_MODE;
				break;
			case ORIGINAL_MODE:
				selectedOption = ARCADE_MODE;
				break;
			}
		}
	}

	return UPDATE_CONTINUE;
}