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


ModuleSceneRace::ModuleSceneRace(bool active) : Module(active)
{
	arrowLeft.sprite = { 6, 4, 46, 42 };
	arrowRight.sprite = { 61, 4, 46, 42};
	bridalStone.sprite = { 119, 7, 116, 40 };
	nokSparkPlugs.sprite = { 245, 5, 86, 71 };
	birdBird.sprite = { 3, 55, 76, 56 };
	discoNora.sprite = { 87, 54, 64, 56 };
	rustyDrum.sprite = { 159, 56, 44, 56 };
	rustyDrum.small = true;
	smallCacti.sprite = { 212, 89, 54, 57 };
	bigRock.sprite = { 95, 117, 96, 56 };
	bigRock.small = true;
	morobare.sprite = { 4, 130, 80, 48 };
	tallCactus.sprite = { 5, 186, 36, 88 };
	phoneBooth.sprite = { 62, 187, 40, 96 };
	palmLeft.sprite = { 109, 183, 76, 144 };
	palmLeft.hitBoxXOffset = 10;
	palmLeft.hitBoxWidth = 30;
	palmRight.sprite = { 195, 183, 76, 144 };
	palmRight.hitBoxXOffset = 39;
	palmRight.hitBoxWidth = 30;
	retroLamp.sprite = { 292, 194, 24, 159 };
	palmTree.sprite = { 4, 287, 46, 142 };
	smallTree.sprite = { 58, 337, 64, 71 };
	streetMirror.sprite = { 132, 332, 20, 72 };
	lampRight.sprite = { 161, 334, 52, 160 };
	lampRight.hitBoxXOffset = 45;
	lampRight.hitBoxWidth = 10;
	lampLeft.sprite = { 227, 334, 56, 160 };
	lampLeft.hitBoxWidth = 10;
	tallTree.sprite = { 287, 363, 40, 128 };
	deadTree.sprite = { 62, 419, 45, 70 };

	semaphoreAnimation.frames.push_back({ 340, 422, 30, 72 });
	semaphoreAnimation.frames.push_back({ 371, 422, 30, 72 });
	semaphoreAnimation.frames.push_back({ 402, 422, 30, 72 });
	semaphoreAnimation.frames.push_back({ 433, 422, 30, 72 });
	semaphoreAnimation.speed = 0.007f;
	semaphoreAnimation.loop = false;
	semaphore.sprite = { 433, 422, 30, 72 };

	startSign.sprite = { 333, 2, 314, 103 };
	startSign.hitBoxWidth = 50;
	checkSign.sprite = { 333, 108, 314, 103 };
	checkSign.hitBoxWidth = 50;
	goalSign.sprite = { 333, 214, 314, 103 };
	goalSign.hitBoxWidth = 50;

	rightLegOfSign.sprite = { 0, 0, 0, 0 };
	rightLegOfSign.hitBoxXOffset = 264;
	rightLegOfSign.hitBoxWidth = 50;

	crowd = { 340, 322, 268, 93 };
	victoryPose = { 612, 409, 36, 87 };
	crowd.small = true;
	victoryPose.small = true;

	greenRivalStraight.frames.push_back({ 91, 440, 32, 72 });
	greenRivalStraight.frames.push_back({ 129, 440, 32, 72 });
	greenRivalStraight.speed = 0.2f;

	yellowRivalStraight.frames.push_back({ 91, 520, 32, 72 });
	yellowRivalStraight.frames.push_back({ 129, 520, 32, 72 });
	yellowRivalStraight.speed = 0.2f;

	greenRivalTurnsLeft.frames.push_back({ 244, 440, 45, 72 });
	greenRivalTurnsLeft.frames.push_back({ 295, 440, 45, 72 });
	greenRivalTurnsLeft.speed = 0.2f;

	yellowRivalTurnsLeft.frames.push_back({ 244, 520, 45, 72 });
	yellowRivalTurnsLeft.frames.push_back({ 295, 520, 45, 72 });
	yellowRivalTurnsLeft.speed = 0.2f;

	greenRivalTurnsRight.frames.push_back({ 244, 756, 45, 72 });
	greenRivalTurnsRight.frames.push_back({ 295, 756, 45, 72 });
	greenRivalTurnsRight.speed = 0.2f;

	yellowRivalTurnsRight.frames.push_back({ 244, 836, 45, 72 });
	yellowRivalTurnsRight.frames.push_back({ 295, 836, 45, 72 });
	yellowRivalTurnsRight.speed = 0.2f;

	falsePlayer.frames.push_back({ 91, 280, 32, 72 });
	falsePlayer.frames.push_back({ 129, 280, 32, 72 });
	falsePlayer.speed = 0.2f;

	extendedPlayTag.frames.push_back({ 242, 939, 104, 8 });
	extendedPlayTag.frames.push_back({ 0, 0, 0, 0 });
	extendedPlayTag.speed = 0.1f;

	rival1 = new rival();
	rival2 = new rival();
	rival3 = new rival();
	rival4 = new rival();
	rival5 = new rival();
	endPlayer = new rival();

	rivals.push_back(rival1);
	rivals.push_back(rival2);
	rivals.push_back(rival3);
	rivals.push_back(rival4);
	rivals.push_back(rival5);
	rivals.push_back(endPlayer);

	grass = new Color();
	rumble = new Color();
	rumble2 = new Color();
	line = new Color();
}


