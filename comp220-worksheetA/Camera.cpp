#include "Camera.h"



Camera::Camera()
{
	cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	cameraTarget = glm::vec3(0.0f, 0.0f, 1.0f);

	cameraDirection = glm::normalize(cameraPosition - cameraTarget);

	up = glm::vec3(0.0f, 1.0f, 0.0f);

	cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	cameraUp = glm::cross(cameraDirection, cameraRight);

	cameraFront = glm::normalize(cameraDirection);

	//view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

	
}


Camera::~Camera()
{
}
