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
#include "../Core/GameObject/Objects/StanfordDragon.h"

// https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_01

Tryouts::Tryouts()
{

	camera = new Camera(glm::vec3(0.f, 0.f, 0.f));
	camera->setMouseSensitivity(0.25f);
	camera->setMovementSpeed(50.f);
	objectManager = new GameObjectManager();
	renderer = new Renderer();

	p_skyColor = renderer->getSkyColor();
	Vsync = true;
	for(int i = 0; i < 20; i++)
		objectManager->addObject(new Cube(RandomNum::getRandomVector(-100.f, 100.f) , glm::vec3(0.f), 5.f));
	
	objectManager->addObject(new StanfordDragon(glm::vec3(100.f, 0.f, -100.f), glm::vec3(0.f), 1.f));

}


Tryouts::~Tryouts()
{
	delete this->camera;
	delete this->renderer;
	delete this->objectManager;
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
	renderer->render(*camera);
	return this;
}