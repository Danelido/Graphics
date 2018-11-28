#include "GameObject.h"
#include "../Utils/CreateMatrix.h"

GameObject::GameObject(const std::string& objFile, const std::string& texFile, glm::vec3 position, glm::vec3 rotation, float scale)
{
	p_model = new OBJModel(objFile, texFile);
	p_position = position;
	p_rotation = rotation;
	p_scale = scale;
	p_light = nullptr;
	
	p_lastPosition = p_position;
	p_lastRotation = p_rotation;
	p_lastScale = p_scale;

	p_cachedModelMatrix = CreateMatrix::modelMatrix(p_position, p_rotation, p_scale);
}

GameObject::~GameObject()
{
	delete this->p_model;
}

OBJModel* GameObject::getModel() const
{
	return this->p_model;
}

void GameObject::setPosition(glm::vec3 pos)
{
	this->p_position = pos;
}

void GameObject::setRotation(glm::vec3 rot)
{
	this->p_rotation = rot;
}

void GameObject::setScale(float scale)
{
	this->p_scale = scale;
}

void GameObject::attachLight(Light * light)
{
	this->p_light = light;
	light->setOwner(this);
}

const bool GameObject::shouldUpdateModelMatrix()
{
	
	if (p_position != p_lastPosition ||
		p_rotation != p_lastRotation ||
		p_scale != p_lastScale) {
		return true;
	}

	return false;

}

glm::mat4 & GameObject::getModelMatrix()
{
	if (shouldUpdateModelMatrix())
	{
		p_cachedModelMatrix = CreateMatrix::modelMatrix(p_position, p_rotation, p_scale);
		p_lastPosition = p_position;
		p_lastRotation = p_rotation;
		p_lastScale = p_scale;
	}

	return p_cachedModelMatrix;
}

const glm::vec3 & GameObject::getPosition() const
{
	return this->p_position;
}

const glm::vec3 & GameObject::getRotation() const
{
	return this->p_rotation;
}

const float & GameObject::getScale() const
{
	return this->p_scale;
}

Light* GameObject::getAttachedLight()
{
	return p_light;
}

const bool GameObject::hasLightAttached() const
{
	return (p_light != nullptr);
}