ModuleSceneRace::~ModuleSceneRace()
{
	for (rival* p : rivals) {
		delete p;
	}

	delete grass;
	delete rumble;
	delete rumble2;
	delete line;
}


// Load assets
bool ModuleSceneRace::Start()
{
	LOG("Loading race");

	graphics = App->textures->Load("Game/backgrounds.png", 255, 0, 204);
	decoration = App->textures->Load("Game/stuff.png", 255, 0, 255);
	drivers = App->textures->Load("Game/bikes.png", 255, 0, 204);

	landscapePositionY = (float)MAX_LANDSCAPE_ALTITUDE;

	App->player->Enable();
	App->ui->Enable();

	App->score->ResetScore();
	App->score->OpenLapData(lapRecordsFile);

	semaphoreAnimation.Reset();

	ResetRace();

	return true;
}


update_status ModuleSceneRace::Update()
{
	time_t now = time(NULL);
	int seconds = static_cast<int>(difftime(g_timer, now));
	if (App->player->state != ModulePlayer::PAUSE && App->player->state != ModulePlayer::GAME_OVER && App->player->state != ModulePlayer::SCORE_SCREEN) 
	{
		if (seconds != 0) 
		{
			pos += static_cast<int>(App->player->GetSpeed() / 1.5f);
			if (App->player->state != ModulePlayer::GOING_TO_END) {
				App->score->UpdateScore(App->player->GetSpeed());
			}
		}
	}

	if (seg_pos / SEGMENT_LENGTH > biomeBorders[biomeIndex] && App->player->state != BEFORE_RACE)
	{
		if (biomeIndex < biomes.size() - 1) 
		{
			biomeIndex++;
		}
	}

	App->renderer->DrawQuad(skyBox, currentBiome.skyColor.r, currentBiome.skyColor.g, currentBiome.skyColor.b, 255, false);

	if (App->player->state == RACING) {
		BiomeChange();
	}

	ManageRoad();

	if (App->player->state == BEFORE_RACE) 
	{
		App->renderer->Blit(decoration, 98, SCREEN_HEIGHT - semaphoreAnimation.GetCurrentFrame().h * 4 - 21, &semaphoreAnimation.GetCurrentFrame(), 0.0f, false, false, 2.266f, 2.266f);
	}

	if (showExtendedPlay) 
	{
		App->ui->ShowLapTimes();
		App->renderer->Blit(drivers, SCREEN_WIDTH / 2 - extendedPlayTag.frames[0].w, SCREEN_HEIGHT / 2 - extendedPlayTag.frames[0].h - 16, &extendedPlayTag.GetCurrentFrame(), 0.0f, false, false, 2, 2);
		extendedPlayTime.Update();
	}

	if (App->player->state != ModulePlayer::SCORE_SCREEN) {
		App->ui->ShowProgressBar(trackProgressBar, yellowBarLength, goalPoint, pos / SEGMENT_LENGTH);
	}

	return UPDATE_CONTINUE;
}


