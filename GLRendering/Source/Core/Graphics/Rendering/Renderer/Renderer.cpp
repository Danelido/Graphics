#include "Renderer.h"
#include "../../../Utils/CreateMatrix.h"

Renderer::Renderer()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	enableCulling();
	this->p_skyColor = glm::vec3(0.45f, 0.3f, 0.60f);
	this->p_gameObjectShader = new GameObjectShader();
	this->p_gameObjectShader->use();
	this->p_gameObjectShader->setProjectionMatrix(CreateMatrix::PerspectiveProjectionMatrix(1280.f, 720.f, 0.1f, 1000.f));

	p_goRenderModule = new GORenderModule(this->p_gameObjectShader);
}

Renderer::~Renderer()
{
	delete this->p_goRenderModule;
	delete this->p_gameObjectShader;
}

void Renderer::processGameObject(const GameObject* gameObject)
{

	if (p_gameObjectMap.find(gameObject->getModel()) == p_gameObjectMap.end()) {
		// Create a new array for this VAO
		std::vector<const GameObject*> newVec;
		newVec.emplace_back(gameObject);
		this->p_gameObjectMap.emplace(gameObject->getModel(), newVec);
	}
	else {
		// Add it to the existing array
		std::vector<const GameObject*>& vec = p_gameObjectMap[gameObject->getModel()];
		vec.emplace_back(gameObject);
	}
	
}

void Renderer::render(const Camera & camera, const std::vector<Light*>* lights)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use entity shader
	this->p_gameObjectShader->use();
	
	if (lights)
	{
		this->p_gameObjectShader->processLights(lights);
	}

	this->p_gameObjectShader->setCameraPosition(camera.getPosition());
	this->p_gameObjectShader->setSkyColor(p_skyColor);
	this->p_gameObjectShader->setViewMatrix(CreateMatrix::viewMatrix(camera));

	this->p_goRenderModule->render(this->p_gameObjectMap);
	
	this->p_gameObjectShader->unuse();
	
	this->p_gameObjectMap.clear();
}

void Renderer::setSkyColor(glm::vec3 skyCol)
{
	glClearColor(skyCol.r, skyCol.g, skyCol.b, 1.0f);
	this->p_skyColor = skyCol;
}

const glm::vec3 Renderer::getSkyColor() const
{
	return this->p_skyColor;
}

void Renderer::enableCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Renderer::disableCulling()
{
	glDisable(GL_CULL_FACE);
}
