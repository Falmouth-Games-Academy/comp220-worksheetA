#pragma once
#include <glm/glm.hpp> // Old header file standard (.hpp)

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGLWindow.h"

class Camera {
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position)
	{
		this->position = position;
	};
	glm::vec3 GetPosition()
	{
		return position;
	};

	void SetDirection(glm::vec3 direction)
	{
		this->direction = direction;
	};
	glm::vec3 GetDirection()
	{
		return direction;
	};

	void SetUp(glm::vec3 up)
	{
		this->up = up;
	};
	glm::vec3 GetUp()
	{
		return up;
	}

	glm::mat4 ViewMatrix();
	glm::mat4 ProjectionMatrix(OpenGLWindow * openGLWindow);

private:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;

	float fieldOfView;
};