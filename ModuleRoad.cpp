#include "ModuleRoad.h"
#include <math.h>
#include "SDL_gfx/include/SDL_gfxPrimitives.h"

const int ModuleRoad::SEGMENT_DEPTH = 20;
const int ModuleRoad::RUMBLE_LENGTH = 3;
const int ModuleRoad::DRAW_DISTANCE = 4;
const int ModuleRoad::SEGMENTS_IN_ROAD = RUMBLE_LENGTH * DRAW_DISTANCE * 5;

ModuleRoad::ModuleRoad(const int &index)
{
	int road_offset_z = index * SEGMENTS_IN_ROAD * SEGMENT_DEPTH;
	for (int i = 0; i < SEGMENTS_IN_ROAD; i++) {
		Segment s;
		s.p1 = Point3D{ 0, 0, road_offset_z + SEGMENT_DEPTH * i};
		s.p2 = Point3D{ 0, 0, road_offset_z + SEGMENT_DEPTH * i + SEGMENT_DEPTH };
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
	//// Define points from real world on the screen
	//Point2D p1, p2;
	//// Decleare points from real world coordinates
	//Point3D realP1, realP2;
	//// TODO Declare cemara point on Real world
	//Point3D cameraPos{ SCREEN_WIDTH/2, 10, 0 };
	//int widthP1, widthP2;

	//// TODO Get points from real world (loop)
	//// realP1 = ...
	//// realP2 = ...
	//p1 = Project(realP1, cameraPos, CAMERA_DEPTH, ROAD_WIDTH, &widthP1);
	//p2 = Project(realP2, cameraPos, CAMERA_DEPTH, ROAD_WIDTH, &widthP2);

	//// Create data for the polygon to draw
	//Point2D upperLeft{ p2.x - widthP2 / 2, p2.y };
	//Point2D upperRight{ p2.x + widthP2 / 2, p2.y };
	//Point2D bottomLeft{ p1.x - widthP1 / 2, p1.y };
	//Point2D bottomRight{ p1.x + widthP1 / 2, p1.y };
	//
	//Sint16 vx[4] = {upperLeft.x, upperRight.x, bottomLeft.x, bottomRight.x};
	//Sint16 vy[4] = {upperLeft.y, upperRight.y, bottomLeft.y, bottomRight.y};
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
	// First reference the real-world point to camera coordinates
	Point3D referencedToCamera;
	referencedToCamera.x = p.x - camera.x;
	referencedToCamera.y = p.y - camera.y;
	referencedToCamera.z = p.z - camera.z;
	// Compute the scale factor (similar triangles law)
	double scale = cameraDepth / referencedToCamera.z;
	// Compute the screen pixel point gven screen dimensions
	Point2D ret;
	ret.x = std::round((SCREEN_WIDTH / 2) + (scale * referencedToCamera.x  * SCREEN_WIDTH / 2));
	ret.y = std::round((SCREEN_HEIGHT / 2) - (scale * referencedToCamera.y  * SCREEN_HEIGHT / 2));
	// Compute and set the segment width for the given point
	*segmentWidth = std::round((scale * roadWidth   * SCREEN_WIDTH / 2));
	return ret;
}