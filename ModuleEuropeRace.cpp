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
	landscapeParis = { 8, 197, 320, 74 };
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
	biomes.push_back(alpine = biome(Color(0, 224, 96, 255), Color(0, 192, 64, 255),
		Color(192, 192, 192, 255), Color(64, 64, 64, 255),
		Color(64, 64, 64, 255), Color(64, 224, 224, 225),
		landscapeAlpine, alpineMountains));
	biomes.push_back(windmills = biome(Color(160, 200, 64, 255), Color(128, 192, 32, 255),
		Color(224, 192, 224, 255), Color(96, 64, 64, 255),
		Color(96, 64, 64, 255), Color(192, 224, 224, 225),
		landscapeWindmills, windmillVillage));
	biomes.push_back(sunset = biome(Color(224, 160, 0, 255), Color(192, 128, 0, 255),
		Color(224, 192, 192, 255), Color(64, 32, 32, 255),
		Color(64, 64, 64, 255), Color(224, 64, 0, 225),
		landscapeSunset, sunsetBuildings));
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
		line.y += currentAltitude + altitudeVariation;
		currentAltitude = line.y;

		LOG("Altitude variation: %f", altitudeVariation)

		line.curve = 0;
		if (i > 300 && i < 700) line.curve = 4;
		if (i > 500 && i < 600) line.curve = -1;

		//if (i > 0) line.y = (float)(sin(i / 30.0) * 1500);
		if (i > 800 && i < 1100) {
			ChangeAltitude(altitudeVariation, 110.0f, i, 800, 1100);
		}

		if (i > 1100 && i < 1500) {
			ChangeAltitude(altitudeVariation, -50.0f, i, 1100, 1500);
		}

		int dist = rand() % 3;
		int sign = rand() % 2 + 1;

		if (sign == 1) {
			dist *= (-1);
		}

		if (i == 300) { line.atrezzos.push_back(make_pair(deadTree, 2)); }
		if (i == 400) { line.atrezzos.push_back(make_pair(discoNora, 1)); }
		if (i == 500) { line.atrezzos.push_back(make_pair(palmLeft, -2)); }

		lines.push_back(line);
	}

	

	N = lines.size();
	pos = 0;
}

ModuleEuropeRace::~ModuleEuropeRace()
{
}