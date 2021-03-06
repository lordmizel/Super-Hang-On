#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFontManager.h"
#include "ModulePlayer.h"
#include "ModuleScore.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer(bool active) : Module(active)
{
	// Forward
	forward.frames.push_back({ 91, 280, 32, 72 });
	forward.frames.push_back({ 129, 280, 32, 72 });
	forward.speed = 0.2f;

	// Leaning Left
	leaningLeft.frames.push_back({ 91, 280, 32, 72 });
	leaningLeft.frames.push_back({ 129, 280, 32, 72 });
	leaningLeft.frames.push_back({ 168, 280, 35, 72 });
	leaningLeft.frames.push_back({ 206, 280, 35, 72 });
	leaningLeft.frames.push_back({ 244, 280, 45, 72 });
	leaningLeft.frames.push_back({ 295, 280, 45, 72 });
	leaningLeft.loop = false;
	leaningLeft.speed = 0.05f;

	// Leaned Left
	leanedLeft.frames.push_back({ 345, 280, 62, 72 });
	leanedLeft.frames.push_back({ 410, 280, 62, 72 });
	leanedLeft.speed = 0.2f;

	// Unlean Left
	unLeanLeft.frames.push_back({ 295, 280, 45, 72 });
	unLeanLeft.frames.push_back({ 244, 280, 45, 72 });
	unLeanLeft.frames.push_back({ 206, 280, 35, 72 });
	unLeanLeft.frames.push_back({ 168, 280, 35, 72 });
	unLeanLeft.frames.push_back({ 129, 280, 32, 72 });
	unLeanLeft.frames.push_back({ 91, 280, 32, 72 });
	unLeanLeft.loop = false;
	unLeanLeft.speed = 0.1f;

	// Leaning Left
	leaningRight.frames.push_back({ 91, 596, 32, 72 });
	leaningRight.frames.push_back({ 129, 596, 32, 72 });
	leaningRight.frames.push_back({ 168, 596, 35, 72 });
	leaningRight.frames.push_back({ 206, 596, 35, 72 });
	leaningRight.frames.push_back({ 244, 596, 45, 72 });
	leaningRight.frames.push_back({ 295, 596, 45, 72 });
	leaningRight.loop = false;
	leaningRight.speed = 0.05f;

	// Leaned Left
	leanedRight.frames.push_back({ 345, 596, 62, 72 });
	leanedRight.frames.push_back({ 410, 596, 62, 72 });
	leanedRight.speed = 0.2f;

	// Unlean Right
	unLeanRight.frames.push_back({ 295, 596, 45, 72 });
	unLeanRight.frames.push_back({ 244, 596, 45, 72 });
	unLeanRight.frames.push_back({ 206, 596, 35, 72 });
	unLeanRight.frames.push_back({ 168, 596, 35, 72 });
	unLeanRight.frames.push_back({ 129, 596, 32, 72 });
	unLeanRight.frames.push_back({ 91, 596, 32, 72 });
	unLeanRight.loop = false;
	unLeanRight.speed = 0.1f;

	// Forward Braking
	forwardBraking.frames.push_back({ 91, 360, 32, 72 });
	forwardBraking.frames.push_back({ 129, 360, 32, 72 });
	forwardBraking.speed = 0.2f;

	// Leaning Left Braking
	leaningLeftBraking.frames.push_back({ 91, 360, 32, 72 });
	leaningLeftBraking.frames.push_back({ 129, 360, 32, 72 });
	leaningLeftBraking.frames.push_back({ 168, 360, 35, 72 });
	leaningLeftBraking.frames.push_back({ 206, 360, 35, 72 });
	leaningLeftBraking.frames.push_back({ 244, 360, 45, 72 });
	leaningLeftBraking.frames.push_back({ 295, 360, 45, 72 });
	leaningLeftBraking.loop = false;
	leaningLeftBraking.speed = 0.05f;

	// Leaned Left Braking
	leanedLeftBraking.frames.push_back({ 345, 360, 62, 72 });
	leanedLeftBraking.frames.push_back({ 410, 360, 62, 72 });
	leanedLeftBraking.speed = 0.2f;

	// Unlean Left Braking
	unLeanLeftBraking.frames.push_back({ 295, 360, 45, 72 });
	unLeanLeftBraking.frames.push_back({ 244, 360, 45, 72 });
	unLeanLeftBraking.frames.push_back({ 206, 360, 35, 72 });
	unLeanLeftBraking.frames.push_back({ 168, 360, 35, 72 });
	unLeanLeftBraking.frames.push_back({ 129, 360, 32, 72 });
	unLeanLeftBraking.frames.push_back({ 91, 360, 32, 72 });
	unLeanLeftBraking.loop = false;
	unLeanLeftBraking.speed = 0.1f;

	// Leaning Left Braking
	leaningRightBraking.frames.push_back({ 91, 676, 32, 72 });
	leaningRightBraking.frames.push_back({ 129, 676, 32, 72 });
	leaningRightBraking.frames.push_back({ 168, 676, 35, 72 });
	leaningRightBraking.frames.push_back({ 206, 676, 35, 72 });
	leaningRightBraking.frames.push_back({ 244, 676, 45, 72 });
	leaningRightBraking.frames.push_back({ 295, 676, 45, 72 });
	leaningRightBraking.loop = false;
	leaningRightBraking.speed = 0.05f;

	// Leaned Left Braking
	leanedRightBraking.frames.push_back({ 345, 676, 62, 72 });
	leanedRightBraking.frames.push_back({ 410, 676, 62, 72 });
	leanedRightBraking.speed = 0.2f;

	// Unlean Right Braking
	unLeanRightBraking.frames.push_back({ 295, 676, 45, 72 });
	unLeanRightBraking.frames.push_back({ 244, 676, 45, 72 });
	unLeanRightBraking.frames.push_back({ 206, 676, 35, 72 });
	unLeanRightBraking.frames.push_back({ 168, 676, 35, 72 });
	unLeanRightBraking.frames.push_back({ 129, 676, 32, 72 });
	unLeanRightBraking.frames.push_back({ 91, 676, 32, 72 });
	unLeanRightBraking.loop = false;
	unLeanRightBraking.speed = 0.1f;

	// Small crash
	smallCrash.frames.push_back({ 0, 0, 220, 124 });
	smallCrash.frames.push_back({ 220, 0, 220, 124 });
	smallCrash.frames.push_back({ 440, 0, 220, 124 });
	smallCrash.frames.push_back({ 660, 0, 220, 124 });
	smallCrash.frames.push_back({ 880, 0, 220, 124 });
	smallCrash.frames.push_back({ 1100, 0, 220, 124 });
	smallCrash.frames.push_back({ 0, 124, 220, 124 });
	smallCrash.frames.push_back({ 220, 124, 220, 124 });
	smallCrash.frames.push_back({ 440, 124, 220, 124 });
	smallCrash.frames.push_back({ 660, 124, 220, 124 });
	smallCrash.frames.push_back({ 880, 124, 220, 124 });
	smallCrash.frames.push_back({ 1100, 124, 220, 124 });
	smallCrash.frames.push_back({ 0, 248, 220, 124 });
	smallCrash.frames.push_back({ 0, 248, 220, 124 });
	smallCrash.frames.push_back({ 0, 248, 220, 124 });
	smallCrash.frames.push_back({ 0, 248, 220, 124 });
	smallCrash.frames.push_back({ 0, 248, 220, 124 });
	smallCrash.frames.push_back({ 0, 248, 220, 124 });
	smallCrash.frames.push_back({ 99, 99, 0, 0 });
	smallCrash.loop = false;
	smallCrash.speed = 0.04f;

	// Big crash
	bigCrash.frames.push_back({0, 373, 171, 144});
	bigCrash.frames.push_back({ 171, 373, 171, 144 });
	bigCrash.frames.push_back({ 342, 373, 171, 144 });
	bigCrash.frames.push_back({ 513, 373, 171, 144 });
	bigCrash.frames.push_back({ 684, 373, 171, 144 });
	bigCrash.frames.push_back({ 855, 373, 171, 144 });
	bigCrash.frames.push_back({ 1026, 373, 171, 144 });
	bigCrash.frames.push_back({ 0, 517, 171, 144 });
	bigCrash.frames.push_back({ 171, 517, 171, 144 });
	bigCrash.frames.push_back({ 342, 517, 171, 144 });
	bigCrash.frames.push_back({ 513, 517, 171, 144 });
	bigCrash.frames.push_back({ 513, 517, 171, 144 });
	bigCrash.frames.push_back({ 513, 517, 171, 144 });
	bigCrash.frames.push_back({ 513, 517, 171, 144 });
	bigCrash.frames.push_back({ 513, 517, 171, 144 });
	bigCrash.frames.push_back({ 513, 517, 171, 144 });
	bigCrash.frames.push_back({ 99, 99, 0, 0 });
	bigCrash.loop = false;
	bigCrash.speed = 0.04f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	state = BEFORE_RACE;
	graphics = App->textures->Load("Game/bikes.png", 255, 0, 204);
	crashes = App->textures->Load("Game/falls.png", 224, 64, 32);

	position.x = SCREEN_WIDTH / 2 - 16 * 2;
	position.y = SCREEN_HEIGHT - 73 * 2;

	timeWaitingAtStart.SetTime(4);
	timeWaitingAtStart.Start();

	timeLeftInRace.SetTime(30);

	if (collision == 0) 
	{
		collision = App->audio->LoadFx("Game/collision.wav");
	}

	if (crash == 0) 
	{
		crash = App->audio->LoadFx("Game/crash.wav");
	}

	if (scream == 0) 
	{
		scream = App->audio->LoadFx("Game/wilhelm.wav");
	}

	if (skid == 0) 
	{
		skid = App->audio->LoadFx("Game/skid.wav");
	}

	ResetPlayer();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->textures->Unload(crashes);

	return true;
}

