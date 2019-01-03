#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <math.h>         // Used only for sin() and cos() functions

#include <glm/glm.hpp> // Old header file standard (.hpp)

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGLWindow.h"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera();

	void mouseMovement(int xOffset, int yOffset, float deltaTime);
	void keyboardMovement(Camera_Movement direction, float deltaTime);
	glm::vec3 direction();
	glm::vec3 right();
	glm::vec3 up();

	glm::mat4 viewMatrix();
	glm::mat4 projectionMatrix(OpenGLWindow * openGLWindow);
private:
	// position
	glm::vec3 position;
	// horizontal angle : toward -Z
	float horizontalAngle;
	// vertical angle : 0, look at the horizon
	float verticalAngle;
	// Initial Field of View
	float initialFoV;

	float speed;
	float mouseSpeed;
};

#endif // CAMERA_H