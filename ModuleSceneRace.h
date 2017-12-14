#ifndef __ModuleSceneRace_H__
#define __ModuleSceneRace_H__

#include "Module.h"
#include "Animation.h"

class Segment;
//class Rival;

struct atrezzo {
	SDL_Rect sprite;
	int hitBoxXOffset = 0;
	int hitBoxWidth = 0;
};

struct rival {
	SDL_Rect sprite;
	float z = 0;
	int speed = 1000;
	int hitBoxXOffset = 0;
	int hitBoxWidth = 0;
};

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

	atrezzo arrowLeft;
	atrezzo arrowRight;
	atrezzo bridalStone;
	atrezzo nokSparkPlugs;
	atrezzo birdBird;
	atrezzo discoNora;
	atrezzo rustyDrum;
	atrezzo smallCacti;
	atrezzo bigRock;
	atrezzo morobare;
	atrezzo tallCactus;
	atrezzo phoneBooth;
	atrezzo palmLeft;
	atrezzo palmRight;
	atrezzo retroLamp;
	atrezzo palmTree;
	atrezzo smallTree;
	atrezzo streetMirror;
	atrezzo lampRight;
	atrezzo lampLeft;
	atrezzo tallTree;
	atrezzo deadTree;

	atrezzo test;

	atrezzo startSign;

	vector<rival*> rivals;

	//TODO: Turn into animation
	SDL_Rect rivalRunningFront;

private:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* decoration = nullptr;
	SDL_Texture* drivers = nullptr;

	SDL_Rect skyBox = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	Animation sempahore;

	SDL_Rect road;
	SDL_Rect limit;
	SDL_Rect midLine;

	

	const int MAX_LANDSCAPE_ALTITUDE = 273;
	float landscapePositionX = 0.0f;
	float landscapePositionY = 0.0f;
	float foregroundPositionX = 0.0f;
	int landscapeParallaxFactor = 300;
	int foregroundParallaxFactor = 200;

	void DrawRoad();
	int stage;
	float time_;

	SDL_Rect landscapeParis;
};

#endif