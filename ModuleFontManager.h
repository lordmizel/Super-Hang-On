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

	void StringRendering(const std::string stringToRender, const int x, const int y, const Color color = Color(255, 255, 255, 255));
	void DigitRendering(const int numberToRender, const int numDigits, const int x, const int y, const Color color = Color(255, 255, 255, 255), const bool fillWithZero = false, const bool big = false);

	void PrintDigit(const int digit, const int x, const int y, const Color color, const bool big);
	void PrintChar(const char c, const int x, const int y, const Color color);

	std::map<char, SDL_Rect> characters;

private:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;

	SDL_Rect blankSpace;
	SDL_Rect numbers[10];
	SDL_Rect numbersBig[10];
};

#endif