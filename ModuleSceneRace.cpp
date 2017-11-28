#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFont.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneRace.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "ModuleScore.h"
//#include "ModuleEnemy.h"
#include "Segment.h"
#include <string>

ModuleSceneRace::ModuleSceneRace(bool active) : Module(active)
{
	landscapeParis = { 330, 256, 320, 128 };

	sempahor.frames.push_back({ 12, 265, 62, 142 });
	sempahor.frames.push_back({ 84, 265, 62, 142 });
	sempahor.frames.push_back({ 157, 265, 62, 142 });
	sempahor.frames.push_back({ 225, 265, 62, 142 });
	sempahor.loop = false;
	sempahor.speed = 0.01f;

	stage = 1;
	time_ = 60;
}

ModuleSceneRace::~ModuleSceneRace()
{}

// Load assets
bool ModuleSceneRace::Start()
{
	LOG("Loading race");

	graphics = App->textures->Load("backgrounds.png", 255, 0, 204);
	//decoration = App->textures->Load("sprites/decoration.png", 255, 255, 255);

	App->player->Enable();
	//App->enemy->Enable();
	return true;
}

// UnLoad assets
bool ModuleSceneRace::CleanUp()
{
	LOG("Unloading space scene");
	App->textures->Unload(graphics);
	return true;
}

void ModuleSceneRace::DrawRoad()
{
	int segment_length_draw = SEGMENT_LENGTH;
	int seg_pos = pos;
	if (pos % SEGMENT_LENGTH != 0) {
		seg_pos = SEGMENT_LENGTH * (pos / SEGMENT_LENGTH);
	}
	while (seg_pos >= N * segment_length_draw) seg_pos -= N * segment_length_draw;
	while (seg_pos < 0) seg_pos += N * segment_length_draw;

	float x = 0, dx = 0;
	int startPos = seg_pos / segment_length_draw;
	int camH = (int)(1500 + lines[startPos].y);
	int maxy = HEIGHT;


	/*App->renderer->Blit(graphics, landscapePosition-landscapeParis.w, 0, &landscapeParis, 0.2, true, false, 2, 2);
	App->renderer->Blit(graphics, landscapePosition, 0, &landscapeParis, 0.2, true, false, 2, 2);
	App->renderer->Blit(graphics, landscapePosition + landscapeParis.w, 0, &landscapeParis, 0.2, true, false, 2, 2);*/

	for (int n = startPos; n < startPos + 100; n++) {
		Segment &l = lines[n%N];
		l.project((int)(playerX - x), camH, seg_pos - (n >= N ? N * 200 : 0));
		x += dx;
		dx += l.curve;

		if (n == startPos) {
			if (l.curve > 0){
				playerX -= 40;
			}
			else if(l.curve < 0) {
				playerX += 40;
			}
		}

		l.clip = maxy;
		if (l.Y >= maxy) continue;
		maxy = (int)(l.Y);

		Color grass = (n / 3) % 2 ? Color(128, 128, 128, 255) : Color(160, 160, 160, 255);
		Color rumble = (n / 3) % 2 ? Color(224, 224, 224, 255) : Color(96, 96, 96, 255);
		Color rumble2 = (n / 3) % 2 ? Color(96, 96, 96, 255) : Color(224, 224, 224, 255);
		Color grass2aux = (n / 3) % 2 ? grass2 : grass2;
		Color line = (n / 3) % 2 ? color_line : color_road;

		

		Segment p;
		if (n == 0)
			p = lines[lines.size() - 1 % N]; //previous line
		else
			p = lines[(n - 1) % N]; //previous line

		int numRalles = 10;
		for (int i = numRalles; i > 0; i--) {
			if((short)p.Y != (short)l.Y)
			App->renderer->DrawPolygon(grass, SCREEN_WIDTH / 2 /*(short)p.X*/, (short)p.Y, SCREEN_WIDTH/*(short)(p.W*0.3*i)*/, SCREEN_WIDTH / 2/*(short)l.X*/, (short)l.Y, SCREEN_WIDTH/*(short)(l.W*0.3*i)*/);
		}
		App->renderer->DrawPolygon(rumble2, (short)p.X, (short)p.Y, (short)(p.W*1.15), (short)l.X, (short)l.Y, (short)(l.W*1.15));
		App->renderer->DrawPolygon(rumble, (short)p.X, (short)p.Y, (short)(p.W*1.03), (short)l.X, (short)l.Y, (short)(l.W*1.03));
		
		App->renderer->DrawPolygon(color_road, (short)p.X, (short)p.Y, (short)p.W, (short)l.X, (short)l.Y, (short)l.W);
		App->renderer->DrawPolygon(line, (short)p.X, (short)p.Y, (short)(p.W*0.05), (short)l.X, (short)l.Y, (short)(l.W*0.05));
	}

	//App->score->ShowScore();

	//Draw background
	//App->renderer->Blit(graphics, 0, 0, &landscapeParis, 0.0f);
	/*App->renderer->Blit(graphics, 0, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);
	App->renderer->Blit(graphics, 610, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);
	App->renderer->Blit(graphics, -610, SCREEN_HEIGHT / 2 + 7, &backgroundParalax, .05f, true);*/


	//Draw Objects
	/*for (int n = startPos + 300; n > startPos; n--) {
		if (lines[n%N].spriteX != -1)
			lines[n%N].DrawObject(deadTree, decoration);
	}*/
}

// Update: draw background
update_status ModuleSceneRace::Update()
{
	time_t now = time(NULL);
	int seconds = difftime(g_timer, now);
	if (seconds != 0){
		pos += App->player->GetSpeed() / 1.5f;
		App->score->UpdateScore(App->player->GetSpeed());
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		playerX += 40;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		playerX -= 40;
	}

	DrawRoad();

	//DrawDecoration
	//App->renderer->Blit(decoration, 5, SCREEN_HEIGHT / 2  - 60, &startSign, 0.f);
	//App->renderer->Blit(decoration,  35, SCREEN_HEIGHT / 2 + 10, &sempahor.GetCurrentFrame(), 0.f);

	App->ui->ShowUI();

	return UPDATE_CONTINUE;
}