update_status ModulePlayer::Update()
{
	//Change speed depending on max velocity
	if (state == RACING || state == CRASHING || state == OUT_OF_CONTROL) 
	{
		if (speed < currentMaxSpeed)
		{
			speed = speed + acceleration;
		}
		else if (speed > currentMaxSpeed)
		{
			if (braking == true || offRoad == true) 
			{
				speed = speed - acceleration * 2;
			}
			else 
			{
				speed = speed - acceleration;
			}
			
		}
	}

	switch (state) 
	{
	case(BEFORE_RACE):
		current_animation = &forward;
		
		App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - forward.frames[0].w, position.y, &forward.frames[0], 0.0f, false, false, 2, 2);
		
		timeWaitingAtStart.Update();
		if (timeWaitingAtStart.IsExpired()) 
		{
			timeLeftInRace.Start();
			App->audio->PlayMusic(App->audio->musicChosen, 0.0f);
			state = RACING;
		}
		break;

	case(RACING):

		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) 
		{
			Pause();
		}

		ManagePositionX();

		ManageSpeed();

		ManageAnimations();

		App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - current_animation->GetCurrentFrame().w, position.y, &(current_animation->GetCurrentFrame()), 0.0f, false, false, 2, 2);
		break;

	case(CRASHING):
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) 
		{
			Pause();
		}

		if (speed > 200 && current_animation != &smallCrash) 
		{
			current_animation = &bigCrash;
		}
		else if (current_animation != &bigCrash)
		{
			current_animation = &smallCrash;
		}
		
		if (speed > 80) 
		{
			speed = 80;
			current_animation->Reset();
		}

		currentMaxSpeed = 0;

		App->renderer->Blit(crashes, SCREEN_WIDTH / 2 - current_animation->GetCurrentFrame().w + 50, SCREEN_HEIGHT - current_animation->GetCurrentFrame().h * 2, &(current_animation->GetCurrentFrame()), 0.0f, false, false, 2, 2);
		if (current_animation->GetCurrentFrame().x == current_animation->frames[current_animation->frames.size() - 1].x && current_animation->GetCurrentFrame().y == current_animation->frames[current_animation->frames.size() - 1].y) 
		{
			state = RECOVERING;
		}
		break;

	case(RECOVERING):
		speed = 0;
		if (positionX > 0) 
		{
			positionX -= 30;
		}
		else if (positionX < 0) 
		{
			positionX += 30;
		}
		if(positionX > -30 && positionX < 30)
		{
			positionX = 0;
			current_animation = &forward;
			state = RACING;
		}

		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) 
		{
			Pause();
		}

		break;

	case(OUT_OF_CONTROL):
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			Pause();
		}

		if (speed > 90) 
		{
			speed = 90;
		}
		currentMaxSpeed = 90;
		if (deviateRight)
		{
			current_animation = &leanedRight;
			positionX += 20;
		}
		else 
		{
			current_animation = &leanedLeft;
			positionX -= 20;
		}
		timeOutOfControl.Update();
		if (timeOutOfControl.IsExpired()) 
		{
			state = RACING;
		}
		App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - current_animation->GetCurrentFrame().w, position.y, &(current_animation->GetCurrentFrame()), 0.0f, false, false, 2, 2);
		break;

	case(GAME_OVER):
		gameOverTimer.Update();
		if (gameOverTimer.IsExpired()) 
		{
			App->score->SaveLapData();
			App->score->ValidateScoreEntry(timeLeftInRace.GetTotalTimeElapsed());
			App->audio->PlayMusic("Game/scoreboard.ogg", 0.0f);
			state = SCORE_SCREEN;
		}

		if (previousState == CRASHING) 
		{
			App->renderer->Blit(crashes, SCREEN_WIDTH / 2 - current_animation->GetCurrentFrame().w + 50, SCREEN_HEIGHT - current_animation->GetCurrentFrame().h * 2, &(current_animation->GetCurrentFrame()), 0.0f, false, false, 2, 2);
		}
		else 
		{
			App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - current_animation->GetCurrentFrame().w, position.y, &(current_animation->GetCurrentFrame()), 0.0f, false, false, 2, 2);
		}
		break;

	case(SCORE_SCREEN):
		if (!raceHasEnded) 
		{
			App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - current_animation->GetCurrentFrame().w, position.y, &(current_animation->GetCurrentFrame()), 0.0f, false, false, 2, 2);
		}
		break;

	case(PAST_GOAL):
		speed = 0;
		if (positionX > 0)
		{
			positionX -= 30;
		}
		else if (positionX < 0)
		{
			positionX += 30;
		}
		if (positionX > -30 && positionX < 30)
		{
			positionX = 0;
		}

		App->ui->ShowLapTimes();
		timeLeftInRace.Pause();

		timePastGoal.Update();
		if (timePastGoal.IsExpired())
		{
			App->score->currentScore.score = App->score->currentScore.score + (int)timeLeftInRace.GetRemainingTime() * 1000000;
			raceEnded = true;
			state = GOING_TO_END;
		}
		break;

	case(GOING_TO_END):
		speed = 200;
		App->ui->ShowBonusPoints((int)timeLeftInRace.GetRemainingTime());
		raceHasEnded = true;
		break;

	case(END_SCENE):
		speed = 0;
		timeEndScene.Update();

		if (timeEndScene.IsExpired()) {
			App->score->SaveLapData();
			App->score->ValidateScoreEntry(timeLeftInRace.GetTotalTimeElapsed());
			timeLeftInRace.Resume();
			App->audio->PlayMusic("Game/scoreboard.ogg", 0.0f);
			state = SCORE_SCREEN;
		}
		break;

	case(PAUSE):
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			state = previousState;
			current_animation->speed = previousAnimationSpeed;
			timeOutOfControl.Resume();
			timeLeftInRace.Resume();
		}

		if (previousState == CRASHING) 
		{
			App->renderer->Blit(crashes, SCREEN_WIDTH / 2 - current_animation->GetCurrentFrame().w + 50, SCREEN_HEIGHT - current_animation->GetCurrentFrame().h * 2, &(current_animation->GetCurrentFrame()), 0.0f, false, false, 2, 2);
		}
		else 
		{
			App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - current_animation->GetCurrentFrame().w, position.y, &(current_animation->GetCurrentFrame()), 0.0f, false, false, 2, 2);
		}
		
		break;
	}
	
	//Stuff that takes action for more than one state

	if (state == RACING || state == CRASHING || state == RECOVERING || state == OUT_OF_CONTROL) 
	{
		timeLeftInRace.Update();
		if (timeLeftInRace.IsExpired())
		{
			gameOverTimer.SetTime(5);
			gameOverTimer.Start();
			current_animation->speed = 0.0f;
			state = GAME_OVER;
		}
	}

	if (state != PAUSE && state != GAME_OVER && state != SCORE_SCREEN)
	{
		App->score->UpdateScore(App->player->GetSpeed());
	}

	if (state != SCORE_SCREEN)
	{
		App->ui->ShowUI();
	}
	else
	{
		App->ui->ShowRankings();
	}

	collider = { SCREEN_WIDTH / 2 - current_animation->GetCurrentFrame().w + 40, SCREEN_HEIGHT - 50, (current_animation->GetCurrentFrame().w - 40) * 2, 50 };
	return UPDATE_CONTINUE;
}

