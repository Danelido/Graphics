#include "Renderer.h"
#include "../../../Utils/CreateMatrix.h"

Renderer::Renderer()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.3f, 0.7f, 1.0f);
	enableCulling();
	this->p_skyColor = glm::vec3(0.45f, 0.95f, 0.20f);
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
		newVec.reserve(10000);
		newVec.emplace_back(gameObject);
		this->p_gameObjectMap[gameObject->getModel()] = newVec;

		
	}
	else {
		// Add it to the existing array
		std::vector<const GameObject*>& vec = p_gameObjectMap[gameObject->getModel()];
		vec.emplace_back(gameObject);
	}
	
}

void Renderer::render(const Camera & camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use entity shader
	this->p_gameObjectShader->use();
	// send skycolor to shader for fog?
	// set potential light source
	// set the viewmatrix
	this->p_gameObjectShader->setViewMatrix(CreateMatrix::viewMatrix(camera));
	// entityRenderModule.render(send in map)
	this->p_goRenderModule->render(this->p_gameObjectMap);
	// unuse entity shader
	this->p_gameObjectShader->unuse();
	
	this->p_gameObjectMap.clear();
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
