#ifndef SKYBOXSHADER_H
#define SKYBOXSHADER_H
#include "../ShaderAbstraction/ShaderClass.h"
#include <GLM/glm.hpp>
class SkyBoxShader : public ShaderClass
{

private:
	GLint viewMatrixLocation;
	GLint projectionMatrixLocation;
	GLint modelMatrixLocation;
	GLint fogColorLocation;

public:
	SkyBoxShader();
	virtual ~SkyBoxShader();

	void setViewMatrix(const glm::mat4& view);
	void setProjectionMatrix(const glm::mat4& projection);
	void setModelMatrix(const glm::mat4& model);
	void setFogColor(const glm::vec3& fogColor);

};

#endif
