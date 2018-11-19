#ifndef GAMEOBJECTH
#define GAMEOBJECTH

#include "../Graphics/Rendering/OBJModel.h"
#include <GLM/glm.hpp>

class GameObject {
private:
	OBJModel* p_model;

	glm::vec3 p_position;
	glm::vec3 p_rotation;
	float p_scale;

public:

	GameObject(OBJModel* model, glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), float scale = 1.f);
	virtual ~GameObject();

	OBJModel* getModel() const;

	void setPosition(glm::vec3 pos);
	void setRotation(glm::vec3 rot);
	void setScale(float scale);

	const glm::vec3& getPosition() const;
	const glm::vec3& getRotation() const;
	const float& getScale() const;


};

#endif
