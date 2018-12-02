#include "Renderer.h"
#include "../../../Utils/CreateMatrix.h"

Renderer::Renderer()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	enableBackFaceCulling();
	fogStart = 0.f;
	fogEnd = 0.f;
	this->p_skyColor = glm::vec3(0.f);
	this->p_gameObjectShader = new GameObjectShader();
	this->p_gameObjectShader->use();
	this->p_gameObjectShader->setProjectionMatrix(CreateMatrix::PerspectiveProjectionMatrix(1280.f, 720.f, 0.1f, 1000.f));

	p_goRenderModule = new GORenderModule(this->p_gameObjectShader);
	p_skyBox = new SkyBox();

}

Renderer::~Renderer()
{
	delete this->p_goRenderModule;
	delete this->p_gameObjectShader;
	delete this->p_skyBox;
}

const long int & Renderer::getNrOfVertices() const
{
	return this->p_goRenderModule->totalNrOfVertices();
}

void Renderer::processGameObject(GameObject* gameObject)
{
	
	for (auto& map : p_gameObjectMap)
	{
		if (*map.first == *gameObject->getModel())
		{
			map.second.emplace_back(gameObject);
			return;
		}
	}
	// Create a new array for this VAO
	std::vector<GameObject*> newVec;
	newVec.emplace_back(gameObject);
	this->p_gameObjectMap.emplace(gameObject->getModel(), newVec);
	
	
}

void Renderer::renderSkybox(const Camera & camera)
{
	glDepthMask(GL_FALSE);
	disableBackFaceCulling();
	enableFrontFaceCulling();
	p_skyBox->setFogColor(p_skyColor);
	p_skyBox->render(&camera);
	glDepthMask(GL_TRUE);
	disableFrontFaceCulling();
	enableBackFaceCulling();
}

void Renderer::renderGameObjects(const Camera & camera, const std::vector<Light*>* lights)
{
	// Use entity shader
	this->p_gameObjectShader->use();
	this->p_gameObjectShader->setFogStart(fogStart);
	this->p_gameObjectShader->setFogEnd(fogEnd);
	this->p_gameObjectShader->setSpecularStrength(specularStrengthFactor);
	this->p_gameObjectShader->setSpecularEnd(specEnd);

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

void Renderer::render(const Camera & camera, const std::vector<Light*>* lights)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderSkybox(camera);
	renderGameObjects(camera, lights);
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

void Renderer::setFogStart(const float & fogStart)
{
	this->fogStart = fogStart;
}

void Renderer::setFogEnd(const float & fogEnd)
{
	this->fogEnd = fogEnd;
}

void Renderer::setSpecularStrength(const float& factor)
{
	this->specularStrengthFactor = factor;
}

void Renderer::setSpecEnd(const float& specEnd)
{
	this->specEnd = specEnd;
}

void Renderer::enableBackFaceCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Renderer::disableBackFaceCulling()
{
	glDisable(GL_CULL_FACE);
}

void Renderer::enableFrontFaceCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
}

void Renderer::disableFrontFaceCulling()
{
	glDisable(GL_CULL_FACE);
}

const float& Renderer::getFogEnd() const
{
	return this->fogEnd;
}