#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFont.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneTrack.h"
#include "ModulePlayer.h"
//#include "ModuleEnemy.h"
#include "Line.h"
#include <string>

ModuleSceneTrack::ModuleSceneTrack(bool active) : Module(active)
{
	startSign = { 7, 2, 627, 207};

	sempahor.frames.push_back({ 12, 265, 62, 142 });
	sempahor.frames.push_back({ 84, 265, 62, 142 });
	sempahor.frames.push_back({ 157, 265, 62, 142 });
	sempahor.frames.push_back({ 225, 265, 62, 142 });
	sempahor.loop = false;
	sempahor.speed = 0.01f;

	maxPuntuation = 6514651;
	stage = 1;
	time = 60;
	score = 0;
	speed = 200;

	backgroundTop = {33, 437, 62, 25};
	backgroundTime = { 97, 437, 76, 26 };
	backgroundScore = { 175, 437, 98, 26 };
	backgroundStage = { 275, 421, 83, 18 };
	backgroundStageProces = { 33, 467, 226, 18 };
	backgroundCourse = { 409, 421, 98, 18 };
	backgroundSpeed = { 275, 441, 82, 18 };
	backgroundKm = { 367, 441, 34, 18 };

	//Decoration
	deadTree = { 649, 0, 138, 209 };

}

ModuleSceneTrack::~ModuleSceneTrack()
{}

// Load assets
bool ModuleSceneTrack::Start()
{
	LOG("Loading space intro");

	graphics = App->textures->Load("sprites/backgrounds.png", 255, 255, 255);
	decoration = App->textures->Load("sprites/decoration.png", 255, 255, 255);
	gui = App->textures->Load("sprites/miscellaneous.png", 255, 255, 255);

	//Gui fonts
//	App->numericFontYellow = App->font->LoadMedia("fonts/fontNumber18x18.png", "1234567890", 16, 18);
	//App->numericFontWhite = App->font->LoadMedia("fonts/fontNumber18x18.png", "1234567890", 16, 18, 18);
	//App->numericFontRed = App->font->LoadMedia("fonts/fontNumber18x18.png", "1234567890", 16, 18, 36);
	//App->numericFontGreen = App->font->LoadMedia("fonts/fontNumber18x18.png", "1234567890", 16, 18, 54);

	//ON DEBUG MODE
	//App->menusFont = App->font->LoadMedia("fonts/font18x30.png", "9876543210", 18, 30);

	App->player->Enable();
	//App->enemy->Enable();
	return true;
}

// UnLoad assets
bool ModuleSceneTrack::CleanUp()
{
	LOG("Unloading space scene");
	App->textures->Unload(graphics);
	return true;
}