// UnLoad assets
bool ModuleSceneRace::CleanUp()
{
	LOG("Unloading race scene");
	App->textures->Unload(graphics);
	App->textures->Unload(decoration);
	App->textures->Unload(drivers);
	
	return true;
}


void ModuleSceneRace::ManageRoad()
{
	seg_pos = pos;
	if (pos % SEGMENT_LENGTH != 0) 
	{
		seg_pos = SEGMENT_LENGTH * (pos / SEGMENT_LENGTH);
	}

	while (seg_pos >= N * SEGMENT_LENGTH) 
	{
		seg_pos -= N * SEGMENT_LENGTH;
	}
	while (seg_pos < 0) 
	{
		seg_pos += N * SEGMENT_LENGTH;
	}

	float x = 0, dx = 0;
	int startPos = seg_pos / SEGMENT_LENGTH;
	int camH = (int)(1500 + lines[startPos].y);
	float maxy = SCREEN_HEIGHT;

	if ((int)landscapePositionX < -SCREEN_WIDTH) 
	{
		landscapePositionX = landscapePositionX + SCREEN_WIDTH;
	}
	if ((int)landscapePositionX > SCREEN_WIDTH) 
	{
		landscapePositionX = landscapePositionX - SCREEN_WIDTH;
	}

	if ((int)foregroundPositionX < -SCREEN_WIDTH) 
	{
		foregroundPositionX = foregroundPositionX + SCREEN_WIDTH;
	}
	if ((int)foregroundPositionX > SCREEN_WIDTH) 
	{
		foregroundPositionX = foregroundPositionX - SCREEN_WIDTH;
	}

	App->renderer->Blit(graphics, (int)landscapePositionX, (int)landscapePositionY - currentBiome.background1.h * 2 + 2, &currentBiome.background1, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, (int)landscapePositionX - SCREEN_WIDTH, (int)landscapePositionY - currentBiome.background1.h * 2 + 2, &currentBiome.background1, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, (int)landscapePositionX + SCREEN_WIDTH, (int)landscapePositionY - currentBiome.background1.h * 2 + 2, &currentBiome.background1, 0.0f, false, false, 2, 2);

	App->renderer->Blit(graphics, (int)foregroundPositionX, (int)landscapePositionY - currentBiome.background2.h * 2 + 2, &currentBiome.background2, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, (int)foregroundPositionX - SCREEN_WIDTH, (int)landscapePositionY - currentBiome.background2.h * 2 + 2, &currentBiome.background2, 0.0f, false, false, 2, 2);
	App->renderer->Blit(graphics, (int)foregroundPositionX + SCREEN_WIDTH, (int)landscapePositionY - currentBiome.background2.h * 2 + 2, &currentBiome.background2, 0.0f, false, false, 2, 2);
	
	for (int n = startPos; n < startPos + 150; n++) 
	{
		*grass = (n / 3) % 2 ? currentBiome.grassDark : currentBiome.grassLight;
		*rumble = (n / 3) % 2 ? currentBiome.rumbleDark : currentBiome.rumbleLight;
		*rumble2 = (n / 3) % 2 ? currentBiome.rumbleLight : currentBiome.rumbleDark;
		*line = (n / 3) % 2 ? currentBiome.rumbleLight : currentBiome.roadColor;

		Segment &current = lines[n%N];
		current.project((int)(App->player->GetXPosition() - x), camH, seg_pos - (n >= N ? N * 100 : 0));
		x += dx;
		dx += current.curve;

		if (n == startPos && App->player->state != ModulePlayer::PAUSE && App->player->state != ModulePlayer::GAME_OVER && App->player->state != ModulePlayer::SCORE_SCREEN) 
		{
			if (current.curve > 0)
			{
				App->player->AlterXPosition(-App->player->GetSpeed() / 3.0f * current.curve/6);
				landscapePositionX -= App->player->GetSpeed() / (float)landscapeParallaxFactor;
				foregroundPositionX -= App->player->GetSpeed() / (float)foregroundParallaxFactor;
			}
			else if(current.curve < 0) 
			{
				App->player->AlterXPosition(App->player->GetSpeed() / 3.0f * (-1)*current.curve/6);
				landscapePositionX += App->player->GetSpeed() / (float)landscapeParallaxFactor;
				foregroundPositionX += App->player->GetSpeed() / (float)foregroundParallaxFactor;
			}
		}

		current.clip = maxy;
		if (current.Y >= maxy) continue;
		maxy = current.Y;

		Segment previous;
		if (n == 0)
		{
			previous = lines[lines.size() - 1 % N];
		}
		else
		{
			previous = lines[(n - 1) % N];
		}

		int laneNumber = 10;
		for (int i = laneNumber; i > 0; i--) 
		{
			if ((short)previous.Y != (short)current.Y) 
			{
				App->renderer->DrawPolygon(*grass, SCREEN_WIDTH / 2, (short)previous.Y, SCREEN_WIDTH, SCREEN_WIDTH / 2, (short)current.Y, SCREEN_WIDTH);
			}
		}

		App->renderer->DrawPolygon(*rumble2, (short)previous.X, (short)previous.Y, (short)(previous.W*1.15), (short)current.X, (short)current.Y, (short)(current.W*1.15));
		App->renderer->DrawPolygon(*rumble, (short)previous.X, (short)previous.Y, (short)(previous.W*1.03), (short)current.X, (short)current.Y, (short)(current.W*1.03));
		
		App->renderer->DrawPolygon(currentBiome.roadColor, (short)previous.X, (short)previous.Y, (short)previous.W, (short)current.X, (short)current.Y, (short)current.W);
		App->renderer->DrawPolygon(*line, (short)previous.X, (short)previous.Y, (short)(previous.W*0.05), (short)current.X, (short)current.Y, (short)(current.W*0.05));
	}

	//Draw Objects and Rivals
	for (int n = startPos + 174; n >= startPos; n--) {
		if (!lines[n%N].atrezzos.empty()) {
			for (unsigned int i = 0; i < lines[n%N].atrezzos.size(); i++) {
				lines[n%N].DrawObject(lines[n%N].atrezzos[i].first, decoration, lines[n%N].atrezzos[i].second);
			}
		}
		for (unsigned int i = 0; i < rivals.size(); i++) 
		{
			if (n%N == (int)rivals[i]->z % N && (int)rivals[i]->z % N > startPos) 
			{
				if (rivals[i]->isYellow && i < rivals.size() - 1) 
				{
					if (lines[n%N].curve < 0) 
					{
						rivals[i]->currentAnimation = &yellowRivalTurnsLeft;
					}
					else if (lines[n%N].curve > 0) 
					{
						rivals[i]->currentAnimation = &yellowRivalTurnsRight;
					}
					else if (i < rivals.size() - 1)
					{
						rivals[i]->currentAnimation = &yellowRivalStraight;
					}
				}
				else if (i < rivals.size() - 1)
				{
					if (lines[n%N].curve < 0) 
					{
						rivals[i]->currentAnimation = &greenRivalTurnsLeft;
					}
					else if (lines[n%N].curve > 0) 
					{
						rivals[i]->currentAnimation = &greenRivalTurnsRight;
					}
					else
					{
						rivals[i]->currentAnimation = &greenRivalStraight;
					}
				}
				if (App->player->raceEnded == false) 
				{
					lines[(int)rivals[i]->z % N].DrawRival(rivals[i], drivers);
				}
			}
			else if ((int)rivals[i]->z < startPos - 20 && i < rivals.size() - 1 && rivals[i]->reincident == true) 
			{
				// If the player overtakes this rival, then teleport the rival
				// forward to make him appear again
				rivals[i]->z += 200 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (450 - 200)));
				// Random e [-0.8f, 0.8f]
				rivals[i]->x = -0.8f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.8f - (-0.8f))));
			}
			else if (((int)rivals[i]->z > startPos + 500 && i < rivals.size() - 1 && App->player->state != ModulePlayer::GOING_TO_END && App->player->state != ModulePlayer::RACING)
				|| ((int)rivals[i]->z > startPos + 200 && i < rivals.size() - 1 && (App->player->state == ModulePlayer::CRASHING || App->player->state == ModulePlayer::RECOVERING))) {
				
				rivals[i]->z = (float)(startPos - 10);
				rivals[i]->x = -0.8f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.8f - (-0.8f))));
			}
		}
	}

	for (unsigned int i = 0; i < rivals.size(); i++) 
	{
		if (App->player->state != ModulePlayer::PAUSE && App->player->state != ModulePlayer::BEFORE_RACE && App->player->state != ModulePlayer::GAME_OVER && App->player->state != ModulePlayer::SCORE_SCREEN) 
		{
			rivals[i]->z += rivals[i]->speed;
			rivals[i]->currentAnimation->speed = 0.2f;
		}
		else 
		{
			rivals[i]->currentAnimation->speed = 0.0f;
		}
	}
	
	if (maxy >= MAX_LANDSCAPE_ALTITUDE) 
	{
		landscapePositionY = maxy;
	}
	else
	{
		landscapePositionY = MAX_LANDSCAPE_ALTITUDE;
	}

	//CheckPoint Management
	if (checkPointIndex != checkPoints.size())
	{
		if (startPos > checkPoints[checkPointIndex])
		{
			showExtendedPlay = true;
			App->player->timeLeftInRace.AddTime(30);
			extendedPlayTime.SetTime(2);
			extendedPlayTime.Start();
			App->score->CompareLapTime((int)(App->player->timeLeftInRace.GetTotalTimeElapsed() * 100));
			App->score->currentScore.stage++;
			checkPointIndex++;
		}
	}
	if (extendedPlayTime.IsExpired())
	{
		showExtendedPlay = false;
	}

	//Final Stretch Management
	if (startPos > goalPoint - 700 && startPos < goalPoint - 300)
	{
		App->player->CenterMaxX(ROAD_WIDTH);
	}
	else if (startPos > goalPoint - 300)
	{
		App->player->CenterMaxX(0);
		for (unsigned int i = 0; i < rivals.size() - 1; ++i)
		{
			if ((int)rivals[i]->z > startPos) {
				rivals[i]->speed = 2.5f;
			}
			else {
				rivals[i]->speed = 1.0f;
			}
		}
	}

	if (startPos > goalPoint && (App->player->state == ModulePlayer::RACING || App->player->state == ModulePlayer::OUT_OF_CONTROL))
	{
		endPlayer->z = (float)(((startPos + 9) * SEGMENT_LENGTH) / 100);
		endPlayer->speed = 1.0f;
		App->score->CompareLapTime((int)(App->player->timeLeftInRace.GetTotalTimeElapsed() * 100));
		App->player->timePastGoal.SetTime(3.5f);
		App->player->timePastGoal.Start();
		App->audio->PlayMusic("Game/goal.ogg", 0.0f);
		App->player->state = ModulePlayer::PAST_GOAL;
	}

	if (startPos > goalPoint + 284 && App->player->state == ModulePlayer::GOING_TO_END) 
	{
		startPos = goalPoint + 284;
		endPlayer->z = 0;
		endPlayer->speed = 0;
		App->player->timeEndScene.SetTime(2);
		App->player->timeEndScene.Start();
		App->player->state = ModulePlayer::END_SCENE;
	}
}

