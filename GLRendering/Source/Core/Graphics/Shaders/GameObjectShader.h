#ifndef GAMEOBJECTSHADERH
#define GAMEOBJECTSHADERH
#include "../ShaderAbstraction/ShaderClass.h"
#include "../../GameObject/Light/Light.h"
#include <vector>
#include <map>
#include <GLM/glm.hpp>

class GameObjectShader : public ShaderClass
{
// Note to self: Change this in the vertex & fragment shader also if it is edited.
#define MAX_LIGHTS 12
private:
	GLint modelMatrixLocation;
	GLint viewMatrixLocation;
	GLint projectionMatrixLocation;

	GLint cameraPositionLocation;
	GLint skyColorLocation;
	GLint numberOfLightLocation;

	GLint fogStartLocation;
	GLint fogEndLocation;

	struct LightBlock {
		GLint positionLocation;
		GLint colorLocation;
	};
	std::map<GLint, LightBlock> lightMap;

public:
	GameObjectShader();
	virtual ~GameObjectShader();

	void setModelMatrix(const glm::mat4& model);
	void setViewMatrix(const glm::mat4& view);
	void setProjectionMatrix(const glm::mat4& projection);
	void setCameraPosition(const glm::vec3& cameraPos);
	void processLights(const std::vector<Light*>* lights);
	void setFogStart(const float& fogStart);
	void setFogEnd(const float& fogEnd);
	void setSkyColor(const glm::vec3& skyCol);
};


#endif
