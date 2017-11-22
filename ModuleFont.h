#ifndef __MODULEFONT_H__
#define __MODULEFONT_H__

#include <vector>
#include <map>

#include "Module.h"

using namespace std;

struct SDL_Surface;
struct SDL_Texture;

struct Font {
	unsigned int width;
	unsigned int heigth;
	unsigned int y;
	map<char, int> fontMap;
	SDL_Texture* surface = nullptr;
};


class ModuleFont : public Module
{
public:

	ModuleFont();
	~ModuleFont();

	//bool Init();
	//bool CleanUp();
	unsigned int LoadMedia(const char* filePath, const char* formatFont, unsigned int fontWidth, unsigned int fontHeight, unsigned int initY = 0);

public:
	vector<Font> fonts;
private:
	
};

#endif // __MODULEFONT_H__