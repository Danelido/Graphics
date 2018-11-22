#ifndef GAMEOBJECTMANAGERH
#define GAMEOBJECTMANAGERH
#include <map>
#include <string>
#include <vector>
#include "GameObject.h"
#include "../Graphics/Rendering/OBJModel.h"
#include "../Graphics/Rendering/Renderer/Renderer.h"

class GameObjectManager
{
public:
	GameObjectManager();
	virtual ~GameObjectManager();

	void update(float dt);
	void render(Camera* camera, Renderer* renderer);

	bool addObject(GameObject* object);
	const size_t& getNrOfGameObjects() const;

private:
	std::vector<GameObject*> p_gameObjects;
	
};



#endif
