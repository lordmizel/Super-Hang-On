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
#include "Segment.h"
#include <string>

//float cover = 0;

ModuleSceneRace::ModuleSceneRace(bool active) : Module(active)
{
	/*sempahore.frames.push_back({ 12, 265, 62, 142 });
	sempahore.frames.push_back({ 84, 265, 62, 142 });
	sempahore.frames.push_back({ 157, 265, 62, 142 });
	sempahore.frames.push_back({ 225, 265, 62, 142 });
	sempahore.loop = false;
	sempahore.speed = 0.01f;*/

	arrowLeft = { 6, 4, 46, 42 };
	arrowRight = { 61, 4, 46, 62};
	bridalStone = { 119, 7, 116, 40 };
	nokSparkPlugs = { 245, 5, 86, 71 };
	birdBird = { 3, 55, 76, 56 };
	discoNora = { 87, 54, 64, 56 };
	rustyDrum = { 159, 56, 44, 56 };
	smallCacti = { 212, 89, 54, 57 };
	bigRock = { 95, 117, 96, 56 };
	morobare = { 4, 130, 80, 48 };
	tallCactus = { 5, 186, 36, 88 };
	phoneBooth = { 62, 187, 40, 96 };
	palmLeft = { 109, 183, 76, 144 };
	palmRight = { 195, 183, 76, 144 };
	retroLamp = { 292, 194, 24, 159 };
	palmTree = { 4, 287, 46, 142 };
	smallTree = { 58, 337, 64, 71 };
	streetMirror = { 132, 332, 20, 72 };
	lampRight = { 161, 334, 52, 160 };
	lampLeft = { 227, 334, 56, 160 };
	tallTree = { 287, 363, 40, 128 };
	deadTree = { 62, 419, 45, 70 };

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

	App->renderer->Blit(graphics, 0 - App->player->GetAbsoluteX() / 200, -currentBiome.background1.y + 340, &currentBiome.background1, 0.2f, false, false, 2, 2);

	for (int n = startPos; n < startPos + 200; n++) {
		Color grass = (n / 3) % 2 ? currentBiome.grassDark : currentBiome.grassLight;
		Color rumble = (n / 3) % 2 ? currentBiome.rumbleDark : currentBiome.rumbleLight;
		Color rumble2 = (n / 3) % 2 ? currentBiome.rumbleLight : currentBiome.rumbleDark;
		Color line = (n / 3) % 2 ? currentBiome.rumbleLight : currentBiome.roadColor;

		Segment &l = lines[n%N];
		l.project((int)(App->player->GetXPosition() - x), camH, seg_pos - (n >= N ? N * 100 : 0));
		x += dx;
		dx += l.curve;

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

		Segment previous;
		if (n == 0)
			previous = lines[lines.size() - 1 % N];
		else
			previous = lines[(n - 1) % N];

		int laneNumber = 10;
		for (int i = laneNumber; i > 0; i--) {
			if ((short)previous.Y != (short)l.Y) {
				App->renderer->DrawPolygon(grass, SCREEN_WIDTH / 2, (short)previous.Y, SCREEN_WIDTH, SCREEN_WIDTH / 2, (short)l.Y, SCREEN_WIDTH);
			}
		}
		App->renderer->DrawPolygon(rumble2, (short)previous.X, (short)previous.Y, (short)(previous.W*1.15), (short)l.X, (short)l.Y, (short)(l.W*1.15));
		App->renderer->DrawPolygon(rumble, (short)previous.X, (short)previous.Y, (short)(previous.W*1.03), (short)l.X, (short)l.Y, (short)(l.W*1.03));
		
		App->renderer->DrawPolygon(currentBiome.roadColor, (short)previous.X, (short)previous.Y, (short)previous.W, (short)l.X, (short)l.Y, (short)l.W);
		App->renderer->DrawPolygon(line, (short)previous.X, (short)previous.Y, (short)(previous.W*0.05), (short)l.X, (short)l.Y, (short)(l.W*0.05));
	}

	//Draw Objects
	for (int n = startPos + 199; n >= startPos; n--) {
		if (!lines[n%N].atrezzos.empty()) {
			for (int i = 0; i < lines[n%N].atrezzos.size(); i++) {
				lines[n%N].DrawObject(lines[n%N].atrezzos[i].first, decoration, lines[n%N].atrezzos[i].second);
			}
		}
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

	App->ui->ShowUI();

	return UPDATE_CONTINUE;
}

void ModuleSceneRace::BiomeChange() {
	//Adapt light grass
	if (currentBiome.grassLight.r != biomes[biomeIndex].grassLight.r) {
		currentBiome.grassLight.r < biomes[biomeIndex].grassLight.r ? currentBiome.grassLight.r++ : currentBiome.grassLight.r--;
	}
	if (currentBiome.grassLight.g != biomes[biomeIndex].grassLight.g) {
		currentBiome.grassLight.g < biomes[biomeIndex].grassLight.g ? currentBiome.grassLight.g += 2 : currentBiome.grassLight.g -= 2;
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
