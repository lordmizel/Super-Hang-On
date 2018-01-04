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
	lapRecordsFile = "Game/europelaps.txt";
	trackProgressBar = { 17, 234, 112, 8 };
	yellowBarLength = 188;

	goalPoint = 12200;

	landscapeParis = { 8, 197, 320, 74 };
	parisBuildings = { 336, 104, 320, 15 };
	landscapeAlpine = { 677, 3, 320, 61 };
	alpineMountains = { 336, 352, 320, 21 };
	landscapeWindmills = { 677, 358, 320, 43 };
	windmillVillage = { 335, 378, 320, 21 };
	landscapeSunset = { 677, 251, 320, 39 };
	sunsetBuildings = { 335, 333, 320, 16 };
	landscapeCity = { 677,404,320,39 };
	cityBuildings = { 335, 405,320,15 };

	biomes.push_back(paris = biome(Color(160, 160, 160, 255), Color(128, 128, 128, 255),
		Color(224, 224, 224, 255), Color(96, 96, 96, 255),
		Color(32, 32, 32, 255), Color(224, 224, 224, 225),
		landscapeParis, parisBuildings));
	biomes.push_back(alpine = biome(Color(0, 224, 96, 255), Color(0, 192, 64, 255),
		Color(192, 192, 192, 255), Color(64, 64, 64, 255),
		Color(64, 64, 64, 255), Color(224, 224, 224, 225),
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
	
	biomeBorders.push_back(1700);	//Alpine
	biomeBorders.push_back(3900);	//Windmills
	biomeBorders.push_back(6000);	//Sunset
	biomeBorders.push_back(8500);	//City
	biomeBorders.push_back(99999);	//Needed to avoid bug
	
	currentBiome = biomes[biomeIndex];

	checkPoints.push_back(1300);
	checkPoints.push_back(3300);
	checkPoints.push_back(5600);
	checkPoints.push_back(7900);
	checkPoints.push_back(10000);

	for (int i = 0; i <13000; i++)
	{
		Segment segment;
		segment.z = (float)i * SEGMENT_LENGTH;
		segment.y += currentAltitude + altitudeVariation;
		currentAltitude = segment.y;

		segment.curve = 0;

		//First part (0-1300) - Paris
		if (i == 30) segment.atrezzos.push_back(make_pair(startSign, -3.0f));
		if (i == 30) segment.atrezzos.push_back(make_pair(rightLegOfSign, -3.0f));
		if (i == 29) segment.atrezzos.push_back(make_pair(semaphore, -2.0f));

		if (i > 300 && i < 700) segment.curve = 4;
		if (i > 500 && i < 600) segment.curve = -1;
		if (i > 900 && i < 1100) segment.curve = 1;
		if (i > 1100 && i < 1200) segment.curve = -1;
		if (i > 1200 && i < 1300) segment.curve = 1;

		if (i > 400 && i < 600) ChangeAltitude(altitudeVariation, -50.0f, i, 400, 600);
		if (i > 800 && i < 900) ChangeAltitude(altitudeVariation, 150.0f, i, 800, 900);

		for (int j = 50; j <= 1250; j += 60) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(retroLamp, -2.4f));
				segment.atrezzos.push_back(make_pair(retroLamp, 2.0f));
				break;
			}
		}
		for (int j = 200; j <= 300; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(arrowRight, -2.0f));
				break;
			}
		}
		if (i == 1025) segment.atrezzos.push_back(make_pair(streetMirror, -2.0f));
		if (i == 1025) segment.atrezzos.push_back(make_pair(streetMirror, -2.0f));
		if (i == 1175) segment.atrezzos.push_back(make_pair(phoneBooth, 2.0f));
		for (int j = 1300; j <= 1400; j += 40) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(discoNora, -2.5f));
				segment.atrezzos.push_back(make_pair(arrowLeft, 1.5f));
				break;
			}
		}


		//Second part (1300 - 3300) - Paris to Alpine
		if (i > 1400 && i < 1500) segment.curve = -3;
		if (i > 1600 && i < 1700) segment.curve = -3;
		if (i > 1800 && i < 2400) segment.curve = 4;
		if (i > 2500 && i < 2600) segment.curve = -1;
		if (i > 2800 && i < 2900) segment.curve = 2;
		if (i > 3100 && i < 3350) segment.curve = 3;

		if (i > 1550 && i < 2100) ChangeAltitude(altitudeVariation, 180.0f, i, 1550, 2100);
		if (i > 2000 && i < 2500) ChangeAltitude(altitudeVariation, -20.0f, i, 2000, 2500);
		if (i > 2600 && i < 2800) ChangeAltitude(altitudeVariation, -40.0f, i, 2600, 2800);
		if (i > 3100 && i < 3300) ChangeAltitude(altitudeVariation, 20.0f, i, 3100, 3300);

		if (i == 1500) segment.atrezzos.push_back(make_pair(bridalStone, -4.0f));
		if (i == 1500) segment.atrezzos.push_back(make_pair(bridalStone, 2.0f));
		for (int j = 1520; j <= 1650; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(streetMirror, 1.5f));
				break;
			}
		}
		for (int j = 1300; j <= 1400; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(arrowLeft, 1.5f));
				break;
			}
		}
		for (int j = 1500; j <= 1600; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(arrowLeft, 1.5f));
				break;
			}
		}
		for (int j = 1800; j <= 2400; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(arrowRight, -2.0f));
				break;
			}
		}
		for (int j = 1800; j < 2700; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(smallTree, -6.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (-2.5f - (-6.0f))))));
				segment.atrezzos.push_back(make_pair(smallTree, 2.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6.0f - 2.0f)))));
				break;
			}
		}
		for (int j = 1800; j < 2700; j += 55) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(tallTree, -6.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (-2.5f - (-6.0f))))));
				segment.atrezzos.push_back(make_pair(tallTree, 2.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6.0f - 2.0f)))));
				break;
			}
		}
		for (int j = 2750; j < 2900; j += 40) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(morobare, -3.5f));
				segment.atrezzos.push_back(make_pair(morobare, 2.0f));
				break;
			}
		}
		for (int j = 3000; j < 3900; j += 40) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(smallTree, -6.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (-2.5f - (-6.0f))))));
				segment.atrezzos.push_back(make_pair(smallTree, 1.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6.0f - 2.0f)))));
				break;
			}
		}
		for (int j = 3000; j < 3900; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(bigRock, -6.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (-2.5f - (-6.0f))))));
				segment.atrezzos.push_back(make_pair(bigRock, 1.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (6.0f - 1.5f)))));
				break;
			}
		}


		//Third Part (3300 - 5600) - Alpine to Windmills
		if (i > 3500 && i < 3650) segment.curve = -0.5f;
		if (i > 3900 && i < 4100) segment.curve = -4;
		if (i > 4750 && i < 6350) segment.curve = 2;
		if (i > 4800 && i < 5100) segment.curve = -2;
		if (i > 5400 && i < 5700) segment.curve = -2;

		if (i > 3300 && i < 3400) ChangeAltitude(altitudeVariation, -40.0f, i, 3300, 3400);
		if (i > 3800 && i < 4200) ChangeAltitude(altitudeVariation, 130.0f, i, 3800, 4200);
		if (i > 4800 && i < 5300) ChangeAltitude(altitudeVariation, -20.0f, i, 4800, 5300);
		for (int j = 3800; j <= 3900; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(arrowLeft, 1.5f));
				break;
			}
		}
		for (int j = 4200; j <= 5500; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(tallTree, -2.5f));
				segment.atrezzos.push_back(make_pair(tallTree, 1.5f));
				break;
			}
		}


		//Fourth part (5600 - 7900) - Windmills to Sunset
		if (i > 5600 && i < 5800) segment.curve = 2;
		if (i > 5900 && i < 6200) segment.curve = -2;
		if (i > 6400 && i < 6700) segment.curve = 0.5f;
		if (i > 6800 && i < 7000) segment.curve = -0.5;
		if (i > 7200 && i < 7800) segment.curve = -4;
		
		if (i > 5800 && i < 6300) ChangeAltitude(altitudeVariation, 170.0f, i, 5800, 6300);
		if (i > 6700 && i < 7200) ChangeAltitude(altitudeVariation, 50.0f, i, 6500, 7200);

		for (int j = 5800; j <= 5900; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(arrowLeft, 1.5f));
				break;
			}
		}
		for (int j = 5900; j <= 6000; j += 50) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(birdBird, 1.5f));
				segment.atrezzos.push_back(make_pair(birdBird, -3.0f));
				break;
			}
		}
		for (int j = 6100; j <= 6300; j += 50) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(nokSparkPlugs, 1.5f));
				segment.atrezzos.push_back(make_pair(nokSparkPlugs, -3.0f));
				break;
			}
		}
		for (int j = 6500; j <= 6600; j += 20) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(rustyDrum, -2.0f));
				break;
			}
		}
		for (int j = 6700; j <= 6800; j += 20) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(rustyDrum, 1.5f));
				break;
			}
		}
		for (int j = 7000; j <= 8400; j += 50) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(palmRight, 1.3f));
				segment.atrezzos.push_back(make_pair(palmLeft, -2.3f));
				break;
			}
		}
		for (int j = 7100; j <= 7200; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(arrowLeft, 1.5f));
				break;
			}
		}
		if (i == 7500) segment.atrezzos.push_back(make_pair(phoneBooth, 2.0f));
		

		//Fifth part (7900 - 10200) - Sunset to City
		if (i > 8000 && i < 8100) segment.curve = -0.5f;
		if (i > 8100 && i < 8200) segment.curve = 0.5f;
		if (i > 8200 && i < 8300) segment.curve = -3;
		if (i > 8300 && i < 8400) segment.curve = 3;
		if (i > 8700 && i < 8900) segment.curve = 4;
		if (i > 9300 && i < 10000) segment.curve = -3;

		if (i > 8300 && i < 8900) ChangeAltitude(altitudeVariation, 180.0f, i, 8300, 8900);

		for (int j = 8100; j <= 8200; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(arrowLeft, 1.5f));
				break;
			}
		}
		if (i == 8100) segment.atrezzos.push_back(make_pair(phoneBooth, -2.5f));
		for (int j = 8200; j <= 8300; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(arrowRight, -2.0f));
				break;
			}
		}
		for (int j = 8600; j <= 8700; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(arrowRight, -2.0f));
				break;
			}
		}
		for (int j = 8700; j <= 9000; j += 40) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(streetMirror, 1.5f));
				break;
			}
		}
		for (int j = 9000; j <= 9300; j += 40) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(streetMirror, -2.0f));
				break;
			}
		}
		for (int j = 9200; j <= 9300; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(arrowLeft, 1.5f));
				break;
			}
		}
		if (i == 9500) segment.atrezzos.push_back(make_pair(birdBird, 1.5f));
		if (i == 9550) segment.atrezzos.push_back(make_pair(bridalStone, 1.5f));
		if (i == 9600) segment.atrezzos.push_back(make_pair(nokSparkPlugs, 1.5f));
		if (i == 9650) segment.atrezzos.push_back(make_pair(discoNora, 1.5f));
		if (i == 9700) segment.atrezzos.push_back(make_pair(morobare, 1.5f));
		if (i == 9750) segment.atrezzos.push_back(make_pair(birdBird, 1.5f));
		if (i == 9800) segment.atrezzos.push_back(make_pair(bridalStone, 1.5f));
		if (i == 9850) segment.atrezzos.push_back(make_pair(nokSparkPlugs, 1.5f));
		if (i == 9900) segment.atrezzos.push_back(make_pair(discoNora, 1.5f));
		if (i == 9950) segment.atrezzos.push_back(make_pair(morobare, 1.5f));


		//Sixth part (10200 - 12200) - City
		if (i > 10300 && i < 10700) segment.curve = -3.0f;
		if (i > 10700 && i < 11000) segment.curve = 0.5f;
		if (i > 11000 && i < 11400) segment.curve = 1;
		if (i > 11400 && i < 11700) segment.curve = 3;
		if (i > 11700 && i < 12000) segment.curve = -4;

		for (int j = 10200; j <= 13000; j += 60) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(lampLeft, -2.0f));
				segment.atrezzos.push_back(make_pair(lampRight, 1.0f));
				break;
			}
		}
		for (int j = 11300; j <= 11400; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(arrowRight, -2.0f));
				break;
			}
		}
		for (int j = 11600; j <= 11700; j += 30) {
			if (i == j) {
				segment.atrezzos.push_back(make_pair(arrowLeft, 1.5f));
				break;
			}
		}


		for (vector<int>::iterator it = checkPoints.begin(); it != checkPoints.end(); ++it) {
			if (i == *it) {
				segment.atrezzos.push_back(make_pair(checkSign, -3.0f));
				segment.atrezzos.push_back(make_pair(rightLegOfSign, -3.0f));
			}
		}

		if (i == goalPoint) { segment.atrezzos.push_back(make_pair(goalSign, -3.0f)); }
		if (i == goalPoint) { segment.atrezzos.push_back(make_pair(rightLegOfSign, -3.0f)); }

		if (i == goalPoint + 300) { segment.atrezzos.push_back(make_pair(crowd, -0.9f)); }
		if (i == goalPoint + 296) { segment.atrezzos.push_back(make_pair(victoryPose, -0.1f)); }

		lines.push_back(segment);
	}

	N = lines.size();
}

ModuleEuropeRace::~ModuleEuropeRace()
{
}