#pragma once

#include "Libraries.h"
#include "Camera.h"

class Player
{
public:
	Player();
	~Player();

	void KeyboardEvents(SDL_Event event);
	void ProcessInputs(float deltaTime);
	void ClearEvents();
	void MouseMovement(float xPos, float yPos);

	bool isPressed(SDL_Keycode key);
	bool isReleased(SDL_Keycode key);

private:

	std::map<SDL_Keycode, Uint8> keyState;

	Camera camera;

	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float movementSpeed; 
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 400;
	float lastY = 320;

	bool firstMouse = true;
};

