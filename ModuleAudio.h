#ifndef __MODULEAUDIO_H__
#define __MODULEAUDIO_H__

#include <vector>
#include "Module.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

class ModuleAudio : public Module
{
public:

	ModuleAudio(bool start_enabled = true);
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, const float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(const unsigned int fx, const int repeat = 0) const;

	bool PauseFx(const unsigned int id) const;
	void MusicFadeOut(const float fade_time) const;

	char* musicChosen;

private:

	Mix_Music*	music = nullptr;
	std::vector<Mix_Chunk*>	fx;
};

#endif // __MODULEAUDIO_H__