#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::KeyboardEvents(SDL_Event event)
{
	keyState[event.key.keysym.sym] = event.key.state;
}

bool Player::isPressed(SDL_Keycode key)
{
	return keyState[key] = SDL_PRESSED;
}

bool Player::isReleased(SDL_Keycode key)
{
	return keyState[key] = SDL_RELEASED;
}

void Player::ProcessInputs(float deltaTime)
{
	cameraPosition = camera.GetCameraPosition();
	cameraTarget = camera.GetCameraFront();
	cameraUp = camera.GetCameraUp();
	movementSpeed = camera.GetCameraSpeed() * deltaTime;
	if (isPressed(SDLK_w))
	{
		camera.IncreaseCameraPosition(movementSpeed * cameraTarget);
	}
	if (isPressed(SDLK_s))
	{
		camera.IncreaseCameraPosition(-movementSpeed * cameraTarget);
	}
	if (isPressed(SDLK_a))
	{
		camera.IncreaseCameraPosition(-glm::normalize(glm::cross(cameraTarget, cameraUp)) * movementSpeed);
	}
	if (isPressed(SDLK_d))
	{
		camera.IncreaseCameraPosition(glm::normalize(glm::cross(cameraTarget, cameraUp)) * movementSpeed);
	}
	if (isPressed(SDLK_SPACE))
	{
		camera.IncreaseCameraPosition(glm::vec3(0, camera.GetCameraSpeed(), 0) * movementSpeed);
	}
	if (isPressed(SDLK_LSHIFT))
	{
		camera.IncreaseCameraPosition(glm::vec3(0, -camera.GetCameraSpeed(), 0) * movementSpeed);
	}

}

void Player::ClearEvents()
{
	keyState.clear();
}

void Player::MouseMovement(float xPos, float yPos)
{
	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	float sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	camera.SetCameraFront(glm::normalize(front));
}
