#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFontManager.h"


ModuleFontManager::ModuleFontManager(bool active) : Module(active)
{
	//blankSpace = { 525, 280, 8, 8 };
	numbers[0] = { 374, 211, 8, 8 };
	numbers[1] = { 294, 211, 8, 8 };
	numbers[2] = { 302, 211, 8, 8 };
	numbers[3] = { 311, 211, 8, 8 };
	numbers[4] = { 320, 211, 8, 8 };
	numbers[5] = { 329, 211, 8, 8 };
	numbers[6] = { 338, 211, 8, 8 };
	numbers[7] = { 347, 211, 8, 8 };
	numbers[8] = { 356, 211, 8, 8 };
	numbers[9] = { 365, 211, 8, 8 };
}

ModuleFontManager::~ModuleFontManager()
{
}

// Load assets
bool ModuleFontManager::Start()
{
	LOG("Loading font manager");

	graphics = App->textures->Load("bikes.png", 255, 0, 204);

	return true;
}

// Unload assets
bool ModuleFontManager::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

void ModuleFontManager::PrintDigit(int digit, int x, int y, Color color)
{
	App->renderer->Blit(graphics, x, y, &numbers[digit], 0.0f, false, false, 2, 2);
}

