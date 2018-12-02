#include "GameObjectShader.h"
#include <GLM/gtc/type_ptr.hpp>
GameObjectShader::GameObjectShader()
{
	if (!this->loadShadersFromFile("Shaders/GameObjectVertex.glsl", "Shaders/GameObjectFragment.glsl")) {
		system("pause");
	}

	modelMatrixLocation = glGetUniformLocation(this->program(), "modelMatrix");
	viewMatrixLocation = glGetUniformLocation(this->program(), "viewMatrix");
	projectionMatrixLocation = glGetUniformLocation(this->program(), "projectionMatrix");
	cameraPositionLocation = glGetUniformLocation(this->program(), "cameraPosition");
	skyColorLocation = glGetUniformLocation(this->program(), "skyColor");
	numberOfLightLocation = glGetUniformLocation(this->program(), "numberOfLights");
	fogStartLocation = glGetUniformLocation(this->program(), "u_fogStart");
	fogEndLocation = glGetUniformLocation(this->program(), "u_fogEnd");
	specularStrengthLocation = glGetUniformLocation(this->program(), "u_specularStrength");
	specularEnd = glGetUniformLocation(this->program(), "u_specEnd");

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		std::string posLoc = "lights[" + std::to_string(i) + "].lightPosition";
		std::string colLoc = "lights[" + std::to_string(i) + "].lightColor";
		
		LightBlock block;
		block.positionLocation = glGetUniformLocation(this->program(), posLoc.c_str());
		block.colorLocation = glGetUniformLocation(this->program(), colLoc.c_str());
		
		lightMap[i] = block;
	}


}

GameObjectShader::~GameObjectShader()
{
}

void GameObjectShader::setModelMatrix(const glm::mat4 & model)
{
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &model[0][0]);
}	

void GameObjectShader::setViewMatrix(const glm::mat4 & view)
{
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &view[0][0]);
}

void GameObjectShader::setProjectionMatrix(const glm::mat4 & projection)
{
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projection[0][0]);
}

void GameObjectShader::setCameraPosition(const glm::vec3 & cameraPos)
{
	glUniform3f(cameraPositionLocation, cameraPos.x, cameraPos.y, cameraPos.z);
}

void GameObjectShader::processLights(const std::vector<Light*>* lights)
{

	glUniform1i(numberOfLightLocation, (int)(lights->size()));

	for (int i = 0; i < lights->size(); i++)
	{
		glUniform3f(lightMap[i].positionLocation,
			lights->at(i)->getPosition().x,
			lights->at(i)->getPosition().y,
			lights->at(i)->getPosition().z);

		glUniform3f(lightMap[i].colorLocation,
			lights->at(i)->getLightColor().x,
			lights->at(i)->getLightColor().y,
			lights->at(i)->getLightColor().z);
	}
}

void GameObjectShader::setFogStart(const float & fogStart)
{
	glUniform1f(fogStartLocation, fogStart);
}

void GameObjectShader::setFogEnd(const float & fogEnd)
{
	glUniform1f(fogEndLocation, fogEnd);
}

void GameObjectShader::setSkyColor(const glm::vec3 & skyCol)
{
	glUniform3f(skyColorLocation, skyCol.x, skyCol.y, skyCol.z);
}
void GameObjectShader::setSpecularStrength(const float& factor)
{
	glUniform1f(specularStrengthLocation, factor);
}

void GameObjectShader::setSpecularEnd(const float& specEnd)
{
	glUniform1f(specularEnd, specEnd);
}