#include "Camera.h"
#include <GLFW/glfw3.h>
#include "../Input/InputManager.h"

Camera::Camera(const glm::vec3 & position)
{
	this->p_position = position;
	this->p_pitch = 0.f;
	this->p_yaw = 0.f;
	this->p_roll = 0.f;
	this->p_sensitivity = 0.1f;
	this->p_movementSpeed = 50.f;

	glfwSetCursorPos(glfwGetCurrentContext(), 1280.f / 2.f, 720.f / 2.f);
	glfwGetCursorPos(glfwGetCurrentContext(), &this->p_lastMousePos.x, &this->p_lastMousePos.y);

}

Camera::~Camera()
{
}

void Camera::update(const float & dt)
{
	// move
	if (InputManager::isKeyHeldDown(GLFW_KEY_W)) {
		this->p_position.z -= glm::cos(this->p_yaw) * this->p_movementSpeed * dt;
		this->p_position.x += glm::sin(this->p_yaw) * this->p_movementSpeed * dt;
	}

	if (InputManager::isKeyHeldDown(GLFW_KEY_A)) {
		this->p_position.z -= glm::sin(90.f) * glm::sin(this->p_yaw) * this->p_movementSpeed * dt;
		this->p_position.x -= glm::sin(90.f) * glm::cos(this->p_yaw) * this->p_movementSpeed * dt;
	}

	if (InputManager::isKeyHeldDown(GLFW_KEY_S)) {
		this->p_position.z += glm::cos(this->p_yaw) * this->p_movementSpeed * dt;
		this->p_position.x -= glm::sin(this->p_yaw) * this->p_movementSpeed * dt;
	}

	if (InputManager::isKeyHeldDown(GLFW_KEY_D)) {
		this->p_position.z += glm::sin(90.f) * glm::sin(this->p_yaw) * this->p_movementSpeed * dt;
		this->p_position.x += glm::sin(90.f) * glm::cos(this->p_yaw) * this->p_movementSpeed * dt;
	}

	// up and down
	if (InputManager::isKeyHeldDown(GLFW_KEY_X)) {
		this->p_position.y += this->p_movementSpeed * dt;
	}
	if (InputManager::isKeyHeldDown(GLFW_KEY_Z)) {
		this->p_position.y -= this->p_movementSpeed * dt;
	}

	if (InputManager::window_focused)
	{
		glfwGetCursorPos(glfwGetCurrentContext(), &this->p_currentMousePos.x, &this->p_currentMousePos.y);
		glm::vec2 vel = this->p_currentMousePos - this->p_lastMousePos;
		glfwSetCursorPos(glfwGetCurrentContext(), 1280.f / 2.f, 720.f / 2.f);
		glfwGetCursorPos(glfwGetCurrentContext(), &this->p_currentMousePos.x, &this->p_currentMousePos.y);
		this->p_lastMousePos = this->p_currentMousePos;

		this->p_yaw += this->p_sensitivity * vel.x * 0.01f;
		this->p_pitch += this->p_sensitivity* vel.y  * 0.01f;
	}
	if (this->p_pitch >= 1.f)
	{
		this->p_pitch = 1.f;
	}
	else if (this->p_pitch <= -1.f)
	{
		this->p_pitch = -1.f;
	}

	// Do a barrel roll
	if (InputManager::isKeyHeldDown(GLFW_KEY_G)) {
		this->p_roll += this->p_movementSpeed * dt;
	}
	if (InputManager::isKeyHeldDown(GLFW_KEY_H)) {
		this->p_roll -= this->p_movementSpeed * dt;
	}

}

void Camera::setMouseSensitivity(const float & sen)
{
	this->p_sensitivity = sen;
}

void Camera::setMovementSpeed(const float & speed)
{
	this->p_movementSpeed = speed;
}

const glm::vec3 & Camera::getPosition() const
{
	return this->p_position;
}

const float & Camera::getPitch() const
{
	return this->p_pitch;
}

const float & Camera::getYaw() const
{
	return this->p_yaw;
}

const float & Camera::getRoll() const
{
	return this->p_roll;
}
