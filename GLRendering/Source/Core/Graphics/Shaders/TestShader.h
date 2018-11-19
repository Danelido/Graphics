#ifndef TESTSHADERH
#define TESTSHADERH
#include "../ShaderAbstraction/ShaderClass.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>


class TestShader : public ShaderClass {

private:
	GLint colorLocation;
	GLint modelMatrixLocation;
	GLint viewMatrixLocation;
	GLint projectionMatrixLocation;
	GLint overrideColorLocation;

public:
	TestShader();
	virtual ~TestShader();


	void setColor(float red, float green, float blue);
	void setOverrideColor(float red, float green, float blue);
	void setTextureInt(const char* name,int i);
	void setModelMatrix(const glm::mat4& model);
	void setViewMatrix(const glm::mat4& view);
	void setProjectionMatrix(const glm::mat4& projection);

};


#endif
