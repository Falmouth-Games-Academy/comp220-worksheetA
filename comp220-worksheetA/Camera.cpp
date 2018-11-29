#include "Camera.h"



Camera::Camera()
{
	cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);

	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

	cameraDirection = glm::normalize(cameraPosition - cameraTarget);

	up = glm::vec3(0.0f, 1.0f, 0.0f);

	cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);;

	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	//view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

	
}


Camera::~Camera()
{
}
