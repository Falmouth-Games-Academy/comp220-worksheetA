#pragma once
class Input;
class Camera;
#include <glm/glm.hpp>
#include "Globals.h"

class Controls {
public:

	Controls();
	~Controls();

	void cameraControls(Input &input, Camera &camera, float deltaTime);

	// Camera vars
	float cameraMovSpeed = globals::cameraMovSpeed;
	float cameraShiftIncreaseSpeed = globals::cameraShiftIncreaseSpeed;
	glm::vec3 cameraMovementVec = glm::vec3(0.0f);

private:

};