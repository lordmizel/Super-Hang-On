#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFontManager.h"
#include <string>

using namespace std;

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

	numbersBig[0] = { 119, 129, 8, 14 };
	numbersBig[1] = { 109, 129, 8, 14 };
	numbersBig[2] = { 99, 129, 8, 14 };
	numbersBig[3] = { 88, 129, 8, 14 };
	numbersBig[4] = { 77, 129, 8, 14 };
	numbersBig[5] = { 66, 129, 8, 14 };
	numbersBig[6] = { 55, 129, 8, 14 };
	numbersBig[7] = { 44, 129, 8, 14 };
	numbersBig[8] = { 33, 129, 8, 14 };
	numbersBig[9] = { 22, 129, 8, 14 };

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
	graphics2 = App->textures->Load("songs.png", 224, 160, 0);

	return true;
}

// Unload assets
bool ModuleFontManager::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);

	return true;
}

void ModuleFontManager::DigitRendering(int numberToRender, int numDigits, int x, int y, Color color, bool fillWithZero, bool big)
{
	int numberThreshold = 1;

	for (int i = 0; i < numDigits - 1; i++) {
		numberThreshold *= 10;
	}

	int helper = numberToRender;
	int digitPositionX = 0;
	bool numberInRange = false;

	for (int dig = numDigits; dig > 0; dig--) {
		if (helper < numberThreshold && !numberInRange && dig > 1) {
			if (!fillWithZero) {
				App->renderer->Blit(graphics, x + digitPositionX, y, &blankSpace, 0.0f, false, false, 2, 2);
			}
			else {
				PrintDigit(0, x + digitPositionX, y, color, big);
			}
		}
		else
		{
			PrintDigit(helper / numberThreshold, x + digitPositionX, y, color, big);
			numberInRange = true;
		}

		helper = helper % numberThreshold;
		numberThreshold = numberThreshold / 10;
		digitPositionX += 16;
	}
}

void ModuleFontManager::StringRendering(string stringToRender, int x, int y, Color color) {
	int digitPositionX = 0;
	for (unsigned int c = 0; c < stringToRender.size(); c++) {
		App->font_manager->PrintChar(stringToRender.at(c), x + digitPositionX, y, color);
		digitPositionX += 16;
	}
}

void ModuleFontManager::PrintDigit(int digit, int x, int y, Color color, bool big)
{
	if (!big) {
		App->renderer->Blit(graphics, x, y, &numbers[digit], 0.0f, false, false, 2, 2, color);
	}
	else {
		App->renderer->Blit(graphics2, x, y, &numbersBig[digit], 0.0f, false, false, 2, 2, color);
	}
}

void ModuleFontManager::PrintChar(char c, int x, int y, Color color) 
{
	App->renderer->Blit(graphics, x, y, &characters[c], 0.0f, false, false, 2, 2, color);
}