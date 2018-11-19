#include "GameObject.h"

GameObject::GameObject(OBJModel* model, glm::vec3 position, glm::vec3 rotation, float scale) :
	p_model(model)
{
	p_position = position;
	p_rotation = rotation;
	p_scale = scale;
}

GameObject::~GameObject()
{
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
