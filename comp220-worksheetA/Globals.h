#pragma once
#include <glm/glm.hpp>
#include <iostream>

namespace globals
{
	const int skyBoxNum = 2;

	const float SCREEN_WIDTH = 800.0f;
	const float SCREEN_HEIGHT = 600.0f;

	extern const glm::vec3 worldUp;
	extern const glm::vec3 worldRight;
	extern const glm::vec3 worldForward;

	const float cameraMovSpeed = 2.5f;
	const float cameraShiftIncreaseSpeed = 4;
}