#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEuropeRace.h"
#include "ModulePlayer.h"
#include "Segment.h"

ModuleEuropeRace::ModuleEuropeRace(bool active) : ModuleSceneRace(active)
{
	landscapeParis = { 330, 256, 320, 128 };
	parisBuildings = { 0, 0, 0, 0 };
	landscapeSea = { 330, 484, 320, 128 };
	seaRocks = { 0, 0, 0, 0 };

	biomes.push_back(paris = biome(Color(160, 160, 160, 255), Color(128, 128, 128, 255),
		Color(224, 224, 224, 255), Color(96, 96, 96, 255),
		Color(32, 32, 32, 255), Color(224, 224, 224, 225),
		landscapeParis, parisBuildings));
	biomes.push_back(coast = biome(Color(224, 224, 64, 255), Color(224, 224, 64, 255),
		Color(224, 224, 224, 255), Color(128, 128, 128, 255),
		Color(192, 192, 192, 255), Color(32, 0, 224, 225),
		landscapeParis, parisBuildings));

	biomes.push_back(sunset = biome(Color(224, 160, 0, 255), Color(192, 128, 0, 255),
		Color(224, 192, 192, 255), Color(64, 32, 32, 255),
		Color(64, 64, 64, 255), Color(224, 64, 0, 225),
		landscapeSunset, sunsetBuildings));
	biomes.push_back(alpine = biome(Color(0, 224, 96, 255), Color(0, 192, 64, 255),
		Color(192, 192, 192, 255), Color(64, 64, 64, 255),
		Color(64, 64, 64, 255), Color(64, 224, 224, 225),
		landscapeAlpine, alpineMountains));
	biomes.push_back(windmills = biome(Color(160, 224, 64, 255), Color(128, 192, 32, 255),
		Color(224, 192, 224, 255), Color(96, 64, 64, 255),
		Color(96, 64, 64, 255), Color(192, 224, 224, 225),
		landscapeWindmills, windmillVillage));
	biomes.push_back(city = biome(Color(0, 0, 32, 255), Color(0, 0, 32, 255),
		Color(224, 224, 128, 255), Color(0, 0, 96, 255),
		Color(0, 0, 96, 255), Color(0, 0, 0, 225),
		landscapeCity, cityBuildings));
	

	biomeBorders.push_back(1000);
	biomeBorders.push_back(2000);
	biomeBorders.push_back(3000);
	biomeBorders.push_back(4000);
	biomeBorders.push_back(5000);
	biomeBorders.push_back(6000);
	biomeBorders.push_back(NULL);
	
	currentBiome = biomes[biomeIndex];

	for (int i = 0; i <10000; i++)
	{
		Segment line;
		line.z = (float)i * SEGMENT_LENGTH;

		line.curve = 0;
		if (i > 300 && i < 700) line.curve = 4;
		//if (i > 500 && i < 600) line.curve = -4;
		if (i > 500 && i < 600) line.curve = -1;

		//if (i > 0) line.y = (float)(sin(i / 30.0) * 10000);
		//if (i > 0) line.y = (float)(sin(i / 30.0) * 1500);

		//if (i >= 0 && i < 500) biomeIndex = 0;
		//if (i >= 500 && i < 1000) biomeIndex = 1;
		//if (i >= 1000 && i < 1500) biomeIndex = 2;
		//if (i >= 1500 /*&& i < 500*/) biomeIndex = 3;

		int dist = rand() % 3;
		int sign = rand() % 2 + 1;

		if (sign == 1) {
			dist *= (-1);
		}

		if (i == 200) {
			line.spriteX = 2;
		}

		lines.push_back(line);
	}

	

	N = lines.size();
	pos = 0;
}

ModuleEuropeRace::~ModuleEuropeRace()
{
}