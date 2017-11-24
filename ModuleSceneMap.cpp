#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMap.h"


ModuleSceneMap::ModuleSceneMap(bool active) : Module(active)
{
	// Backdrop
	backdrop.x = 0;
	backdrop.y = 0;
	backdrop.w = SCREEN_WIDTH * 3;
	backdrop.h = SCREEN_HEIGHT * 3;

	// World map
	worldMap.x = 1;
	worldMap.y = 41;
	worldMap.w = 280;
	worldMap.h = 165;

	// "Choose your class" message
	chooseClass.x = 3;
	chooseClass.y = 3;
	chooseClass.w = 136;
	chooseClass.h = 8;

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
	courseAfrica.x = 142;
	courseAfrica.y = 3;
	courseAfrica.w = 71;
	courseAfrica.h = 16;
	// Asia text
	courseAsia.x = 142;
	courseAsia.y = 21;
	courseAsia.w = 71;
	courseAsia.h = 16;
	// America text
	courseAmerica.x = 215;
	courseAmerica.y = 3;
	courseAmerica.w = 71;
	courseAmerica.h = 16;
	// Europe text
	courseEurope.x = 215;
	courseEurope.y = 21;
	courseEurope.w = 71;
	courseEurope.h = 16;

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

	graphics = App->textures->Load("bikes.png", 255, 0, 204);

	App->audio->PlayMusic("opening.ogg", 1.0f);
	if (fx == 0)
		fx = App->audio->LoadFx("rtype/starting.wav");

	App->renderer->camera.x = App->renderer->camera.y = 0;

	return true;
}

// UnLoad assets
bool ModuleSceneMap::CleanUp()
{
	LOG("Unloading scene");

	App->textures->Unload(graphics);

	if (fx == 0)
		fx = App->audio->LoadFx("rtype/starting.wav");

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

	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - pressButton.frames[0].w, SCREEN_HEIGHT / 7 * 6, &(pressButton.GetCurrentFrame()), 0.0f, false, false, 2, 2);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->fade->isFading() == false) 
	{
		switch (courseSelect) 
		{
		case AFRICA:
			App->fade->FadeToBlack((Module*)App->scene_music, this);
			break;
		case ASIA:
			App->audio->PlayFx(fx);
			break;
		case AMERICA:
			App->audio->PlayFx(fx);
			break;
		case EUROPE:
			App->audio->PlayFx(fx);
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

	return UPDATE_CONTINUE;
}
