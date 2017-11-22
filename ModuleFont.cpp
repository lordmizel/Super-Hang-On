#include "Globals.h"
#include "Application.h"
#include "ModuleFont.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"


ModuleFont::ModuleFont()
{}

// Destructor
ModuleFont::~ModuleFont()
{}

unsigned int ModuleFont::LoadMedia(const char* filePath, const char* formatFont, unsigned int fontWidth, unsigned int fontHeigth, unsigned int initY)
{
	//Loading success flag
	bool success = true;
	Font font;
	//Load splash image
	font.surface = App->textures->Load(filePath, 255, 255, 255);
	font.y = initY;
	if (font.surface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", filePath, SDL_GetError());
		success = false;
	}
	font.width = fontWidth;
	font.heigth = fontHeigth;
	for (unsigned int i = 0; formatFont[i] != '\0'; i++) {
		font.fontMap[formatFont[i]] = i*fontWidth;
	}
	fonts.push_back(font);
	return fonts.size() -1;
}