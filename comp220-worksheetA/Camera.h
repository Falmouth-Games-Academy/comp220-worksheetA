#pragma once

#include "Libraries.h"

class Camera
{
public:
	Camera();
	~Camera();

	void UpdateView();
	void KeyPressed();
	void MoveMouse();
	void MousePressed();

	glm::mat4 GetViewMatrix()
	{
		return viewMatrix;
	}

private:
	glm::mat4 viewMatrix;

	glm::vec3 eyeVector;

	glm::vec2 mousePosition;

	float roll;
	float pitch;
	float yaw;

	const unsigned char key;

	bool isMousePressed = false;
};

