#ifndef TRYOUTSH
#define TRYOUTSH
#include "Scene.h"
#include "../Core/Graphics/Shaders/TestShader.h"
#include "../Core/Camera/Camera.h"
#include "../Core/Graphics/Rendering/Renderer/Renderer.h"
#include "../Core/GameObject/GameObjectManager.h"

class Tryouts : public Scene
{

private:
	Camera* camera;
	Renderer* renderer;
	GameObjectManager* objectManager;
	glm::vec3 p_skyColor;
	bool Vsync;

public:
	Tryouts();
	virtual ~Tryouts();

	virtual Scene* handleEvent();
	virtual Scene* renderImGui();
	virtual Scene*  update(float dt);
	virtual Scene*  render();
};

#endif

