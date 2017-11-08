#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMusic.h"



ModuleSceneMusic::ModuleSceneMusic(bool active) : Module(active)
{
	animationSpeed = 0.07f;

	// Backdrop
	backdrop.x = 0;
	backdrop.y = 0;
	backdrop.w = SCREEN_WIDTH * 3;
	backdrop.h = SCREEN_HEIGHT * 3;

	// "Select music" text
	selectMusic.x = 6;
	selectMusic.y = 3;
	selectMusic.w = 96;
	selectMusic.h = 8;

	// Song1 animation
	song1.frames.push_back({ 4, 26, 248, 22 });
	song1.frames.push_back({ 0, 0, 0, 0 });
	song1.speed = animationSpeed;

	// Song1 animation
	song2.frames.push_back({ 4, 50, 248, 22 });
	song2.frames.push_back({ 0, 0, 0, 0 });
	song2.speed = animationSpeed;

	// Song1 animation
	song3.frames.push_back({ 4, 74, 248, 22 });
	song3.frames.push_back({ 0, 0, 0, 0 });
	song3.speed = animationSpeed;

	// Song1 animation
	song4.frames.push_back({ 4, 98, 248, 22 });
	song4.frames.push_back({ 0, 0, 0, 0 });
	song4.speed = animationSpeed;

	//  "Press start button" text
	pressButton.frames.push_back({ 115, 2, 136, 8 });
	pressButton.frames.push_back({ 0, 0, 0, 0 });
	pressButton.speed = 0.03f;

	selectedSong = SONG1;
	
}

ModuleSceneMusic::~ModuleSceneMusic()
{
}

bool ModuleSceneMusic::Start()
{
	LOG("Loading space intro");

	graphics = App->textures->Load("songs.png", 224, 160, 0);

	//App->audio->PlayMusic("opening.ogg", 1.0f);
	if (fx == 0)
		fx = App->audio->LoadFx("rtype/starting.wav");

	App->renderer->camera.x = App->renderer->camera.y = 0;

	return true;
}

// UnLoad assets
bool ModuleSceneMusic::CleanUp()
{
	LOG("Unloading scene");

	App->textures->Unload(graphics);

	if (fx == 0)
		fx = App->audio->LoadFx("rtype/starting.wav");

	return true;
}

// Update: draw background
update_status ModuleSceneMusic::Update()
{
	App->renderer->DrawQuad(backdrop, 224, 160, 0, 255, false);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 48, 30, &selectMusic);

	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 124, 60, &(song1.GetCurrentFrame()));
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 124, 90, &(song2.GetCurrentFrame()));
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 124, 120, &(song3.GetCurrentFrame()));
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 124, 150, &(song4.GetCurrentFrame()));

	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - 68, 200, &(pressButton.GetCurrentFrame()));

	switch (selectedSong) {
	case SONG1:
		song1.speed = animationSpeed;
		song2.Reset();
		song2.speed = 0.0f;
		song3.Reset();
		song2.speed = 0.0f;
		song4.Reset();
		song2.speed = 0.0f;
		break;
	case SONG2:
		song1.Reset();
		song1.speed = 0.0f;
		song2.speed = animationSpeed;
		song3.Reset();
		song3.speed = 0.0f;
		song4.Reset();
		song4.speed = 0.0f;
		break;
	case SONG3:
		song1.Reset();
		song1.speed = 0.0f;
		song2.Reset();
		song2.speed = 0.0f;
		song3.speed = animationSpeed;
		song4.Reset();
		song4.speed = 0.0f;
		break;
	case SONG4:
		song1.Reset();
		song1.speed = 0.0f;
		song2.Reset();
		song2.speed = 0.0f;
		song3.Reset();
		song4.speed = 0.0f;
		song4.speed = animationSpeed;
		break;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		if (selectedSong != SONG1)
		{
			selectedSong--;
		}
		else
		{
			selectedSong = SONG4;
		}
	}
	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		if (selectedSong != SONG4)
		{
			selectedSong++;
		}
		else
		{
			selectedSong = SONG1;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->fade->isFading() == false)
	{
		switch (selectedSong)
		{
		case SONG1:
			App->audio->musicChosen = "outrideACrisis.ogg";
			break;
		case SONG2:
			App->audio->musicChosen = "sprinter.ogg";
			break;
		case SONG3:
			App->audio->musicChosen = "winningRun.ogg";
			break;
		case SONG4:
			App->audio->musicChosen = "hardRoad.ogg";
			break;
		}
		App->fade->FadeToBlack((Module*)App->scene_race, this);
	}

	return UPDATE_CONTINUE;
}