void ModuleSceneTrack::PrintTrack()
{

	while (pos >= N * 200) pos -= N * SEGL;
	while (pos < 0) pos += N * SEGL;

	float x = 0, dx = 0;
	int startPos = pos / SEGL;
	int camH = (int)(1500 + lines[startPos].y);
	int maxy = HEIGHT;

	for (int n = startPos; n < startPos + 300; n++) {
		Line &l = lines[n%N];
		l.project((int)(playerX - x), camH, pos - (n >= N ? N * 200 : 0));
		x += dx;
		dx += l.curve;

		l.clip = maxy;
		if (l.Y >= maxy) continue;
		maxy = (int)(l.Y);

		Color grass = (n / 3) % 2 ? Color(102, 255, 102, 255) : Color(51, 255, 51, 255);
		Color grass2aux = (n / 3) % 2 ? grass2 : grass2;
		Color line = (n / 10) % 2 ? color_line : color_road;

		Line p;
		if (n == 0)
			p = lines[lines.size() - 1 % N]; //previous line
		else
			p = lines[(n - 1) % N]; //previous line

		int numRalles = 100;
		//App->renderer->DrawPoly(grass, 0, (short)p.Y, (short)p.width, 0, (short)l.Y, (short)l.width);
		for (int i = numRalles; i > 0; i--) {
			if (i % 2 == 0)
				App->renderer->DrawPolygon(Green, (short)p.X, (short)p.Y, (short)(p.W*0.3*i), (short)l.X, (short)l.Y, (short)(l.W*0.3*i));
			else
				App->renderer->DrawPolygon(grass, (short)p.X, (short)p.Y, (short)(p.W*0.3*i), (short)l.X, (short)l.Y, (short)(l.W*0.3*i));
		}
		App->renderer->DrawPolygon(Green, (short)p.X, (short)p.Y, (short)(p.W*0.1), (short)l.X, (short)l.Y, (short)(l.W*0.01));
		App->renderer->DrawPolygon(grass2aux, (short)p.X, (short)p.Y, (short)(p.W*0.05), (short)l.X, (short)l.Y, (short)(l.W*0.05));
		//App->renderer->DrawPoly(rumble, (short)p.X, (short)p.Y, (short)(p.W*1.2), (short)l.X, (short)l.Y, (short)(l.W*1.2));
		App->renderer->DrawPolygon(color_road, (short)p.X, (short)p.Y, (short)p.W, (short)l.X, (short)l.Y, (short)l.W);
		App->renderer->DrawPolygon(line, (short)p.X, (short)p.Y, (short)(p.W*0.05), (short)l.X, (short)l.Y, (short)(l.W*0.05));
	}

	//Draw background
	App->renderer->Blit(graphics, 0, 0, &background, 0.0f);
	App->renderer->Blit(graphics, 0, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);
	App->renderer->Blit(graphics, 610, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);
	App->renderer->Blit(graphics, -610, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);


	//Draw Objects
	for (int n = startPos + 300; n > startPos; n--) {
		if (lines[n%N].spriteX != -1)
			lines[n%N].DrawObject(deadTree, decoration);
	}
}
/*
void ModuleSceneTrack::PrintTrack()
{

	while (pos >= N * 200) pos -= N * Line::SEGL;
	while (pos < 0) pos += N * Line::SEGL;

	float x = 0, dx = 0;
	int startPos = pos / Line::SEGL;
	int camH = (int)(1500 + lines[startPos].Gety());
	int maxy = Line::HEIGHT;

	for (int n = startPos; n < startPos + 300; n++) {
		Line &l = lines[n%N];
		l.project((int)(playerX - x), camH, pos - (n >= N ? N * 200 : 0));
		x += dx;
		dx += l.GetCurve();

		l.SetClip(maxy);
		if (l.GetY() >= maxy) continue;
		maxy = (int)(l.GetY());

		Color grass = (n / 3) % 2 ? Color(102,255,102,255) : Color(51,255,51,255);
		Color grass2aux = (n / 3) % 2 ? grass2 : grass2;
		Color line = (n / 10) % 2 ? color_line : color_road;

		Line p;
		if (n == 0)
			p = lines[lines.size() - 1 % N]; //previous line
		else
		    p = lines[(n - 1) % N]; //previous line

		int numRalles = 100;
		//App->renderer->DrawPoly(grass, 0, (short)p.GetY(), (short)p.GetW()idth, 0, (short)l.GetY(), (short)l.GetW()idth);
		for (int i = numRalles; i > 0; i--) {
			if(i % 2 == 0)
				App->renderer->DrawPolygon(Green, (short)p.GetX(), (short)p.GetY(), (short)(p.GetW()*0.3*i), (short)l.GetX(), (short)l.GetY(), (short)(l.GetW()*0.3*i));
			else
				App->renderer->DrawPolygon(grass, (short)p.GetX(), (short)p.GetY(), (short)(p.GetW()*0.3*i), (short)l.GetX(), (short)l.GetY(), (short)(l.GetW()*0.3*i));
		}
		App->renderer->DrawPolygon(Green, (short)p.GetX(), (short)p.GetY(), (short)(p.GetW()*0.1), (short)l.GetX(), (short)l.GetY(), (short)(l.GetW()*0.01));
		App->renderer->DrawPolygon(grass2aux, (short)p.GetX(), (short)p.GetY(), (short)(p.GetW()*0.05), (short)l.GetX(), (short)l.GetY(), (short)(l.GetW()*0.05));
		//App->renderer->DrawPolygon(rumble, (short)p.GetX(), (short)p.GetY(), (short)(p.GetW()*1.2), (short)l.GetX(), (short)l.GetY(), (short)(l.GetW()*1.2));
		App->renderer->DrawPolygon(color_road, (short)p.GetX(), (short)p.GetY(), (short)p.GetW(), (short)l.GetX(), (short)l.GetY(), (short)l.GetW());
		App->renderer->DrawPolygon(line, (short)p.GetX(), (short)p.GetY(), (short)(p.GetW()*0.05), (short)l.GetX(), (short)l.GetY(), (short)(l.GetW()*0.05));
	}

	//Draw background
	App->renderer->Blit(graphics, 0, 0, &background, 0.0f);
	App->renderer->Blit(graphics, 0, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);
	App->renderer->Blit(graphics, 610, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);
	App->renderer->Blit(graphics, -610, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);


	//Draw Objects
	for (int n = startPos + 300; n > startPos; n--) {
		if (lines[n%N].GetSpriteX() != -1)
			lines[n%N].DrawObject(deadTree, decoration);
	}
}
*/
void ModuleSceneTrack::PrintGui() {
	App->renderer->Blit(gui, (SCREEN_WIDTH / 10), (SCREEN_HEIGHT / 20), &backgroundTop, 0.f);
	App->renderer->Blit(gui, (SCREEN_WIDTH / 2) - backgroundTime.w / 2, (SCREEN_HEIGHT / 20), &backgroundTime, 0.f);
	App->renderer->Blit(gui, (SCREEN_WIDTH / 10) * 6, (SCREEN_HEIGHT / 20), &backgroundScore, 0.f);
	App->renderer->Blit(gui, (SCREEN_WIDTH / 10), (SCREEN_HEIGHT / 20) * 2 + 8, &backgroundCourse, 0.f);
	App->renderer->Blit(gui, (SCREEN_WIDTH / 10), (SCREEN_HEIGHT / 20) * 3, &backgroundStage, 0.f);
	App->renderer->Blit(gui, (SCREEN_WIDTH / 20), (SCREEN_HEIGHT / 20) * 4, &backgroundStageProces, 0.f);
	App->renderer->Blit(gui, (int)((SCREEN_WIDTH / 10) * 6.5), (int)((SCREEN_HEIGHT / 20) * 2 + 8), &backgroundSpeed, 0.f);
	App->renderer->Blit(gui, (int)((SCREEN_WIDTH / 10) * 8.5) + 16, (int)((SCREEN_HEIGHT / 20) * 2 + 8), &backgroundKm, 0.f);
	App->renderer->Blit(gui, (int)((SCREEN_WIDTH / 10) * 2.7), (int)((SCREEN_HEIGHT / 20) * 2 + 8), &backgroundTrackName, 0.f, false);

	//Text
	/*
	App->renderer->Print(App->numericFontRed, to_string((int)maxPuntuation).c_str(), (SCREEN_WIDTH / 10) + backgroundTop.GetW() + 5, (SCREEN_HEIGHT / 20) + 4, 0.f, false);
	App->renderer->Print(App->numericFontGreen, to_string((int)score).c_str(), (SCREEN_WIDTH / 10) * 6 + backgroundScore.GetW() + 5, (SCREEN_HEIGHT / 20) + 4, 0.f, false);
	if(speed < 280)
		App->renderer->Print(App->numericFontWhite, to_string((int)speed).c_str(), (int)((SCREEN_WIDTH / 10) * 6.5) + backgroundSpeed.GetW() , (int)((SCREEN_HEIGHT / 20) * 2 + 8), 0.f, false);
	else
		App->renderer->Print(App->numericFontRed, to_string((int)speed).c_str(), (int)((SCREEN_WIDTH / 10) * 6.5) + backgroundSpeed.GetW() , (int)((SCREEN_HEIGHT / 20) * 2 + 8), 0.f, false);
	App->renderer->Print(App->menusFont, to_string((int)time).c_str(), SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 20 * 3, 0.f);
	App->renderer->Print(App->numericFontWhite, to_string((int)stage).c_str(), (int)((SCREEN_WIDTH / 10) * 2.4, (SCREEN_HEIGHT / 20) * 3), 0.f, false);
	*/
}


// Update: draw background
update_status ModuleSceneTrack::Update(/*float deltaTime*/)
{
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		pos += 200;
		score += 200;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		playerX += 20;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		playerX -= 20;
	}

	PrintTrack();



	//DrawDecoration
	//App->renderer->Blit(decoration, 5, SCREEN_HEIGHT / 2  - 60, &startSign, 0.f);
	//App->renderer->Blit(decoration,  35, SCREEN_HEIGHT / 2 + 10, &sempahor.GetCurrentFrame(), 0.f);

	if (App->fade->isFading() == false && (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN))
	{

	}
	/*
	time -= deltaTime;
	if (time < 0) time = 0;
	*/
	//Print GUI

	PrintGui();

	

	return UPDATE_CONTINUE;
}
