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


// https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_01

Tryouts::Tryouts()
{
	Vsync = true;
	camera = new Camera(glm::vec3(0.f, 0.f, 0.f));
	camera->setMouseSensitivity(0.25f);
	camera->setMovementSpeed(50.f);
	objectManager = new GameObjectManager();
	lightManager = new LightManager();
	renderer = new Renderer();
	p_skyColor = renderer->getSkyColor();
		

	/* TEST CODE */
	objectManager->addObject(new Cube(glm::vec3(0.f, 0.f, -80.f), glm::vec3(0.f), 50.f));

	// Create light
	Light* tempLight = new Light();
	lightManager->addLight(tempLight);

	// Create a game object and attach the light to it
	GameObject* lightCube = new LightCube(glm::vec3(15.f, -15.f, -25.f), glm::vec3(0.f), 1.0f);
	lightCube->attachLight(tempLight);
	objectManager->addObject(lightCube);



	// Create light
	Light* tempLight2 = new Light();
	tempLight2->setLightColor(glm::vec3(0.2f, 1.f, 0.2f));
	lightManager->addLight(tempLight2);

	// Create a game object and attach the light to it
	GameObject* lightCube2 = new LightCube(glm::vec3(-15.f, -15.f, -25.f), glm::vec3(0.f), 1.0f);
	lightCube2->attachLight(tempLight2);
	objectManager->addObject(lightCube2);



	// Create light
	Light* tempLight3 = new Light();
	tempLight3->setLightColor(glm::vec3(.8f, 0.f, 0.f));
	lightManager->addLight(tempLight3);

	// Create a game object and attach the light to it
	GameObject* lightCube3 = new LightCube(glm::vec3(-15.f, 15.f, -25.f), glm::vec3(0.f), 1.0f);
	lightCube3->attachLight(tempLight3);
	objectManager->addObject(lightCube3);



	// Create light
	Light* tempLight4 = new Light();
	tempLight4->setLightColor(glm::vec3(0.f, 0.8f, .8f));
	lightManager->addLight(tempLight4);

	// Create a game object and attach the light to it
	GameObject* lightCube4 = new LightCube(glm::vec3(15.f, 15.f, -25.f), glm::vec3(0.f), 1.0f);
	lightCube4->attachLight(tempLight4);
	objectManager->addObject(lightCube4);
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
	ImGui::ColorEdit3("Clear color", (float*)&p_skyColor);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	
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
	renderer->render(*camera, &lightManager->getLights());
	return this;
}