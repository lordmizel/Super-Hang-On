#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFont.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMapAfrica.h"
#include "ModulePlayer.h"
#include "Line.h"

ModuleSceneMapAfrica::ModuleSceneMapAfrica(bool active) : ModuleSceneTrack(active)
{
	background = { 17, 61, 640, 275 };
	backgroundParalax = { 668,98,625,28 };
	backgroundTrackName = { 266, 467,98,18 };


	grass1 = Color(224, 240, 160, 255);
	grass2 = Color(192, 192, 128, 255);
	rumble1 = Color(128, 128, 128, 255);
	rumble2 = Color(225, 225, 225, 255);
	color_road = Color(192, 192, 160, 255);
	color_line = Color(255, 255, 255, 255);


	for (int i = 0; i < 1600; i++)
	{
		Line line;
		line.z = (float)i * line.segL;

		//if (i > 300 && i < 700) line.curve = 4;

		//if (i > 0) line.y = (float)(sin(i / 30.0) * 1500);
		int dist = rand() % 3;
		int sign = rand() % 2 + 1;
		if (sign == 1) dist *= (-1);
		if (i % 20 == 0) line.spriteX = dist;

		lines.push_back(line);
	}

	N = lines.size();
	pos = 0;
	playerX = 0;
}

ModuleSceneMapAfrica::~ModuleSceneMapAfrica()
{}

