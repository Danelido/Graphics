#include "WorldPlane.h"

WorldPlane::WorldPlane(glm::vec3 position) :
	GameObject("WorldPlane.obj", "FloorTile/FloorTileAmbientOcclusion.png", position, glm::vec3(0.f), 1.f)
{
}

WorldPlane::~WorldPlane()
{
}

void WorldPlane::update(float dt)
{
}
