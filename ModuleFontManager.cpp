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

	characters['A'] = { 508, 280, 8, 8 };
	characters['B'] = { 508, 289, 8, 8 };
	characters['C'] = { 508, 298, 8, 8 };
	characters['D'] = { 508, 307, 8, 8 };
	characters['E'] = { 508, 316, 8, 8 };
	characters['F'] = { 508, 325, 8, 8 };
	characters['G'] = { 508, 334, 8, 8 };
	characters['H'] = { 508, 343, 8, 8 };
	characters['I'] = { 508, 352, 8, 8 };
	characters['J'] = { 508, 361, 8, 8 };
	characters['K'] = { 508, 370, 8, 8 };
	characters['L'] = { 508, 379, 8, 8 };
	characters['M'] = { 508, 388, 8, 8 };
	characters['N'] = { 508, 397, 8, 8 };
	characters['O'] = { 508, 406, 8, 8 };
	characters['P'] = { 508, 415, 8, 8 };
	characters['Q'] = { 508, 424, 8, 8 };
	characters['R'] = { 508, 433, 8, 8 };
	characters['S'] = { 508, 442, 8, 8 };
	characters['T'] = { 508, 451, 8, 8 };
	characters['U'] = { 508, 460, 8, 8 };
	characters['V'] = { 508, 469, 8, 8 };
	characters['W'] = { 508, 478, 8, 8 };
	characters['X'] = { 508, 487, 8, 8 };
	characters['Y'] = { 508, 496, 8, 8 };
	characters['Z'] = { 508, 505, 8, 8 };
	characters['.'] = { 508, 514, 8, 8 };
	characters['<'] = { 508, 523, 8, 8 };
	characters['/'] = { 508, 532, 8, 8 };
	characters[' '] = { 508, 270, 8, 8 };
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
	App->renderer->Blit(graphics, x, y, &numbers[digit], 0.0f, false, false, 2, 2, color);
}

void ModuleFontManager::PrintChar(char c, int x, int y, Color color) 
{
	App->renderer->Blit(graphics, x, y, &characters[c], 0.0f, false, false, 2, 2, color);
}