#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFontManager.h"
#include "ModulePlayer.h"
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
	leaningLeft.speed = 0.2f;

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
	unLeanLeft.speed = 0.2f;

	// Leaning Left
	leaningRight.frames.push_back({ 91, 596, 32, 72 });
	leaningRight.frames.push_back({ 129, 596, 32, 72 });
	leaningRight.frames.push_back({ 168, 596, 35, 72 });
	leaningRight.frames.push_back({ 206, 596, 35, 72 });
	leaningRight.frames.push_back({ 244, 596, 45, 72 });
	leaningRight.frames.push_back({ 295, 596, 45, 72 });
	leaningRight.loop = false;
	leaningRight.speed = 0.2f;

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
	unLeanRight.speed = 0.2f;

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
	leaningLeftBraking.speed = 0.2f;

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
	unLeanLeftBraking.speed = 0.2f;

	// Leaning Left Braking
	leaningRightBraking.frames.push_back({ 91, 676, 32, 72 });
	leaningRightBraking.frames.push_back({ 129, 676, 32, 72 });
	leaningRightBraking.frames.push_back({ 168, 676, 35, 72 });
	leaningRightBraking.frames.push_back({ 206, 676, 35, 72 });
	leaningRightBraking.frames.push_back({ 244, 676, 45, 72 });
	leaningRightBraking.frames.push_back({ 295, 676, 45, 72 });
	leaningRightBraking.loop = false;
	leaningRightBraking.speed = 0.2f;

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
	unLeanRightBraking.speed = 0.2f;

	blankSpace = { 525, 280, 8, 8 };
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("bikes.png", 255, 0, 204);

	destroyed = false;
	position.x = SCREEN_WIDTH / 2 - 16 * 2;
	position.y = SCREEN_HEIGHT - 73 * 2;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

update_status ModulePlayer::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) 
	{
		braking = true;
	}
	else
	{
		braking = false;
	}

	if (speed < currentMaxSpeed) 
	{
		speed = speed + acceleration;
	}
	else if (speed > currentMaxSpeed)
	{
		speed = speed - acceleration;
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
				if (speed >= maxSpeedRunning - 5 && App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
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

	ManageAnimations();
		

	// Draw everything --------------------------------------
	PrintSpeed();

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), 0.0f, false, false, 2, 2);

	return UPDATE_CONTINUE;
}

void ModulePlayer::PrintSpeed() {
	int numberThreshold = 100;
	int helper = speed;
	int digitPositionX = 32;
	bool numberInRange = false;

	for (int dig = 3; dig > 0; dig--) {
		if (helper < numberThreshold && !numberInRange) {
			App->renderer->Blit(graphics, (SCREEN_WIDTH / 2) + digitPositionX, 0, &blankSpace, 0.0f, false, false, 2, 2);
		}
		else
		{
			App->font_manager->PrintDigit(helper / numberThreshold, (SCREEN_WIDTH / 2) + digitPositionX, 0, Color(255, 255, 255, 255));
			numberInRange = true;
		}

		helper = helper % numberThreshold;
		numberThreshold = numberThreshold / 10;
		digitPositionX += 16;
	}
}

void ModulePlayer::ManageAnimations() {
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if ((current_animation != &unLeanRight && current_animation != &unLeanRightBraking) && (current_animation->GetCurrentFrame().x == leaningLeft.frames[leaningLeft.frames.size() - 1].x || current_animation->GetCurrentFrame().x == leaningLeftBraking.frames[leaningLeftBraking.frames.size() - 1].x) || current_animation == &leanedLeft || current_animation == &leanedLeftBraking)
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
		if ((current_animation != &unLeanLeft && current_animation != &unLeanLeftBraking) && (current_animation->GetCurrentFrame().x == leaningRight.frames[leaningRight.frames.size() - 1].x || current_animation->GetCurrentFrame().x == leaningRightBraking.frames[leaningRightBraking.frames.size() - 1].x) || current_animation == &leanedRight || current_animation == &leanedRightBraking)
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
				current_animation == &leanedRightBraking;
			}
			else
			{
				current_animation == &leanedRight;
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