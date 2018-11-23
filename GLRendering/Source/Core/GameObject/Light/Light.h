#ifndef LIGHTH
#define LIGHTH
#include <GLM/glm.hpp>

class GameObject;

class Light
{
public:
	Light(const glm::vec3& position = glm::vec3(0.f), const glm::vec3& lightColor = glm::vec3(1.f), const float& lightIntensity = 0.5f);
	virtual ~Light();

	void setPosition(const glm::vec3& position);
	void setLightColor(const glm::vec3& lightColor);
	void setLightIntensity(const float& intensity);
	void setOwner(GameObject* gameObject);

	const glm::vec3& getPosition() const;
	const glm::vec3& getLightColor() const;
	const float& getLightIntensity() const;

private:
	glm::vec3 p_position;
	glm::vec3 p_lightColor;
	float p_lightIntensity;
	
	GameObject* p_owner;

};



#endif
