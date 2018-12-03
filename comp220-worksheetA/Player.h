#pragma once

#include "Libraries.h"
#include "Camera.h"

class Player
{
public:
	Player();
	~Player();

	Camera camera;

	void KeyboardEvents(SDL_Event event);
	void ProcessInputs(float deltaTime);
	void ClearEvents();
	void MouseMovement(float xPos, float yPos);

	bool isPressed(SDL_Keycode key);
	bool isReleased(SDL_Keycode key);

private:

	std::map<SDL_Keycode, Uint8> keyState;

	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;

	float movementSpeed; 
	float yaw = 270.0f;
	float pitch = 0.0f;

	bool firstMouse = true;
};

