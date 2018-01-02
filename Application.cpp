#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFontManager.h"

#include "ModuleScore.h"
#include "ModuleUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneMap.h"
#include "ModuleSceneMusic.h"
#include "ModuleEuropeRace.h"
#include "ModulePlayer.h"

// For srand()
#include <cstdlib>
#include <ctime>

using namespace std;

time_t g_timer = time(NULL);

Application::Application()
{
	// Initialize random number generator
	srand(static_cast <unsigned> (time(0)));

	// Order matters: they will init/start/pre/update/post in this order
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());

	modules.push_back(renderer = new ModuleRender());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(audio = new ModuleAudio());
	modules.push_back(font_manager = new ModuleFontManager());

	// Game Modules
	modules.push_back(scene_intro = new ModuleSceneIntro(false));
	modules.push_back(scene_map = new ModuleSceneMap(false));
	modules.push_back(scene_music = new ModuleSceneMusic(false));
	modules.push_back(europe_race = new ModuleEuropeRace(false));
	modules.push_back(player = new ModulePlayer(false));
	modules.push_back(ui = new ModuleUI(false));
	modules.push_back(score = new ModuleScore());
	

	// Modules to draw on top of game logic
	modules.push_back(fade = new ModuleFadeToBlack());
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not anabled

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if ((*it)->IsEnabled() == true)
		{
			ret = (*it)->Start();
		}
	}

	// Start the first scene --
	fade->FadeToBlack(scene_map, nullptr, 3.0f);

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	clock_t globalClock = clock();
	deltaTime += float(globalClock - timer) / CLOCKS_PER_SEC;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->CleanUp();

	return ret;
}

