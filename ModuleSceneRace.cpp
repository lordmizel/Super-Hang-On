#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
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

	sempahore.frames.push_back({ 12, 265, 62, 142 });
	sempahore.frames.push_back({ 84, 265, 62, 142 });
	sempahore.frames.push_back({ 157, 265, 62, 142 });
	sempahore.frames.push_back({ 225, 265, 62, 142 });
	sempahore.loop = false;
	sempahore.speed = 0.01f;

	deadTree = { 56, 413, 54, 80 };

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
	decoration = App->textures->Load("stuff.png", 255, 0, 255);

	currentBiome = biomes[biomeIndex];

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
	seg_pos = pos;
	if (pos % SEGMENT_LENGTH != 0) {
		seg_pos = SEGMENT_LENGTH * (pos / SEGMENT_LENGTH);
	}
	while (seg_pos >= N * segment_length_draw) seg_pos -= N * segment_length_draw;
	while (seg_pos < 0) seg_pos += N * segment_length_draw;

	float x = 0, dx = 0;
	int startPos = seg_pos / segment_length_draw;
	int camH = (int)(1500 + lines[startPos].y);
	int maxy = SCREEN_HEIGHT;

	
	/*App->renderer->Blit(graphics, landscapePosition-landscapeParis.w, 0, &landscapeParis, 0.2, true, false, 2, 2);
	App->renderer->Blit(graphics, landscapePosition, 0, &landscapeParis, 0.2, true, false, 2, 2);
	App->renderer->Blit(graphics, landscapePosition + landscapeParis.w, 0, &landscapeParis, 0.2, true, false, 2, 2);*/

	for (int n = startPos; n < startPos + 100; n++) {
		Segment &l = lines[n%N];
		l.project((int)(App->player->GetXPosition() - x), camH, seg_pos - (n >= N ? N * 100 : 0));
		x += dx;
		dx += l.curve;

		//TODO: Make centrifugue force dependant on player speed
		if (n == startPos) {
			if (l.curve > 0){
				App->player->AlterXPosition(-App->player->GetSpeed() / 6);
			}
			else if(l.curve < 0) {
				App->player->AlterXPosition(App->player->GetSpeed() / 6);
			}
		}

		l.clip = maxy;
		if (l.Y >= maxy) continue;
		maxy = (int)(l.Y);

		Color grass = (n / 3) % 2 ? currentBiome.grassDark : currentBiome.grassLight;
		Color rumble = (n / 3) % 2 ? currentBiome.rumbleDark : currentBiome.rumbleLight;
		Color rumble2 = (n / 3) % 2 ? currentBiome.rumbleLight : currentBiome.rumbleDark;
		//Color grass2aux = (n / 3) % 2 ? grass2 : grass2;
		Color line = (n / 3) % 2 ? currentBiome.rumbleLight : currentBiome.roadColor;

		Segment p;
		if (n == 0)
			p = lines[lines.size() - 1 % N]; //previous line
		else
			p = lines[(n - 1) % N]; //previous line

		int laneNumber = 10;
		for (int i = laneNumber; i > 0; i--) {
			if((short)p.Y != (short)l.Y)
			App->renderer->DrawPolygon(grass, SCREEN_WIDTH / 2 /*(short)p.X*/, (short)p.Y, SCREEN_WIDTH/*(short)(p.W*0.3*i)*/, SCREEN_WIDTH / 2/*(short)l.X*/, (short)l.Y, SCREEN_WIDTH/*(short)(l.W*0.3*i)*/);
		}
		App->renderer->DrawPolygon(rumble2, (short)p.X, (short)p.Y, (short)(p.W*1.15), (short)l.X, (short)l.Y, (short)(l.W*1.15));
		App->renderer->DrawPolygon(rumble, (short)p.X, (short)p.Y, (short)(p.W*1.03), (short)l.X, (short)l.Y, (short)(l.W*1.03));
		
		App->renderer->DrawPolygon(currentBiome.roadColor, (short)p.X, (short)p.Y, (short)p.W, (short)l.X, (short)l.Y, (short)l.W);
		App->renderer->DrawPolygon(line, (short)p.X, (short)p.Y, (short)(p.W*0.05), (short)l.X, (short)l.Y, (short)(l.W*0.05));

	}

	//Draw Objects
	for (int n = startPos + 99; n >= startPos; n--) {
		if (lines[n%N].spriteX != -1)
			lines[n%N].DrawObject(deadTree, decoration);
	}
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
	
	if (seg_pos / SEGMENT_LENGTH > biomeBorders[biomeIndex])
	{
		if (biomeIndex != biomes.size() - 1) {
			biomeIndex++;
		}
	}

	App->renderer->DrawPolygon(currentBiome.skyColor, 0, 0, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH);

	BiomeChange();

	DrawRoad();

	//DrawDecoration
	//App->renderer->Blit(decoration, 5, SCREEN_HEIGHT / 2  - 60, &startSign, 0.f);
	//App->renderer->Blit(decoration,  35, SCREEN_HEIGHT / 2 + 10, &sempahor.GetCurrentFrame(), 0.f);

	App->ui->ShowUI();

	return UPDATE_CONTINUE;
}

