#include "Tryouts.h"

#include <stdio.h>
#include <GL/glew.h>
#include <chrono>
#include "../Core/Input/InputManager.h"

#include "../Core/Parser/ParserOBJ.h"
#include "../Core/Utils/RandomNum.h"
#include "../Core/Graphics/Resource/Resources.h"

#include "../Core/Vendor/ImGui/imgui.h"
#include "../Core/Vendor/ImGui/imgui_impl_glfw.h"
#include "../Core/Vendor/ImGui/imgui_impl_opengl3.h"

#include "../Core/GameObject/Objects/Cube.h"
#include "../Core/GameObject/Objects/LightCube.h"
#include "../Core/GameObject/Objects/StanfordDragon.h"
#include "../Core/GameObject/Objects/WorldPlane.h"

// https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_01

Tryouts::Tryouts()
{
	Vsync = true;
	camera = new Camera(glm::vec3(0.f, 15.f, 0.f));
	camera->setMouseSensitivity(0.25f);
	camera->setMovementSpeed(50.f);
	objectManager = new GameObjectManager();
	lightManager = new LightManager();
	renderer = new Renderer();
	p_skyColor = renderer->getSkyColor();
		
	objectManager->addObject(new WorldPlane());
	
	float cubeScale = 6.f;
	for (int i = 0; i < 100.f; i++)
	{
		objectManager->addObject(new Cube(
			glm::vec3(RandomNum::getRandomNumber(-500.f, 500.f), cubeScale, RandomNum::getRandomNumber(-500.f, 500.f)),
			glm::vec3(0.f),
			cubeScale
			));
	}

	// Create light
	Light* tempLight = new Light();
	tempLight->setLightColor(glm::vec3(1.f, 1.f, 159.f/255.f));
	lightManager->addLight(tempLight);

	// Create a game object and attach the light to it
	GameObject* lightCube = new LightCube(glm::vec3(15.f, 40.f, -200.f), glm::vec3(0.f), 2.f);
	lightCube->attachLight(tempLight);
	objectManager->addObject(lightCube);
	
	fogStart = 1.f;
	fogEnd = 350.f;
	specularStrengthFactor = 0.5f;
	specEnd = 65.f;


}

Tryouts::~Tryouts()
{
	delete this->camera;
	delete this->renderer;
	delete this->objectManager;
	delete this->lightManager;

}

Scene* Tryouts::handleEvent() 
{
	return this;
}

Scene * Tryouts::renderImGui()
{
	ImGui::Begin("OpenGL");
	ImGui::Text("C = Lock/Unlock FPS camera");
	ImGui::Text("WASD = Move around");
	ImGui::Text("X & Z = Move Up/Down");
	ImGui::Text("World objects: %d", objectManager->getNrOfGameObjects());
	ImGui::Text("Vertices being rendered: %d", renderer->getNrOfVertices());
	ImGui::ColorEdit3("Clear color", (float*)&p_skyColor);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::SliderFloat("FogStart", &fogStart, 1.f, fogEnd);
	ImGui::SliderFloat("FogEnd", &fogEnd, fogStart, 1000.f);
	ImGui::SliderFloat("Specular strength", &specularStrengthFactor, 0.0f, 1.0f);
	ImGui::SliderFloat("Specular distance factor", &specEnd, 0.0f, 500.0f);
	ImGui::Checkbox("Vsync", &Vsync);
	ImGui::End();

	if (!Vsync)
	{
		glfwSwapInterval(0);
	}
	else
	{
		glfwSwapInterval(1);
	}
	return this;
}

Scene* Tryouts::update(float dt) 
{	
	camera->update(dt);
	objectManager->update(dt);
	return this;
}

Scene* Tryouts::render() 
{
	objectManager->render(camera, renderer);
	
	// Final render call
	renderer->setSkyColor(p_skyColor);
	renderer->setFogStart(fogStart);
	renderer->setFogEnd(fogEnd);
	renderer->setSpecularStrength(specularStrengthFactor);
	renderer->setSpecEnd(specEnd);
	renderer->render(*camera, &lightManager->getLights());
	return this;
}