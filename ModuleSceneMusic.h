#ifndef __MODULESCENEMUSIC_H__
#define __MODULESCENEMUSIC_H__

#include "Module.h"
#include "Animation.h"
#include "Timer.h"

struct SDL_Texture;

enum songSelect {
	SONG1,
	SONG2,
	SONG3,
	SONG4
};

class ModuleSceneMusic : public Module
{
public:
	ModuleSceneMusic(bool active = true);
	~ModuleSceneMusic();

	bool Start();
	update_status Update();
	bool CleanUp();

private:
	SDL_Texture* graphics = nullptr;

	SDL_Rect backdrop;
	SDL_Rect selectMusic;

	Animation song1;
	Animation song2;
	Animation song3;
	Animation song4;
	Animation pressButton;

	int selectedSong;
	float animationSpeed;
	uint fx = 0;

	void ChangeSongPlaying();

	Timer timer_;
};

#endif