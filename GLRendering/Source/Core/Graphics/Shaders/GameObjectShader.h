#ifndef GAMEOBJECTSHADERH
#define GAMEOBJECTSHADERH
#include "../ShaderAbstraction/ShaderClass.h"
#include <GLM/glm.hpp>

class GameObjectShader : public ShaderClass
{
private:
	GLint modelMatrixLocation;
	GLint viewMatrixLocation;
	GLint projectionMatrixLocation;

public:
	GameObjectShader();
	virtual ~GameObjectShader();

	void setModelMatrix(const glm::mat4& model);
	void setViewMatrix(const glm::mat4& view);
	void setProjectionMatrix(const glm::mat4& projection);

};


#endif
