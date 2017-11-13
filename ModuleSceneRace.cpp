#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSceneRace.h"
#include "ModuleScore.h"
#include "ModuleRoad.h"


ModuleSceneRace::ModuleSceneRace(bool active) : Module(active)
{
	//Background
	backdrop.x = 330;
	backdrop.y = 256;
	backdrop.w = 320;
	backdrop.h = 128;
}

ModuleSceneRace::~ModuleSceneRace()
{}

// Load assets
bool ModuleSceneRace::Start()
{
	LOG("Loading race scene");
	
	graphics = App->textures->Load("backgrounds.png", 0, 0, 0);
	for (int i = 0; i < 50; i++) {
		roads.push_back(ModuleRoad(i));
	}

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();

	scoreBoard = new ModuleScore(true);											//ELIMINAR ESTO!!!!

	//App->audio->PlayMusic(App->audio->musicChosen, 1.0f);
	
	// TODO 15: create some colliders for the walls
	// solution wall coords: {0, 224, 3930, 16} {1375, 0, 111, 96} {1375, 145, 111, 96}

	return true;
}

// UnLoad assets
bool ModuleSceneRace::CleanUp()
{
	LOG("Unloading race scene");

 	App->textures->Unload(graphics);
	App->player->Disable();
	App->collision->Disable();
	App->particles->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneRace::Update()
{
	//for(ModuleRoad r : roads) {
		roads.at(0).Update();
	//}
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &backdrop);
	App->renderer->Blit(graphics, backdrop.w, 0, &backdrop);

	scoreBoard->ShowScore();
	
	return UPDATE_CONTINUE;
}