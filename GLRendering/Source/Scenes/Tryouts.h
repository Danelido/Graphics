#ifndef TRYOUTSH
#define TRYOUTSH
#include "Scene.h"
#include "../Core/Graphics/Shaders/TestShader.h"
#include "../Core/Camera/Camera.h"
#include "../Core/Graphics/Rendering/Renderer/Renderer.h"
#include "../Core/GameObject/GameObject.h"

class Tryouts : public Scene
{

private:
	Camera* camera;
	
	MeshLoader* meshLoader;
	Renderer* renderer;
	OBJModel* boxModel;
	GameObject* box;
	GameObject* box2;

public:
	Tryouts();
	virtual ~Tryouts();

	virtual Scene* handleEvent();
	virtual Scene*  update(float dt);
	virtual Scene*  render();
};

#endif

