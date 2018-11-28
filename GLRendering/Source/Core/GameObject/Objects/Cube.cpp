#include "Cube.h"

Cube::Cube(glm::vec3 position, glm::vec3 rotation, float scale) :
	GameObject("box.obj", "RTS_Crate.png", position, rotation, scale)

{

}

Cube::~Cube()
{
}

void Cube::update(float dt)
{
	
}