void ModulePlayer::ManageSpeed() 
{
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		braking = true;
	}
	else
	{
		braking = false;
	}

	if (braking)
	{
		//Player is braking
		currentMaxSpeed = maxSpeedBraking;
	}
	else
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			//Player is using the accelerator
			if (!offRoad)
			{
				if (speed >= maxSpeedRunning && App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
				{
					//Player uses nitro
					currentMaxSpeed = maxSpeedNitro;
				}
				else
				{
					currentMaxSpeed = maxSpeedRunning;
				}
			}
			else
			{
				//Player is off-track
				currentMaxSpeed = maxSpeedOffTrack;
			}
		}
		else
		{
			//Player isn't using the accelerator
			currentMaxSpeed = maxSpeedAuto;
		}
	}
}

void ModulePlayer::ManagePositionX()
{
	if (current_animation == &leaningLeft || current_animation == &unLeanLeft || current_animation == &leaningLeftBraking || current_animation == &unLeanLeftBraking)
	{
		positionX -= movementX / 2;
		if (positionX > -maxXPosition)
		{
			absoluteX -= movementX / 2;
		}
	}
	else if (current_animation == &leanedLeft || current_animation == &leanedLeftBraking)
	{
		positionX -= movementX;
		if (positionX > -maxXPosition)
		{
			absoluteX -= movementX;
		}
	}
	else if (current_animation == &leaningRight || current_animation == &unLeanRight || current_animation == &leaningRightBraking || current_animation == &unLeanRightBraking)
	{
		positionX += movementX / 2;
		if (positionX < maxXPosition)
		{
			absoluteX += movementX / 2;
		}
	}
	else if (current_animation == &leanedRight || current_animation == &leanedRightBraking)
	{
		positionX += movementX;
		if (positionX < maxXPosition)
		{
			absoluteX += movementX;
		}
	}

	//Control maximum distance the player can go from the road
	if (positionX > maxXPosition)
	{
		positionX = (float)maxXPosition;
	}
	if (positionX < -maxXPosition)
	{
		positionX = -(float)maxXPosition;
	}

	//Control if player is offroad
	if (positionX > ROAD_WIDTH)
	{
		offRoad = true;
	}
	else if (positionX < -ROAD_WIDTH)
	{
		offRoad = true;
	}
	else
	{
		offRoad = false;
	}
}

