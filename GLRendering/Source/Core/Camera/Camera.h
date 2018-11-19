#ifndef CAMERAH
#define CAMERAH
#include <GLM/glm.hpp>

class Camera {
private:
	glm::vec3 p_position;
	
	float p_pitch;
	float p_yaw;
	float p_roll;
	float p_sensitivity;
	float p_movementSpeed;

	glm::dvec2 p_lastMousePos;
	glm::dvec2 p_currentMousePos;

public:

	Camera(const glm::vec3& position);
	virtual ~Camera();

	void update(const float& dt);

	void setMouseSensitivity(const float& sen);
	void setMovementSpeed(const float& speed);

	const glm::vec3& getPosition() const;
	const float& getPitch() const;
	const float& getYaw() const;
	const float& getRoll() const;

};



#endif
