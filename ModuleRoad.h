#ifndef __ModuleRoad__
#define __ModuleRoad__

#include <vector>
#include "Globals.h"
#include "Module.h"

typedef struct {
	int x, y;
} Point2D;

typedef struct {
	int x, y, z;
} Point3D;

struct Segment {
	//TODO: Add attrezzos and rivals
	Point3D p1;
	Point3D p2;
};

/* This class doesn't identify all the road, but a portion of it formed by a constant number of segments
in all instances of this class.*/
class ModuleRoad : public Module
{
public:
	static const int SEGMENT_DEPTH;
	static const int ROAD_WIDTH;
	static const int SEGMENTS_IN_ROAD;
	static const int RUMBLE_LENGTH;
	static const int CAMERA_DEPTH;
	static const int DRAW_DISTANCE;

	ModuleRoad(const int &index);
	~ModuleRoad();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	Point2D ModuleRoad::Project(const Point3D p, const Point3D camera, const int& cameraDepth,
		const int& roadWidth, int* const segmentWidth);
	std::vector<Segment> roadSegments;

	bool rumbleColor = true;
};

#endif