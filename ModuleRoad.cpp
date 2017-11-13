#include "ModuleRoad.h"
#include "Application.h"					//////////////////////
#include "ModuleRender.h"					//////////////////////
#include "ModulePlayer.h"
#include "ModuleSceneRace.h"
#include "ModuleWindow.h"
#include <math.h>
#include "SDL\include\SDL.h"

const int ModuleRoad::SEGMENT_DEPTH = 30;
const int ModuleRoad::ROAD_WIDTH = 40;
const int ModuleRoad::RUMBLE_LENGTH = 3;
const int ModuleRoad::CAMERA_DEPTH = 7;
const int ModuleRoad::DRAW_DISTANCE = 10;		//How many roads to draw at a given time
const int ModuleRoad::SEGMENTS_IN_ROAD = RUMBLE_LENGTH * DRAW_DISTANCE * 5;

ModuleRoad::ModuleRoad(const int &index)
{
	int road_offset_z = index * SEGMENTS_IN_ROAD * SEGMENT_DEPTH + ModuleSceneRace::ROAD_INIT_OFFSET;
	for (int i = 0; i < SEGMENTS_IN_ROAD; i++) {
		Segment s;
		s.p1 = Point3D{0, 0, road_offset_z + SEGMENT_DEPTH * i};
		s.p2 = Point3D{0, 0, road_offset_z + SEGMENT_DEPTH * i + SEGMENT_DEPTH };
		roadSegments.push_back(s);
	}
}

ModuleRoad::~ModuleRoad()
{
}

bool ModuleRoad::Init()
{
	return true;
}

bool ModuleRoad::Start()
{
	return true;
}

update_status ModuleRoad::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRoad::Update()
{
	// Define points from real world on the screen
	Point2D p1, p2;
	// Decleare points from real world coordinates
	Point3D realP1, realP2;
	// TODO Declare cemara point on Real world
	Point3D cameraPos{ 0, 25 , 1 };
	int widthP1, widthP2;

	//Get the segment where the player is right now
	int playerSegment = App->player->GetCurrentSegment();
	for (int i = playerSegment; i < SEGMENTS_IN_ROAD; i++) {
		// TODO Get points from real world (loop)
		int currentRoadBlockSegment = i % SEGMENTS_IN_ROAD;
		realP1 = roadSegments.at(currentRoadBlockSegment).p1;
		realP2 = roadSegments.at(currentRoadBlockSegment).p2;
		p1 = Project(realP1, cameraPos, CAMERA_DEPTH, ROAD_WIDTH, &widthP1);
		p2 = Project(realP2, cameraPos, CAMERA_DEPTH, ROAD_WIDTH, &widthP2);

		// Create data for the polygon to draw
		Point2D upperLeft{ p2.x - widthP2 / 2, p2.y };
		Point2D upperRight{ p2.x + widthP2 / 2, p2.y };
		Point2D bottomLeft{ p1.x - widthP1 / 2, p1.y };
		Point2D bottomRight{ p1.x + widthP1 / 2, p1.y };

		/*if (upperLeft.y == bottomLeft.y) {
			LOG("1-line pixel detected, break loop");
			break;
		}*/

		Sint16 vx[4] = { upperLeft.x, upperRight.x, bottomRight.x, bottomLeft.x };
		Sint16 vy[4] = { upperLeft.y, upperRight.y, bottomRight.y, bottomLeft.y };

		Sint16 leftBordervx[4] = { upperLeft.x, upperLeft.x - widthP2 / 20, bottomLeft.x - widthP1 / 20 , bottomLeft.x };
		Sint16 leftBordervy[4] = { p2.y, p2.y, p1.y, p1.y };

		Sint16 rightBordervx[4] = { upperRight.x, upperRight.x + widthP2 / 20, bottomRight.x + widthP1 / 20 , bottomRight.x };
		Sint16 rightBordervy[4] = { p2.y, p2.y, p1.y, p1.y };

		Sint16 grassvx[4] = { 0, App->window->width, App->window->width, 0};
		Sint16 grassvy[4] = { p2.y, p2.y, p1.y, p1.y };

		if (i % 3 == 0)
		{
			rumbleColor = !rumbleColor;
		}

		if(rumbleColor)
		{
			App->renderer->DrawPolygon(grassvx, grassvy, 4, 128, 128, 128, 255);
			App->renderer->DrawPolygon(leftBordervx, leftBordervy, 4, 96, 96, 96, 255);
			App->renderer->DrawPolygon(rightBordervx, rightBordervy, 4, 96, 96, 96, 255);
		}
		else
		{
			App->renderer->DrawPolygon(grassvx, grassvy, 4, 160, 160, 160, 255);
			App->renderer->DrawPolygon(leftBordervx, leftBordervy, 4, 224, 224, 224, 255);
			App->renderer->DrawPolygon(rightBordervx, rightBordervy, 4, 224, 224, 224, 255);
		}
		
		App->renderer->DrawPolygon(vx, vy, 4, 32, 32, 32, 255);
	}
	//system("PAUSE");
	return UPDATE_CONTINUE;
}

update_status ModuleRoad::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleRoad::CleanUp()
{
	return true;
}

Point2D ModuleRoad::Project(const Point3D p, const Point3D camera, const int& cameraDepth,
	const int& roadWidth, int* const segmentWidth) {
	int windowWidth = App->window->width;
	int windowHeight = App->window->height;
	// First reference the real-world point to camera coordinates
	Point3D referencedToCamera;
	referencedToCamera.x = p.x - camera.x;
	referencedToCamera.y = p.y - camera.y;
	referencedToCamera.z = p.z - camera.z;
	// Compute the scale factor (similar triangles law)
	double scale = cameraDepth / (double)referencedToCamera.z;
	// Compute the screen pixel point gven screen dimensions
	Point2D ret;
	ret.x = std::round((windowWidth / 2) + (scale * referencedToCamera.x  * windowWidth / 2));
	ret.y = std::round((windowHeight / 2) - (scale * referencedToCamera.y  * windowHeight / 2));
	// Compute and set the segment width for the given point
	*segmentWidth = std::round((scale * roadWidth * windowWidth / 2));
	return ret;
}