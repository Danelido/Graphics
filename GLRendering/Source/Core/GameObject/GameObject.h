#ifndef GAMEOBJECTH
#define GAMEOBJECTH

#include "../Graphics/Rendering/OBJModel.h"
#include <GLM/glm.hpp>
#include "../Utils/CreateMatrix.h"
#include "Light/Light.h"

class GameObject {
private:
	OBJModel* p_model;
	Light* p_light;

	// Cached
	const bool shouldUpdateModelMatrix();
	glm::mat4 p_cachedModelMatrix;
	glm::vec3 p_lastPosition;
	glm::vec3 p_lastRotation;
	float p_lastScale;


protected:
	glm::vec3 p_position;
	glm::vec3 p_rotation;
	float p_scale;
	
	Light* getAttachedLight();
public:

	GameObject(const std::string& objFile, const std::string& texFile, glm::vec3 position, glm::vec3 rotation, float scale);
	virtual ~GameObject();

	virtual void update(float dt) = 0;
	
	OBJModel* getModel() const;

	void setPosition(glm::vec3 pos);
	void setRotation(glm::vec3 rot);
	void setScale(float scale);
	void attachLight(Light* light);

	glm::mat4& getModelMatrix();
	const glm::vec3& getPosition() const;
	const glm::vec3& getRotation() const;
	const float& getScale() const;
	const bool hasLightAttached() const;


};

#endif
