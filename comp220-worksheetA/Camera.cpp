#include "Camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

glm::mat4 Camera::CalculateViewMatrix()
{
	return View;
}

void Camera::Strafe(glm::vec3 mov, float delta)
{
	pos += mov * rotation * delta;
	View = glm::lookAt(pos, lookAt, cameraUp);
}

void Camera::MouseMovement(int x, int y)
{
	
	rotation = rotation * glm::angleAxis(x * 0.001f, globals::worldUp);
	rotation = rotation * glm::angleAxis(y * 0.001f, cameraRight);
	
	cameraForward = globals::worldForward * rotation;
	cameraUp = globals::worldUp * rotation;
	cameraRight = globals::worldRight * rotation;

	lookAt = pos + cameraForward;
	
	View = glm::lookAt(pos, lookAt, cameraUp);
}

