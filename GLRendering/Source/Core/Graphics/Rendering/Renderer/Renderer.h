#ifndef RENDERERH
#define RENDERERH
#include "../OBJModel.h"
#include "../../../Camera/Camera.h"
#include "../../../GameObject/GameObject.h"
#include "../../../GameObject/Light/Light.h"
#include "../../Shaders/GameObjectShader.h"
#include "SubRenderers/GORenderModule.h"
#include <GLM/glm.hpp>
#include <map>

class Renderer {
private:
	glm::vec3 p_skyColor;
	GORenderModule* p_goRenderModule;
	GameObjectShader*	p_gameObjectShader;

	std::map<const OBJModel*, std::vector<GameObject*>> p_gameObjectMap;

	float fogStart;
	float fogEnd;

public:

	Renderer();
	virtual ~Renderer();

	const long int& getNrOfVertices() const;

	void processGameObject(GameObject* gameObject);
	void render(const Camera& camera, const std::vector<Light*>* lights = nullptr);

	void setSkyColor(glm::vec3 skyCol);
	const glm::vec3 getSkyColor() const;

	void setFogStart(const float& fogStart);
	void setFogEnd(const float& fogEnd);
	static void enableCulling();
	static void disableCulling();

};


#endif