void ModulePlayer::ManageAnimations() 
{
	//This is a nightmare
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if ((current_animation != &unLeanRight && current_animation != &unLeanRightBraking) && (current_animation->GetCurrentFrame().x == leaningLeft.frames[leaningLeft.frames.size() - 1].x 
			|| current_animation->GetCurrentFrame().x == leaningLeftBraking.frames[leaningLeftBraking.frames.size() - 1].x) 
			|| current_animation == &leanedLeft || current_animation == &leanedLeftBraking)
		{
			if (braking)
			{
				current_animation = &leanedLeftBraking;
			}
			else
			{
				current_animation = &leanedLeft;
			}
		}
		else if (current_animation == &forward || current_animation == &forwardBraking)
		{
			if (braking)
			{
				leaningLeftBraking.Reset();
				current_animation = &leaningLeftBraking;
			}
			else
			{
				leaningLeft.Reset();
				current_animation = &leaningLeft;
			}
		}
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if ((current_animation != &unLeanLeft && current_animation != &unLeanLeftBraking) && (current_animation->GetCurrentFrame().x == leaningRight.frames[leaningRight.frames.size() - 1].x 
			|| current_animation->GetCurrentFrame().x == leaningRightBraking.frames[leaningRightBraking.frames.size() - 1].x) 
			|| current_animation == &leanedRight || current_animation == &leanedRightBraking)
		{
			if (braking)
			{
				current_animation = &leanedRightBraking;
			}
			else
			{
				current_animation = &leanedRight;
			}
		}
		else if (current_animation == &forward || current_animation == &forwardBraking)
		{
			if (braking)
			{
				leaningRightBraking.Reset();
				current_animation = &leaningRightBraking;
			}
			else
			{
				leaningRight.Reset();
				current_animation = &leaningRight;
			}
		}
		if (current_animation == &leanedRight || current_animation == &leanedRightBraking) {
			if (braking)
			{
				current_animation = &leanedRightBraking;
			}
			else
			{
				current_animation = &leanedRight;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && (current_animation == &leanedLeft || current_animation == &leaningLeft || current_animation == &leanedLeftBraking || current_animation == &leaningLeftBraking))
	{
		if (braking)
		{
			unLeanLeftBraking.Reset();
			current_animation = &unLeanLeftBraking;
		}
		else
		{
			unLeanLeft.Reset();
			current_animation = &unLeanLeft;
		}
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && (current_animation == &leanedRight || current_animation == &leaningRight || current_animation == &leanedRightBraking || current_animation == &leaningRightBraking))
	{
		if (braking)
		{
			unLeanRightBraking.Reset();
			current_animation = &unLeanRightBraking;
		}
		else
		{
			unLeanRight.Reset();
			current_animation = &unLeanRight;
		}
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && current_animation != &unLeanLeft && current_animation != &unLeanRight && current_animation != &unLeanLeftBraking && current_animation != &unLeanRightBraking)
	{
		if (braking)
		{
			current_animation = &forwardBraking;
		}
		else
		{
			current_animation = &forward;
		}
	}

	if ((current_animation == &unLeanLeft && current_animation->GetCurrentFrame().x == unLeanLeft.frames[leaningLeft.frames.size() - 1].x)
		|| (current_animation == &unLeanRight && current_animation->GetCurrentFrame().x == unLeanRight.frames[leaningRight.frames.size() - 1].x)
		|| (current_animation == &unLeanLeftBraking && current_animation->GetCurrentFrame().x == unLeanLeftBraking.frames[leaningLeftBraking.frames.size() - 1].x)
		|| (current_animation == &unLeanRightBraking && current_animation->GetCurrentFrame().x == unLeanRightBraking.frames[leaningRightBraking.frames.size() - 1].x))
	{
		if (braking)
		{
			current_animation = &forwardBraking;
		}
		else
		{
			current_animation = &forward;
		}
	}
}

void ModulePlayer::DetectCollision(const SDL_Rect r, const collision_types typeOfCollision, const float x)
{
	collision_types type = typeOfCollision;
	if (state == RACING || state == OUT_OF_CONTROL)
	{
		if (!(collider.x > r.x + r.w || collider.x + collider.w < r.x || collider.y > r.y + r.h || collider.y + collider.h < r.y))
		{
			switch (type)
			{
			case OBSTACLE:
				if (speed > 200) 
				{
					App->audio->PlayFx(crash, 0);
					App->audio->PlayFx(scream, 0);
				}
				else 
				{
					App->audio->PlayFx(crash, 0);
				}
				state = CRASHING;
				break;

			case RIVAL:
				timeOutOfControl.SetTime(1);
				timeOutOfControl.Start();
				if (x < SCREEN_WIDTH / 2)
				{
					deviateRight = true;
				}
				else
				{
					deviateRight = false;
				}
				App->audio->PlayFx(collision, 0);
				App->audio->PlayFx(skid, 0);
				state = OUT_OF_CONTROL;
				break;
			}
		}
	}
}

void ModulePlayer::CenterMaxX(const float max)
{
	if (maxXPosition > max)
	{
		maxXPosition -= 30;
	}
	else
	{
		maxXPosition = (int)max;
	}
}

void ModulePlayer::Pause() 
{
	previousAnimationSpeed = current_animation->speed;
	current_animation->speed = 0.0f;
	previousState = state;
	timeOutOfControl.Pause();
	state = PAUSE;
}

void ModulePlayer::ResetPlayer() 
{
	maxXPosition = ROAD_WIDTH * 4;
	raceHasEnded = false;
	positionX = 0;
	speed = 0;
	timeLeftInRace.ResetTotalTime();
	raceEnded = false;

	//Animation bug patch
	leaningLeft.speed = 0.05f;
	leanedLeft.speed = 0.2f;
	unLeanLeft.speed = 0.1f;
	leaningRight.speed = 0.05f;
	leanedRight.speed = 0.2f;
	unLeanRight.speed = 0.1f;
	leaningLeftBraking.speed = 0.05f;
	leanedLeftBraking.speed = 0.2f;
	unLeanLeftBraking.speed = 0.1f;
	leaningRightBraking.speed = 0.05f;
	leanedRightBraking.speed = 0.2f;
	unLeanRightBraking.speed = 0.1f;
	bigCrash.speed = 0.04f;
	smallCrash.speed = 0.04f;
}