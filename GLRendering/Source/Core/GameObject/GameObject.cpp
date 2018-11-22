#include "GameObject.h"

GameObject::GameObject(const std::string& objFile, const std::string& texFile, glm::vec3 position, glm::vec3 rotation, float scale)
{
	p_model = new OBJModel(objFile, texFile);
	p_position = position;
	p_rotation = rotation;
	p_scale = scale;
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

const glm::vec3 & GameObject::getPosition() const
{
	return this->p_position;
}

const glm::vec3 & GameObject::getRotation() const
{
	return this->p_rotation;
}

const glm::vec3 GameObject::getCenter() const
{
	glm::vec4 center = glm::vec4(p_position, 1.0f) * (p_scale * 0.5f);
	center = center * CreateMatrix::modelMatrix(p_position, p_rotation, p_scale);
	return glm::vec3(center.x, center.y, center.z);

}

const float & GameObject::getScale() const
{
	return this->p_scale;
}
