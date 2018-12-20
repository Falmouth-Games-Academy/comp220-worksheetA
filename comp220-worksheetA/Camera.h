#pragma once
#include <glm/glm.hpp> // Old header file standard (.hpp)

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGLWindow.h"

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 20.5f;
const float SENSITIVITY = 160.0f;

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

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

	glm::mat4 ViewMatrix();
	glm::mat4 ProjectionMatrix(OpenGLWindow * openGLWindow);

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xOffset, float yOffset, float deltaTime);

private:
	glm::vec3 position;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 direction;

	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float mouseSensitivity;

	float fieldOfView;

	float ClampPitch(float pitch);

	void UpdateDirection();
	void UpdateFront();
	void UpdateRight();
	void UpdateUp();
};