#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMap.h"
#include "ModuleFontManager.h"
#include "ModulePlayer.h"
#include "ModuleEuropeRace.h"
#include "ModuleUI.h"

ModuleSceneMap::ModuleSceneMap(bool active) : Module(active)
{
	// Backdrop
	backdrop = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// World map
	worldMap = { 1, 41, 280, 165 };

	// "Choose your class" message
	chooseClass = { 3, 3, 136, 8 };

	// Africa
	africa.frames.push_back({ 294, 2, 52, 56 });
	africa.frames.push_back({ 0, 0, 0, 0 });
	africa.speed = 0.05f;
	// Asia
	asia.frames.push_back({ 420, 52, 116, 137 });
	asia.frames.push_back({ 0, 0, 0, 0 });
	asia.speed = 0.05f;
	// America
	america.frames.push_back({ 283, 61, 97, 128 });
	america.frames.push_back({ 0, 0, 0, 0 });
	america.speed = 0.05f;
	// Europe
	europe.frames.push_back({ 349, 4, 56, 48 });
	europe.frames.push_back({ 0, 0, 0, 0 });
	europe.speed = 0.05f;

	// Africa text
	courseAfrica = { 142, 3, 71, 16 };
	// Asia text
	courseAsia = { 142, 21, 71, 16 };
	// America text
	courseAmerica = { 215, 3, 71, 16 };
	// Europe text
	courseEurope = { 215, 21, 71, 16 };

	// "Press button" animation
	pressButton.frames.push_back({ 3, 14, 136, 8 });
	pressButton.frames.push_back({ 0, 0, 0, 0 });
	pressButton.speed = 0.03f;
}

ModuleSceneMap::~ModuleSceneMap()
{
}

bool ModuleSceneMap::Start()
{
	LOG("Loading race intro");

	App->player->Disable();
	App->ui->Disable();
	App->europe_race->Disable();

	graphics = App->textures->Load("Game/bikes.png", 255, 0, 204);

	App->audio->PlayMusic("Game/opening.ogg", 1.0f);

	if (fx == 0)
		fx = App->audio->LoadFx("Game/rtype/starting.wav");

	App->renderer->camera.x = App->renderer->camera.y = 0;

	timer_.SetTime(10);
	timer_.Start();

	return true;
}

// UnLoad assets
bool ModuleSceneMap::CleanUp()
{
	LOG("Unloading scene");

	App->textures->Unload(graphics);

	if (fx == 0)
		fx = App->audio->LoadFx("Game/rtype/starting.wav");

	return true;
}

// Update: draw background
update_status ModuleSceneMap::Update()
{
	App->renderer->DrawQuad(backdrop, 160, 192, 224, 255, false);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - worldMap.w, SCREEN_HEIGHT / 2 - worldMap.h, &worldMap, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - chooseClass.w, SCREEN_HEIGHT / 8, &chooseClass, 0.0f, false, false, 2, 2);

	switch (courseSelect) 
	{
	case AFRICA:
		App->renderer->Blit(graphics, 284, 221, &(africa.GetCurrentFrame()), 0.0f, false, false, 2, 2);
		break;
	case ASIA:
		App->renderer->Blit(graphics, 356, 91, &(asia.GetCurrentFrame()), 0.0f, false, false, 2, 2);
		break;
	case AMERICA:
		App->renderer->Blit(graphics, 60, 125, &(america.GetCurrentFrame()), 0.0f, false, false, 2, 2);
		break;
	case EUROPE:
		App->renderer->Blit(graphics, 276, 125, &(europe.GetCurrentFrame()), 0.0f, false, false, 2, 2);
		break;
	}

	App->renderer->Blit(graphics, 276, 253, &courseAfrica, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, 406, 125, &courseAsia, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, 102, 189, &courseAmerica, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, 278, 157, &courseEurope, 0.0f, false, false, 2, 2);

	App->font_manager->DigitRendering(static_cast<int>(timer_.GetRemainingTime()), 2, SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT / 7 * 5, Color{ 255,255,255,255 }, false, true);

	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - pressButton.frames[0].w, SCREEN_HEIGHT / 7 * 6, &(pressButton.GetCurrentFrame()), 0.0f, false, false, 2, 2);
	
	// Force the user to choose Europe
	if (timer_.IsExpired() && App->fade->isFading() == false) {
		App->fade->FadeToBlack((Module*)App->scene_music, this);
	}

	if ((App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->fade->isFading() == false) || (timer_.IsExpired() && App->fade->isFading() == false))
	{
		switch (courseSelect) 
		{
		case AFRICA:
		case ASIA:
		case AMERICA:
			App->audio->PlayFx(fx);
			break;
		case EUROPE:
			App->fade->FadeToBlack((Module*)App->scene_music, this);
			break;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) 
	{
		africa.Reset();
		asia.Reset();
		america.Reset();
		europe.Reset();
		if (courseSelect != AFRICA) 
		{
			courseSelect--;
		}
		else
		{
			courseSelect = EUROPE;
		}
	}
	else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) 
	{
		africa.Reset();
		asia.Reset();
		america.Reset();
		europe.Reset();
		if (courseSelect != EUROPE)
		{
			courseSelect++;
		}
		else
		{
			courseSelect = AFRICA;
		}
	}

	timer_.Update();

	return UPDATE_CONTINUE;
}
