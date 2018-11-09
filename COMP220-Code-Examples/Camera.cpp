#include "Camera.h"



glm::mat4 Camera::viewMatrix()
{
	return glm::lookAt(position, rotation, cameraUp);
}

Camera::Camera()
{
}


Camera::~Camera()
{
}
