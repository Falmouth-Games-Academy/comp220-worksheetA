#include "Camera.h";

Camera::Camera()
{
	position = glm::vec3(0.0f, 0.0f, 10.0f);
	direction = glm::vec3(0.0f, 0.0f, -10.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	fieldOfView = 90.0f;
}

Camera::~Camera()
{

}

glm::mat4 Camera::ViewMatrix()
{
	return glm::lookAt(position, direction, up);
};

glm::mat4 Camera::ProjectionMatrix(OpenGLWindow * openGLWindow)
{
	return glm::perspective(
		glm::radians(fieldOfView),
		((float)openGLWindow->Width() / openGLWindow->Height()),
		0.1f,
		1000.0f
	);
}