void ModuleSceneRace::BiomeChange() 
{
	//Adapt light grass
	if (currentBiome.grassLight.r != biomes[biomeIndex].grassLight.r) 
	{
		currentBiome.grassLight.r < biomes[biomeIndex].grassLight.r ? currentBiome.grassLight.r += 2 : currentBiome.grassLight.r -= 2;
	}
	if (currentBiome.grassLight.g != biomes[biomeIndex].grassLight.g) 
	{
		currentBiome.grassLight.g < biomes[biomeIndex].grassLight.g ? currentBiome.grassLight.g += 2 : currentBiome.grassLight.g -= 2;
	}
	if (currentBiome.grassLight.b != biomes[biomeIndex].grassLight.b) 
	{
		currentBiome.grassLight.b < biomes[biomeIndex].grassLight.b ? currentBiome.grassLight.b += 2 : currentBiome.grassLight.b -= 2;
	}

	//Adapt dark grass
	if (currentBiome.grassDark.r != biomes[biomeIndex].grassDark.r) 
	{
		currentBiome.grassDark.r < biomes[biomeIndex].grassDark.r ? currentBiome.grassDark.r += 2 : currentBiome.grassDark.r -= 2;
	}
	if (currentBiome.grassDark.g != biomes[biomeIndex].grassDark.g) 
	{
		currentBiome.grassDark.g < biomes[biomeIndex].grassDark.g ? currentBiome.grassDark.g += 2 : currentBiome.grassDark.g -= 2;
	}
	if (currentBiome.grassDark.b != biomes[biomeIndex].grassDark.b) 
	{
		currentBiome.grassDark.b < biomes[biomeIndex].grassDark.b ? currentBiome.grassDark.b += 2 : currentBiome.grassDark.b -= 2;
	}

	//Adapt light rumble
	if (currentBiome.rumbleLight.r != biomes[biomeIndex].rumbleLight.r) 
	{
		currentBiome.rumbleLight.r < biomes[biomeIndex].rumbleLight.r ? currentBiome.rumbleLight.r += 2 : currentBiome.rumbleLight.r -= 2;
	}
	if (currentBiome.rumbleLight.g != biomes[biomeIndex].rumbleLight.g) 
	{
		currentBiome.rumbleLight.g < biomes[biomeIndex].rumbleLight.g ? currentBiome.rumbleLight.g += 2 : currentBiome.rumbleLight.g -= 2;
	}
	if (currentBiome.rumbleLight.b != biomes[biomeIndex].rumbleLight.b) 
	{
		currentBiome.rumbleLight.b < biomes[biomeIndex].rumbleLight.b ? currentBiome.rumbleLight.b += 2 : currentBiome.rumbleLight.b -= 2;
	}

	//Adapt dark rumble
	if (currentBiome.rumbleDark.r != biomes[biomeIndex].rumbleDark.r) 
	{
		currentBiome.rumbleDark.r < biomes[biomeIndex].rumbleDark.r ? currentBiome.rumbleDark.r += 2 : currentBiome.rumbleDark.r -= 2;
	}
	if (currentBiome.rumbleDark.g != biomes[biomeIndex].rumbleDark.g) 
	{
		currentBiome.rumbleDark.g < biomes[biomeIndex].rumbleDark.g ? currentBiome.rumbleDark.g += 2 : currentBiome.rumbleDark.g -= 2;
	}
	if (currentBiome.rumbleDark.b != biomes[biomeIndex].rumbleDark.b) 
	{
		currentBiome.rumbleDark.b < biomes[biomeIndex].rumbleDark.b ? currentBiome.rumbleDark.b += 2 : currentBiome.rumbleDark.b -= 2;
	}

	//Adapt road
	if (currentBiome.roadColor.r != biomes[biomeIndex].roadColor.r) 
	{
		currentBiome.roadColor.r < biomes[biomeIndex].roadColor.r ? currentBiome.roadColor.r += 2 : currentBiome.roadColor.r -= 2;
	}
	if (currentBiome.roadColor.g != biomes[biomeIndex].roadColor.g) 
	{
		currentBiome.roadColor.g < biomes[biomeIndex].roadColor.g ? currentBiome.roadColor.g += 2 : currentBiome.roadColor.g -= 2;
	}
	if (currentBiome.roadColor.b != biomes[biomeIndex].roadColor.b) 
	{
		currentBiome.roadColor.b < biomes[biomeIndex].roadColor.b ? currentBiome.roadColor.b += 2 : currentBiome.roadColor.b -= 2;
	}

	//Adapt sky
	if (currentBiome.skyColor.r != biomes[biomeIndex].skyColor.r) 
	{
		currentBiome.skyColor.r < biomes[biomeIndex].skyColor.r ? currentBiome.skyColor.r += 2 : currentBiome.skyColor.r -= 2;
	}
	if (currentBiome.skyColor.g != biomes[biomeIndex].skyColor.g) 
	{
		currentBiome.skyColor.g < biomes[biomeIndex].skyColor.g ? currentBiome.skyColor.g += 2 : currentBiome.skyColor.g -= 2;
	}
	if (currentBiome.skyColor.b != biomes[biomeIndex].skyColor.b) 
	{
		currentBiome.skyColor.b < biomes[biomeIndex].skyColor.b ? currentBiome.skyColor.b += 2 : currentBiome.skyColor.b -= 2;
	}

	currentBiome.background1 = biomes[biomeIndex].background1;
	currentBiome.background2 = biomes[biomeIndex].background2;
}


