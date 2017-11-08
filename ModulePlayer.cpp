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

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;

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
		

		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	}

	return UPDATE_CONTINUE;
}

// TODO 13: Make so is the laser collides, it is removed and create an explosion particle at its position

// TODO 14: Make so if the player collides, it is removed and create few explosions at its positions
// then fade away back to the first screen (use the "destroyed" bool already created 
// You will need to create, update and destroy the collider with the player
