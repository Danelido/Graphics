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
