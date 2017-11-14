#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
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

	blankSpace = { 525, 280, 8, 8 };
	numbers[0] = { 374, 211, 8, 8 };
	numbers[1] = { 294, 211, 8, 8 };
	numbers[2] = { 302, 211, 8, 8 };
	numbers[3] = { 311, 211, 8, 8 };
	numbers[4] = { 320, 211, 8, 8 };
	numbers[5] = { 329, 211, 8, 8 };
	numbers[6] = { 338, 211, 8, 8 };
	numbers[7] = { 347, 211, 8, 8 };
	numbers[8] = { 356, 211, 8, 8 };
	numbers[9] = { 365, 211, 8, 8 };
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("bikes.png", 255, 0, 204);

	destroyed = false;
	position.x = SCREEN_WIDTH/2 - 16;
	position.y = SCREEN_HEIGHT - 73;

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

	if (speed < currentMaxSpeed) 
	{
		speed = speed + acceleration;
	}
	else
	{
		speed = speed - acceleration;
	}

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT)
	{
		//Player is braking
		currentMaxSpeed = maxSpeedBraking;
	}
	else
	{ 
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		{
			//Player is using the accelerator
			if (!offRoad)
			{
				if (speed >= maxSpeedRunning - 5 && App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT)
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

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (current_animation->GetCurrentFrame().x == leaningLeft.frames[leaningLeft.frames.size()-1].x) 
		{
			current_animation = &leanedLeft;
		}
		else if (current_animation != &leaningLeft && current_animation != &leanedLeft)
		{
			leaningLeft.Reset();
			current_animation = &leaningLeft;
		}
	} 
	else if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (current_animation->GetCurrentFrame().x == leaningRight.frames[leaningRight.frames.size() - 1].x) 
		{
			current_animation = &leanedRight;
		}
		else if (current_animation != &leaningRight && current_animation != &leanedRight)
		{
			leaningRight.Reset();
			current_animation = &leaningRight;
		}
	} 

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
	{
		if (current_animation == &leanedLeft || current_animation == &leaningLeft) 
		{
			unLeanLeft.Reset();
			current_animation = &unLeanLeft;
		}
		else if (current_animation == &leanedRight || current_animation == &leaningRight) 
		{
			unLeanRight.Reset();
			current_animation = &unLeanRight;
		}
		else if (current_animation != &unLeanLeft && current_animation != &unLeanRight)
		{
			current_animation = &forward;
		}

		if (current_animation->GetCurrentFrame().x == unLeanLeft.frames[leaningLeft.frames.size() - 1].x || current_animation->GetCurrentFrame().x == unLeanLeft.frames[leaningRight.frames.size() - 1].x)
		{
			current_animation = &forward;
		}
		
	}
		

	// Draw everything --------------------------------------
	if (destroyed == false)
	{
		PrintSpeed();

		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::PrintSpeed() {
	int numberThreshold = 100;
	int helper = speed;
	int digitPositionX = -32;
	bool numberInRange = false;

	for (int dig = 3; dig > 0; dig--) {
		if (helper < numberThreshold && !numberInRange) {
			App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 5 + digitPositionX, 20, &blankSpace);
		}
		else
		{
			App->renderer->Blit(graphics, (SCREEN_WIDTH / 6) * 5 + digitPositionX, 20, &numbers[helper / numberThreshold]);
			numberInRange = true;
		}

		helper = helper % numberThreshold;
		numberThreshold = numberThreshold / 10;
		digitPositionX += 8;
	}
}