#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
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
	state = RACING;
	graphics = App->textures->Load("bikes.png", 255, 0, 204);
	crashes = App->textures->Load("falls.png", 224, 64, 32);

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

void ModulePlayer::DetectCollision(SDL_Rect r, collision_types typeOfCollision)
{
	collision_types type = typeOfCollision;
	if (!(collider.x > r.x + r.w || collider.x + collider.w < r.x || collider.y > r.y + r.h || collider.y + collider.h < r.y)) {
		switch (type) {
		case OBSTACLE:
			state = CRASHING;
			break;
		case RIVAL:
			break;
		}
		
	}
}

update_status ModulePlayer::Update()
{
		if (speed < currentMaxSpeed)
		{
			speed = speed + acceleration;
		}
		else if (speed > currentMaxSpeed)
		{
			speed = speed - acceleration;
		}

		switch (state) {
		case(BEFORE_RACE):
			break;

		case(RACING):
			//TODO: DELETE THIS WHOLE IF STATEMENT!! ONLY FOR DEBUG!!
			if (App->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT)
			{
				state = CRASHING;
			}

			if (current_animation == &leaningLeft || current_animation == &unLeanLeft || current_animation == &leaningLeftBraking || current_animation == &unLeanLeftBraking) {
				positionX -= movementX / 2;
				if (positionX > -ROAD_WIDTH * 4) {
					absoluteX -= movementX / 2;
				}
			}
			else if (current_animation == &leanedLeft || current_animation == &leanedLeftBraking) {
				positionX -= movementX;
				if (positionX > -ROAD_WIDTH * 4) {
					absoluteX -= movementX;
				}
			}
			else if (current_animation == &leaningRight || current_animation == &unLeanRight || current_animation == &leaningRightBraking || current_animation == &unLeanRightBraking) {
				positionX += movementX / 2;
				if (positionX < ROAD_WIDTH * 4) {
					absoluteX += movementX / 2;
				}
			}
			else if (current_animation == &leanedRight || current_animation == &leanedRightBraking) {
				positionX += movementX;
				if (positionX < ROAD_WIDTH * 4) {
					absoluteX += movementX;
				}
			}

			if (positionX > ROAD_WIDTH * 4) {
				positionX = ROAD_WIDTH * 4;
			}
			if (positionX < -ROAD_WIDTH * 4) {
				positionX = -ROAD_WIDTH * 4;
			}

			if (positionX > ROAD_WIDTH) {
				offRoad = true;
			}
			else if (positionX < -ROAD_WIDTH) {
				offRoad = true;
			}
			else {
				offRoad = false;
			}

			ManageSpeed();

			ManageAnimations();

			App->renderer->Blit(graphics, SCREEN_WIDTH / 2 - current_animation->GetCurrentFrame().w, position.y, &(current_animation->GetCurrentFrame()), 0.0f, false, false, 2, 2);
			break;

		case(CRASHING):
		if (speed > 200 && current_animation != &smallCrash) {
			current_animation = &bigCrash;
		}
		else if (current_animation != &bigCrash){
			current_animation = &smallCrash;
		}
		
		if (speed > 80) {
			speed = 80;
			current_animation->Reset();
		}
		currentMaxSpeed = 0;
		App->renderer->Blit(crashes, SCREEN_WIDTH / 2 - current_animation->GetCurrentFrame().w + 50, SCREEN_HEIGHT - current_animation->GetCurrentFrame().h * 2, &(current_animation->GetCurrentFrame()), 0.0f, false, false, 2, 2);
		if (current_animation->GetCurrentFrame().x == current_animation->frames[current_animation->frames.size() - 1].x && current_animation->GetCurrentFrame().y == current_animation->frames[current_animation->frames.size() - 1].y) {
			state = RECOVERING;
		}
		break;

	case(RECOVERING):
		speed = 0;
		if (positionX > 0) {
			positionX -= 20;
		}
		else if (positionX < 0) {
			positionX += 20;
		}
		if(positionX > -20 && positionX < 20)
		{
			positionX = 0;
			state = RACING;
		}

		break;

	case(AFTER_RACE):
		break;
	}
	
		collider = { SCREEN_WIDTH / 2 - current_animation->GetCurrentFrame().w, SCREEN_HEIGHT - 50, current_animation->GetCurrentFrame().w * 2, 50 };
		SDL_RenderFillRect(App->renderer->renderer, &collider);
	
	return UPDATE_CONTINUE;
}

void ModulePlayer::ManageSpeed() {
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

void ModulePlayer::ManageAnimations() {
	//This is a nightmare
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