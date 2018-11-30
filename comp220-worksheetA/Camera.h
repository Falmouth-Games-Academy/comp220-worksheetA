#pragma once

#include "Libraries.h"

class Camera
{
public:
	Camera();
	~Camera();

	glm::vec3 GetCameraPosition()
	{
		return cameraPosition;
	};
	glm::vec3 GetCameraFront()
	{
		return cameraFront;
	};
	glm::vec3 GetCameraUp()
	{
		return cameraUp;
	};

	void SetCameraPosition(glm::vec3 newCameraPosition)
	{
		cameraPosition = newCameraPosition;
	};
	void IncreaseCameraPosition(glm::vec3 newCameraPosition)
	{
		cameraPosition += newCameraPosition;
	};
	void SetCameraFront(glm::vec3 newCameraFront)
	{
		cameraFront = newCameraFront;
	};
	float GetCameraSpeed()
	{
		return cameraSpeed;
	};

private:
	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 up;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;

	float cameraSpeed = 0.05f;
};

