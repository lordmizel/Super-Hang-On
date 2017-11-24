#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleCollision;
class ModuleParticles;

// Game modules ---
class ModulePlayer;
class ModuleScore;
class ModuleSceneIntro;
class ModuleSceneMap;
class ModuleSceneMusic;
class ModuleEuropeRace;

class CharacterManager;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleCollision* collision;
	ModuleParticles* particles;

	// Game modules ---
	ModulePlayer* player;
	ModuleScore* score;
	ModuleSceneIntro* scene_intro;
	ModuleSceneMap* scene_map;
	ModuleSceneMusic* scene_music;
	ModuleEuropeRace* europe_race;

private:

	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__