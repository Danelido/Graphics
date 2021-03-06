#include "GameObjectManager.h"
#include "../Camera/Camera.h"

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	for (auto gObj : p_gameObjects)
	{
		delete gObj;
	}
	this->p_gameObjects.clear();
}

void GameObjectManager::update(float dt)
{
	for (auto gObj : p_gameObjects)
	{
		gObj->update(dt);
	}
}
#include "Objects/WorldPlane.h"
void GameObjectManager::render(Camera* camera, Renderer * renderer)
{
	
	for (auto gObj : p_gameObjects)
	{	
		float dist = glm::length(gObj->getPosition() - camera->getPosition());
		if(dist < renderer->getFogEnd() || dynamic_cast<WorldPlane*>(gObj) != nullptr)
			renderer->processGameObject(gObj);
	}
}

bool GameObjectManager::addObject(GameObject * object)
{
	if(!object)
		return false;

	this->p_gameObjects.emplace_back(object);

	return true;
}

const size_t GameObjectManager::getNrOfGameObjects() const
{
	return this->p_gameObjects.size();
}

