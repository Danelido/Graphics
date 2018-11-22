#include "StanfordDragon.h"

StanfordDragon::StanfordDragon(glm::vec3 position, glm::vec3 rotation, float scale) :
	GameObject("dragon.obj", "TempTexture.png", position, rotation, scale)
{
}

StanfordDragon::~StanfordDragon()
{
}

void StanfordDragon::update(float dt)
{
}
