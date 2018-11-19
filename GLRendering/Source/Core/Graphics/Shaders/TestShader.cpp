#include "TestShader.h"

TestShader::TestShader()
{
	if (!this->loadShadersFromFile("Shaders/TestVert.glsl", "Shaders/TestFrag.glsl")) {
		system("pause");
	}
	//colorLocation = glGetUniformLocation(this->program(), "triangleColor");
	modelMatrixLocation = glGetUniformLocation(this->program(), "modelMatrix");
	viewMatrixLocation = glGetUniformLocation(this->program(), "viewMatrix");
	projectionMatrixLocation = glGetUniformLocation(this->program(), "projectionMatrix");
	//overrideColorLocation = glGetUniformLocation(this->program(), "overrideColor");
}

void TestShader::setColor(float red, float green, float blue)
{
	glUniform3f(this->colorLocation, red, green, blue);
}

void TestShader::setOverrideColor(float red, float green, float blue)
{
	glUniform3f(this->overrideColorLocation, red, green, blue);
}

void TestShader::setTextureInt(const char* name, int i)
{
	glUniform1i(glGetUniformLocation(this->program(), name), i);
}

void TestShader::setModelMatrix(const glm::mat4 & model)
{
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(model));
}

void TestShader::setViewMatrix(const glm::mat4& view)
{
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));
}
void TestShader::setProjectionMatrix(const glm::mat4& projection)
{
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

TestShader::~TestShader()
{
}
