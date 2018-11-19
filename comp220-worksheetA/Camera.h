#pragma once

#include "Libraries.h"

class Camera
{
public:
	Camera();
	~Camera();

	void KeyboardEvents(SDL_Event event);

private:
	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 up;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
	
	glm::mat4 view;

	void ProcessInputs(SDL_Keycode key);

	bool isPressed(SDL_Keycode key);
	bool isReleased(SDL_Keycode key);

	float radius = 10.0f;
	float yaw;
	float pitch;
	float movementSpeed;
	float mouseSensitivity;

	std::map<SDL_Keycode, Uint8> keyState;

};

