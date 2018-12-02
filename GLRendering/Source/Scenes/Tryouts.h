#ifndef TRYOUTSH
#define TRYOUTSH
#include "Scene.h"
#include "../Core/Camera/Camera.h"
#include "../Core/Graphics/Rendering/Renderer/Renderer.h"
#include "../Core/GameObject/GameObjectManager.h"
#include "../Core/GameObject/Light/LightManager.h"

class Tryouts : public Scene
{

private:
	Camera* camera;
	Renderer* renderer;
	GameObjectManager* objectManager;
	LightManager* lightManager;
	glm::vec3 p_skyColor;
	bool Vsync;

	float fogStart;
	float fogEnd;
	float specularStrengthFactor;
	float specEnd;

public:
	Tryouts();
	virtual ~Tryouts();

	virtual Scene* handleEvent();
	virtual Scene* renderImGui();
	virtual Scene*  update(float dt);
	virtual Scene*  render();
};

#endif

