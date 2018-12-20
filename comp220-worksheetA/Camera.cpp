#include "Camera.h";

#include <iostream>

Camera::Camera()
{
	position = glm::vec3(0.0f, 0.0f, 10.0f);
	front = glm::vec3(0.0f, 0.0f, -10.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	direction = glm::vec3(0.0f, 0.0f, -10.0f);

	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	yaw = YAW;
	pitch = PITCH;

	movementSpeed = SPEED;
	mouseSensitivity = SENSITIVITY;

	fieldOfView = 90.0f;

	UpdateDirection();
}

Camera::~Camera()
{

}

glm::mat4 Camera::ViewMatrix()
{
	return glm::lookAt(position, position + direction, up);
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

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	std::cout << "Before " << position.x << " " << position.y << " " << position.z << std::endl;

	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += velocity * front;
	if (direction == BACKWARD)
		position -= velocity * front;
	if (direction == LEFT)
		position -= glm::normalize(glm::cross(front, up)) * velocity;
	if (direction == RIGHT)
		position += glm::normalize(glm::cross(front, up)) * velocity;

	std::cout << "After " << position.x << " " << position.y << " " << position.z << std::endl;

	//UpdateDirection();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, float deltaTime)
{
	xoffset *= 0.1f;
	yoffset *= 0.1f;

	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (true)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(front);

	// Update Front, Right and Up Vectors using the updated Euler angles
	UpdateDirection();
}

/*
void Camera::ProcessMouseMovement(float xOffset, float yOffset, float deltaTime)
{
	xOffset *= mouseSensitivity * deltaTime;
	yOffset *= mouseSensitivity * deltaTime;

	yaw += xOffset;
	pitch += yOffset;

	pitch = ClampPitch(pitch);

	UpdateDirection();
}
*/
float Camera::ClampPitch(float pitch)
{
	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;
	return pitch;
}

void Camera::UpdateDirection()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));
}

/*
void Camera::UpdateDirection()
{
	UpdateFront();
	UpdateRight();
	UpdateUp();
}
*/

void Camera::UpdateFront()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	Camera::front = glm::normalize(front);
}

void Camera::UpdateRight()
{
	right = glm::normalize(glm::cross(front, worldUp)); // Normalize the vectors, because their length gets closer to 0
}

void Camera::UpdateUp()
{
	up = glm::normalize(glm::cross(right, front));
}