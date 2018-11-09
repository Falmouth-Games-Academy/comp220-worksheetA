#pragma once
class Input;
class Camera;
#include <glm/glm.hpp>

class Controls {
public:

	Controls();
	~Controls();

	void cameraControls(Input &input, Camera &camera, float deltaTime);

	// Camera vars
	float cameraMovSpeed = 2.5f;
	glm::vec3 cameraMovementVec = glm::vec3(0.0f);

private:

};