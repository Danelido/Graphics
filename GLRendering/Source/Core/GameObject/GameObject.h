#ifndef GAMEOBJECTH
#define GAMEOBJECTH

#include "../Graphics/Rendering/OBJModel.h"
#include <GLM/glm.hpp>
#include "../Utils/CreateMatrix.h"

class GameObject {
private:
	OBJModel* p_model;
protected:
	glm::vec3 p_position;
	glm::vec3 p_rotation;
	float p_scale;

public:

	GameObject(const std::string& objFile, const std::string& texFile, glm::vec3 position, glm::vec3 rotation, float scale);
	virtual ~GameObject();

	virtual void update(float dt) = 0;
	
	OBJModel* getModel() const;

	void setPosition(glm::vec3 pos);
	void setRotation(glm::vec3 rot);
	void setScale(float scale);

	const glm::vec3& getPosition() const;
	const glm::vec3& getRotation() const;
	const glm::vec3  getCenter() const;
	const float& getScale() const;


};

#endif
