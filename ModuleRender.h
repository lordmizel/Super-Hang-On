#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, const int x, const int y, SDL_Rect* section, const float speed = 1.0f, const bool moveX = false, const bool moveY = false, const float scaledW = -1, const float scaledH = -1, const Color color = Color());
	bool DrawQuad(const SDL_Rect& rect, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a, const bool use_camera = true);
	bool DrawPolygon(const Color c, const short x1, const short y1, const short w1, const short x2, const short y2, const short w2);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
};

#endif // __MODULERENDER_H__