//Avoid a targetVariation inferior to -50 when calling ChangeAltitude(). 
//It works, but the slope down is so steep it makes it look like the bike is flying.
void ModuleSceneRace::ChangeAltitude(float &altitudeVariation, float targetVariation, int currentSegment, int startingSegment, int endSegment, int heldSegments) 
{
	int segmentsToMidpoint = (endSegment - startingSegment - heldSegments) / 2;
	float variation = (float)targetVariation / segmentsToMidpoint;

	if (currentSegment <= startingSegment + segmentsToMidpoint) 
	{
		altitudeVariation += variation;
	}
	else if (currentSegment >= startingSegment + segmentsToMidpoint + heldSegments) 
	{
		altitudeVariation -= variation;
	}
	if (currentSegment == endSegment) 
	{
		altitudeVariation = 0;
	}
}


void ModuleSceneRace::ResetRace() 
{
	LOG("Resetting Race")

	biomeIndex = 0;

	currentBiome = biomes[biomeIndex];
	currentBiome.background1 = biomes[biomeIndex].background1;
	currentBiome.background2 = biomes[biomeIndex].background2;
	currentBiome.grassDark = biomes[biomeIndex].grassDark;
	currentBiome.grassLight = biomes[biomeIndex].grassLight;
	currentBiome.roadColor = biomes[biomeIndex].roadColor;
	currentBiome.rumbleDark = biomes[biomeIndex].rumbleDark;
	currentBiome.rumbleLight = biomes[biomeIndex].rumbleLight;
	currentBiome.skyColor = biomes[biomeIndex].skyColor;

	rival1->currentAnimation = &greenRivalTurnsLeft;
	rival1->z = 11;
	rival1->speed = 1.1f;
	rival1->x = -0.9f;
	rival1->isYellow = true;

	rival2->currentAnimation = &greenRivalStraight;
	rival2->z = 14;
	rival2->speed = 1.4f;
	rival2->x = -0.5f;

	rival3->currentAnimation = &greenRivalStraight;
	rival3->z = 17;
	rival3->speed = 1.5f;
	rival3->x = -0.1f;
	rival3->isYellow = true;
	rival3->reincident = false;

	rival4->currentAnimation = &greenRivalStraight;
	rival4->z = 14;
	rival4->speed = 1.3f;
	rival4->x = 0.3f;

	rival5->currentAnimation = &greenRivalStraight;
	rival5->z = 11;
	rival5->speed = 1.2f;
	rival5->x = 0.7f;
	rival5->isYellow = true;

	endPlayer->currentAnimation = &falsePlayer;
	endPlayer->z = 0;
	endPlayer->speed = 0;
	endPlayer->x = -0.1f;

	rival5->z = 11;
	rival5->x = 0.7f;

	pos = -20;

	checkPointIndex = 0;
}

ModuleSceneRace::biome::biome()
{
}
