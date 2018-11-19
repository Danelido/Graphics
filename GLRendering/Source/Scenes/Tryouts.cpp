#include "Tryouts.h"

#include <stdio.h>
#include <GL/glew.h>
#include <chrono>
#include "../Core/Input/InputManager.h"

#include "../Core/Parser/ParserOBJ.h"
#include "../Core/Utils/RandomNum.h"

Tryouts::Tryouts()
{

	camera = new Camera(glm::vec3(0.f, 0.f, 0.f));
	camera->setMovementSpeed(50.f);

	meshLoader = new MeshLoader();

	renderer = new Renderer();

	boxModel = new OBJModel("box.obj", "bear.png", meshLoader);

	box = new GameObject(boxModel, glm::vec3(0, 0.f, -50.f), glm::vec3(25.f,50.f,0.f), 10.f);
	box2 = new GameObject(boxModel, glm::vec3(50, 0.f, -50.f));

}


Tryouts::~Tryouts()
{
	delete this->camera;
	delete this->renderer;
	delete this->meshLoader;
	delete this->boxModel;
	delete this->box;
	delete this->box2;
}

Scene* Tryouts::handleEvent() 
{
	return this;
}

Scene* Tryouts::update(float dt) 
{
	camera->update(dt);

	renderer->processGameObject(box);
	renderer->processGameObject(box2);
	return this;
}

Scene* Tryouts::render() 
{
	renderer->render(*camera);
	return this;
}