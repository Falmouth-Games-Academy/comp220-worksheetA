#include "Camera.h"

Camera::Camera()
{
	// position
	position = glm::vec3(0, 0, 5);
	// horizontal angle : toward -Z
	horizontalAngle = M_PI;
	// vertical angle : 0, look at the horizon
	verticalAngle = 0.0f;
	// Initial Field of View
	initialFoV = 70.0f;

	speed = 0.003f; // 3 units / second
	mouseSpeed = 3.0f;
}

glm::mat4 Camera::viewMatrix()
{
	glm::mat4 viewMatrix = glm::lookAt(
		position,				// Camera is here
		position + direction(),	// and looks here : at the same position, plus "direction"
		up()					// Head is up (set to 0,-1,0 to look upside-down)
	);

	return viewMatrix;
};

glm::mat4 Camera::projectionMatrix(OpenGLWindow * openGLWindow)
{
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(initialFoV), ((float)openGLWindow->Width() / openGLWindow->Height()), 0.1f, 1000.0f);
	return projectionMatrix;
}

void Camera::mouseMovement(int xOffset, int yOffset, float deltaTime)
{
	//std::cout << xOffset << " " << yOffset << std::endl;
	horizontalAngle += mouseSpeed * deltaTime * xOffset;
	verticalAngle += mouseSpeed * deltaTime * yOffset;
}

void Camera::keyboardMovement(Camera_Movement key, float deltaTime)
{
	std::cout << "Before " << position[0] << " " << position[1] << " " << position[2] << " ";
	// Move forward
	if (key == FORWARD) {
		std::cout << "Direction " << this->direction()[0] << " " << this->direction()[1] << " " << this->direction()[2] << " ";
		position += this->direction(); //* deltaTime * speed;
	}
	// Move backward
	if (key == BACKWARD) {
		position -= this->direction() * deltaTime * speed;
	}
	// Strafe right
	if (key == RIGHT) {
		position += right() * deltaTime * speed;
	}
	// Strafe left
	if (key == LEFT) {
		position -= right() * deltaTime * speed;
	}

	std::cout << "After " << position[0] << " " << position[1] << " " << position[2] << std::endl;
}

glm::vec3 Camera::direction()
{
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	return direction;
}

glm::vec3 Camera::right()
{
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - M_PI / 2.0f),
		0,
		cos(horizontalAngle - M_PI / 2.0f)
	);
	return right;
}

glm::vec3 Camera::up()
{
	glm::vec3 up = glm::cross(right(), direction());
	return up;
}
