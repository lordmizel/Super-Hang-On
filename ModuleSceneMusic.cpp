#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMap.h"
#include "ModuleSceneMusic.h"
#include "ModuleFontManager.h"


ModuleSceneMusic::ModuleSceneMusic(bool active) : Module(active)
{
	animationSpeed = 0.07f;

	// Backdrop
	backdrop = { 0, 0, SCREEN_WIDTH * 3, SCREEN_HEIGHT * 3 };

	// "Select music" text
	selectMusic = { 6, 3, 96, 8 };

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

}

ModuleSceneMusic::~ModuleSceneMusic()
{
}

bool ModuleSceneMusic::Start()
{
	LOG("Loading space intro");

	graphics = App->textures->Load("Game/songs.png", 224, 160, 0);

	App->audio->PlayMusic("Game/outRideACrisis.ogg", 1.0f);
	if (fx == 0) {
		fx = App->audio->LoadFx("Game/starting.wav");
	}

	App->renderer->camera.x = App->renderer->camera.y = 0;

	selectedSong = SONG1;

	timer_.SetTime(10);
	timer_.Start();

	return true;
}

// UnLoad assets
bool ModuleSceneMusic::CleanUp()
{
	LOG("Unloading scene");

	App->textures->Unload(graphics);

	if (fx == 0) 
	{
		fx = App->audio->LoadFx("Game/starting.wav");
	}
		

	timer_.Update();

	return true;
}

// Update: draw background
update_status ModuleSceneMusic::Update()
{
	App->renderer->DrawQuad(backdrop, 224, 160, 0, 255, false);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - selectMusic.w, SCREEN_HEIGHT / 8, &selectMusic, 0.0f, false, false, 2, 2);

	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - song1.frames[0].w, SCREEN_HEIGHT / 8 * 2, &(song1.GetCurrentFrame()), 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - song2.frames[0].w, SCREEN_HEIGHT / 8 * 3, &(song2.GetCurrentFrame()), 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - song3.frames[0].w, SCREEN_HEIGHT / 8 * 4, &(song3.GetCurrentFrame()), 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - song4.frames[0].w, SCREEN_HEIGHT / 8 * 5, &(song4.GetCurrentFrame()), 0.0f, false, false, 2, 2);

	App->font_manager->DigitRendering(static_cast<int>(timer_.GetRemainingTime()), 2, SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT / 7 * 5, Color{ 255,255,255,255 }, false, true);

	App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - pressButton.frames[0].w, SCREEN_HEIGHT / 7 * 6, &(pressButton.GetCurrentFrame()), 0.0f, false, false, 2, 2);

	switch (selectedSong) 
	{
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

	if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) && App->fade->isFading() == false)
	{
		if (selectedSong != SONG1)
		{
			selectedSong--;
		}
		else
		{
			selectedSong = SONG4;
		}
		ChangeSongPlaying();
	}
	else if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) && App->fade->isFading() == false)
	{
		if (selectedSong != SONG4)
		{
			selectedSong++;
		}
		else
		{
			selectedSong = SONG1;
		}
		ChangeSongPlaying();
	}
	if ((App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->fade->isFading() == false) || (timer_.IsExpired() && App->fade->isFading() == false))
	{
		switch (selectedSong)
		{
		case SONG1:
			App->audio->musicChosen = "Game/outrideACrisis.ogg";
			break;
		case SONG2:
			App->audio->musicChosen = "Game/sprinter.ogg";
			break;
		case SONG3:
			App->audio->musicChosen = "Game/winningRun.ogg";
			break;
		case SONG4:
			App->audio->musicChosen = "Game/hardRoad.ogg";
			break;
		}

		App->audio->MusicFadeOut(1);

		switch (App->scene_map->GetSelectedCourse()) 
		{
		case (courseSelect::AFRICA):
		case (courseSelect::ASIA):
		case (courseSelect::AMERICA):
		case (courseSelect::EUROPE):
			App->fade->FadeToBlack((Module*)App->europe_race, this);
			break;
		}
	}

	timer_.Update();

	return UPDATE_CONTINUE;
}

void ModuleSceneMusic::ChangeSongPlaying() 
{
	switch (selectedSong)
	{
	case SONG1:
		App->audio->PlayMusic("Game/outRideACrisis.ogg", 0.0f);
		break;
	case SONG2:
		App->audio->PlayMusic("Game/sprinter.ogg", 0.0f);
		break;
	case SONG3:
		App->audio->PlayMusic("Game/winningRun.ogg", 0.0f);
		break;
	case SONG4:
		App->audio->PlayMusic("Game/hardRoad.ogg", 0.0f);
		break;
	}
}