#ifndef __ModuleSceneRace_H__
#define __ModuleSceneRace_H__

#include "Module.h"
#include "Animation.h"

class Segment;
class ModuleEnemy;



class ModuleSceneRace : public Module
{

public:
	struct biome {
		Color grassLight;
		Color grassDark;
		Color rumbleLight;
		Color rumbleDark;
		Color roadColor;
		Color skyColor;
		SDL_Rect background1;
		SDL_Rect background2;

		biome();
		biome(Color gl, Color gd, Color rl, Color rd, Color rc, Color sc, SDL_Rect bg1, SDL_Rect bg2) :
			grassLight(gl), grassDark(gd), rumbleLight(rl), rumbleDark(rd), roadColor(rc), skyColor(sc), background1(bg1), background2(bg2)
		{
		}
	};

	ModuleSceneRace(bool active = true);
	~ModuleSceneRace();

	bool Start();
	update_status Update(/*float deltaTime*/);
	bool CleanUp();

	vector<Segment> lines;
	
	int N = 0;
	int pos;
	int seg_pos;

protected:
	
	void BiomeChange();
	void ChangeAltitude(float &altitudeVariation, float targetVariation, int currentSegment, int startingSegment, int endSegment, int heldSegments = 0);

	vector<biome> biomes;
	int biomeIndex = 0;
	biome currentBiome;
	vector<int> biomeBorders;

	SDL_Rect arrowLeft;
	SDL_Rect arrowRight;
	SDL_Rect bridalStone;
	SDL_Rect nokSparkPlugs;
	SDL_Rect birdBird;
	SDL_Rect discoNora;
	SDL_Rect rustyDrum;
	SDL_Rect smallCacti;
	SDL_Rect bigRock;
	SDL_Rect morobare;
	SDL_Rect tallCactus;
	SDL_Rect phoneBooth;
	SDL_Rect palmLeft;
	SDL_Rect palmRight;
	SDL_Rect retroLamp;
	SDL_Rect palmTree;
	SDL_Rect smallTree;
	SDL_Rect streetMirror;
	SDL_Rect lampRight;
	SDL_Rect lampLeft;
	SDL_Rect tallTree;
	SDL_Rect deadTree;

private:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* decoration = nullptr;

	Animation sempahore;

	SDL_Rect road;
	SDL_Rect limit;
	SDL_Rect midLine;

	int landscapePosition = 0;

	void DrawRoad();
	int stage;
	float time_;

	SDL_Rect landscapeParis;
};

#endif