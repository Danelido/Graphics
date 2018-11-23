#include "Light.h"
#include "../GameObject.h"

Light::Light(const glm::vec3 & position, const glm::vec3 & lightColor, const float& lightIntensity) :
	p_position(position), p_lightColor(lightColor), p_lightIntensity(lightIntensity)
{
	p_owner = nullptr;
}

Light::~Light()
{
}

void Light::setPosition(const glm::vec3 & position)
{
	if (!p_owner){p_position = position;}
}

void Light::setLightColor(const glm::vec3 & lightColor)
{
	p_lightColor = lightColor;
}

void Light::setLightIntensity(const float & intensity)
{
	std::fmin(this->p_lightIntensity = intensity, 1.0f);
}

void Light::setOwner(GameObject * gameObject)
{
	p_owner = gameObject;
}

const glm::vec3 & Light::getPosition() const
{
	if (p_owner)
	{
		return p_owner->getPosition();
	}else
	{
		return p_position;
	}

}

const glm::vec3 & Light::getLightColor() const
{
	return p_lightColor;
}

const float & Light::getLightIntensity() const
{
	return p_lightIntensity;
}
