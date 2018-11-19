#include "Camera.h"



Camera::Camera()
{
	cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

	cameraDirection = glm::normalize(cameraPosition - cameraTarget);

	up = glm::vec3(0.0f, 1.0f, 0.0f);

	cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	cameraUp = glm::cross(cameraDirection, cameraRight);

	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}


Camera::~Camera()
{
}

void Camera::ProcessInputs(SDL_Keycode key)
{
	float cameraSpeed = 0.5f;
	if (isPressed(SDLK_w))
	{
		cameraPosition += cameraSpeed * cameraFront;
	}
	if (isPressed(SDLK_s))
	{
		cameraPosition -= cameraSpeed * cameraFront;
	}
	if (isPressed(SDLK_a))
	{
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (isPressed(SDLK_d))
	{
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

}

void Camera::KeyboardEvents(SDL_Event event)
{
	keyState[event.key.keysym.sym] = event.key.state;
}

bool Camera::isPressed(SDL_Keycode key)
{
	return keyState[key] = SDL_PRESSED;
}

bool Camera::isReleased(SDL_Keycode key)
{
	return keyState[key] = SDL_RELEASED;
}
