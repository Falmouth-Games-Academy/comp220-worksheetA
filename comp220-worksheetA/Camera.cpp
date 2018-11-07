#include "Camera.h"

Camera::Camera()
{
	
}

Camera::~Camera()
{

}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(pos, lookAt, up);
}

void Camera::Strafe(glm::vec3 mov,float delta)
{
	pos += mov * delta;
	lookAt += mov * delta;
}