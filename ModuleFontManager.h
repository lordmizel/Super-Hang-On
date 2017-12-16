#ifndef __MODULEFONTMANAGER_H__
#define __MODULEFONTMANAGER_H__

#include "Module.h"
#include <map>

struct SDL_Texture;

class ModuleFontManager : public Module
{
public:
	ModuleFontManager(bool start_enabled = true);
	~ModuleFontManager();

	bool Start();
	bool CleanUp();

	void StringRendering(std::string stringToRender, int x, int y, Color color = Color(255, 255, 255, 255));
	void DigitRendering(int numberToRender, int numDigits, int x, int y, Color color = Color(255, 255, 255, 255), bool fillWithZero = false, bool big = false);

	void PrintDigit(int digit, int x, int y, Color color, bool big);
	void PrintChar(char c, int x, int y, Color color);

	std::map<char, SDL_Rect> characters;

private:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;

	SDL_Rect blankSpace;
	SDL_Rect numbers[10];
	SDL_Rect numbersBig[10];
};

#endif