void ModuleSceneRace::BiomeChange() {
	//Adapt light grass
	if (currentBiome.grassLight.r != biomes[biomeIndex].grassLight.r) {
		currentBiome.grassLight.r < biomes[biomeIndex].grassLight.r ? currentBiome.grassLight.r++ : currentBiome.grassLight.r--;
	}
	if (currentBiome.grassLight.g != biomes[biomeIndex].grassLight.g) {
		currentBiome.grassLight.g < biomes[biomeIndex].grassLight.g ? currentBiome.grassLight.g++ : currentBiome.grassLight.g--;
	}
	if (currentBiome.grassLight.b != biomes[biomeIndex].grassLight.b) {
		currentBiome.grassLight.b < biomes[biomeIndex].grassLight.b ? currentBiome.grassLight.b++ : currentBiome.grassLight.b--;
	}

	//Adapt dark grass
	if (currentBiome.grassDark.r != biomes[biomeIndex].grassDark.r) {
		currentBiome.grassDark.r < biomes[biomeIndex].grassDark.r ? currentBiome.grassDark.r++ : currentBiome.grassDark.r--;
	}
	if (currentBiome.grassDark.g != biomes[biomeIndex].grassDark.g) {
		currentBiome.grassDark.g < biomes[biomeIndex].grassDark.g ? currentBiome.grassDark.g++ : currentBiome.grassDark.g--;
	}
	if (currentBiome.grassDark.b != biomes[biomeIndex].grassDark.b) {
		currentBiome.grassDark.b < biomes[biomeIndex].grassDark.b ? currentBiome.grassDark.b++ : currentBiome.grassDark.b--;
	}

	//Adapt light rumble
	if (currentBiome.rumbleLight.r != biomes[biomeIndex].rumbleLight.r) {
		currentBiome.rumbleLight.r < biomes[biomeIndex].rumbleLight.r ? currentBiome.rumbleLight.r++ : currentBiome.rumbleLight.r--;
	}
	if (currentBiome.rumbleLight.g != biomes[biomeIndex].rumbleLight.g) {
		currentBiome.rumbleLight.g < biomes[biomeIndex].rumbleLight.g ? currentBiome.grassLight.g++ : currentBiome.rumbleLight.g--;
	}
	if (currentBiome.rumbleLight.b != biomes[biomeIndex].rumbleLight.b) {
		currentBiome.rumbleLight.b < biomes[biomeIndex].rumbleLight.b ? currentBiome.rumbleLight.b++ : currentBiome.rumbleLight.b--;
	}

	//Adapt dark rumble
	if (currentBiome.rumbleDark.r != biomes[biomeIndex].rumbleDark.r) {
		currentBiome.rumbleDark.r < biomes[biomeIndex].rumbleDark.r ? currentBiome.rumbleDark.r++ : currentBiome.rumbleDark.r--;
	}
	if (currentBiome.rumbleDark.g != biomes[biomeIndex].rumbleDark.g) {
		currentBiome.rumbleDark.g < biomes[biomeIndex].rumbleDark.g ? currentBiome.rumbleDark.g++ : currentBiome.rumbleDark.g--;
	}
	if (currentBiome.rumbleDark.b != biomes[biomeIndex].rumbleDark.b) {
		currentBiome.rumbleDark.b < biomes[biomeIndex].rumbleDark.b ? currentBiome.rumbleDark.b++ : currentBiome.rumbleDark.b--;
	}

	//Adapt road
	if (currentBiome.roadColor.r != biomes[biomeIndex].roadColor.r) {
		currentBiome.roadColor.r < biomes[biomeIndex].roadColor.r ? currentBiome.roadColor.r++ : currentBiome.roadColor.r--;
	}
	if (currentBiome.roadColor.g != biomes[biomeIndex].roadColor.g) {
		currentBiome.roadColor.g < biomes[biomeIndex].roadColor.g ? currentBiome.roadColor.g++ : currentBiome.roadColor.g--;
	}
	if (currentBiome.roadColor.b != biomes[biomeIndex].roadColor.b) {
		currentBiome.roadColor.b < biomes[biomeIndex].roadColor.b ? currentBiome.roadColor.b++ : currentBiome.roadColor.b--;
	}

	//Adapt sky
	if (currentBiome.skyColor.r != biomes[biomeIndex].skyColor.r) {
		currentBiome.skyColor.r < biomes[biomeIndex].skyColor.r ? currentBiome.skyColor.r++ : currentBiome.skyColor.r--;
	}
	if (currentBiome.skyColor.g != biomes[biomeIndex].skyColor.g) {
		currentBiome.skyColor.g < biomes[biomeIndex].skyColor.g ? currentBiome.skyColor.g++ : currentBiome.skyColor.g--;
	}
	if (currentBiome.skyColor.b != biomes[biomeIndex].skyColor.b) {
		currentBiome.skyColor.b < biomes[biomeIndex].skyColor.b ? currentBiome.skyColor.b++ : currentBiome.skyColor.b--;
	}
}

ModuleSceneRace::biome::biome()
{
}
