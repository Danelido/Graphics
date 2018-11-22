#ifndef CREATEMATRIXH
#define CREATEMATRIXH
#include "../Camera/Camera.h"
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <GLM/gtc/matrix_transform.hpp>
namespace CreateMatrix {

	static glm::mat4 modelMatrix(glm::vec3 translation, glm::vec3 rotation, float scale) {
		glm::mat4 matrix = glm::mat4(1.0f);
		matrix = glm::translate(matrix, translation);
		matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
		return matrix;
	}

	static glm::mat4 viewMatrix(const Camera& camera)
	{
		glm::mat4 matrix = glm::mat4(1.0f);
		matrix = glm::rotate(matrix, camera.getPitch(), glm::vec3(1.f, 0.f, 0.f));
		matrix = glm::rotate(matrix, camera.getYaw(),	glm::vec3(0.f, 1.f, 0.f));
		matrix = glm::rotate(matrix, camera.getRoll(),	glm::vec3(0.f, 0.f, 1.f));
		matrix = glm::translate(matrix, -camera.getPosition());
		return matrix;
	}

	/* FOV = 45 */
	static glm::mat4 PerspectiveProjectionMatrix(float screenWidth, float screenHeight, float near, float far)
	{
		return glm::perspective(glm::radians(45.f), screenWidth / screenHeight, near, far);
	}

}


#endif
