#include "SkyBoxShader.h"


SkyBoxShader::SkyBoxShader()
{
	if (!this->loadShadersFromFile("Shaders/SkyBoxVertex.glsl", "Shaders/SkyBoxFragment.glsl")) {
		system("pause");
	}

	viewMatrixLocation = glGetUniformLocation(this->program(), "viewMatrix");
	projectionMatrixLocation = glGetUniformLocation(this->program(), "projectionMatrix");
	modelMatrixLocation = glGetUniformLocation(this->program(), "modelMatrix");
	fogColorLocation = glGetUniformLocation(this->program(), "fogColor");

}
SkyBoxShader::~SkyBoxShader()
{

}

void SkyBoxShader::setViewMatrix(const glm::mat4& view)
{
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &view[0][0]);
}

void SkyBoxShader::setProjectionMatrix(const glm::mat4& projection)
{
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projection[0][0]);
}

void SkyBoxShader::setModelMatrix(const glm::mat4& model)
{
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &model[0][0]);
}

void SkyBoxShader::setFogColor(const glm::vec3& fogColor)
{
	glUniform3f(fogColorLocation, fogColor.r, fogColor.g, fogColor.b);
}