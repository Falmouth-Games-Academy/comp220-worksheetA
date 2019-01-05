#pragma once
#include <glm/glm.hpp>
#include <iostream>

namespace globals
{
	// The starting skybox number (there is 8 skyboxes to choose from)
	const int skyBoxNum = 2;

	// Window size of the application
	const float SCREEN_WIDTH = 800.0f;
	const float SCREEN_HEIGHT = 600.0f;

	// The World axis
	extern const glm::vec3 worldUp;
	extern const glm::vec3 worldRight;
	extern const glm::vec3 worldForward;

	// Camera speed movment variables
	const float cameraMovSpeed = 2.5f;
	const float cameraShiftIncreaseSpeed = 4;
}