#include "LightCube.h"
#include "../../Input/InputManager.h"

LightCube::LightCube(glm::vec3 position, glm::vec3 rotation, float scale) :
	GameObject("sphere.obj", "White.png", position, rotation, scale)
{
}

LightCube::~LightCube()
{
}

void LightCube::update(float dt)
{
	// Testing
	if (InputManager::isKeyHeldDown(GLFW_KEY_T))
	{
		p_position.z -= 20.f * dt;
	}

	if (InputManager::isKeyHeldDown(GLFW_KEY_F))
	{
		p_position.x -= 20.f * dt;
	}

	if (InputManager::isKeyHeldDown(GLFW_KEY_G))
	{
		p_position.z += 20.f * dt;
	}

	if (InputManager::isKeyHeldDown(GLFW_KEY_H))
	{
		p_position.x += 20.f * dt;
	}

}
