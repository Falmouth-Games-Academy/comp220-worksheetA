#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::UpdateView()
{
	glm::mat4 matRoll = glm::mat4(1.0f);
	glm::mat4 matPitch = glm::mat4(1.0f);
	glm::mat4 matYaw = glm::mat4(1.0f);

	matRoll = glm::rotate(matRoll, roll, glm::vec3(0.0f, 0.0f, 1.0f));
	matPitch = glm::rotate(matPitch, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	matYaw = glm::rotate(matYaw, yaw, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 rotate = matRoll * matPitch * matYaw;

	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, -eyeVector);

	viewMatrix = rotate * translate;

}

void Camera::KeyPressed()
{
	float dx = 0; // how much we strafe on x
	float dz = 0; // how much we strafe on z
	switch (key)
	{
		case 'w':
		{
			dz = 2;
			break;
		}
		case 's':
		{
			dz = -2;
			break;
		}
		case 'a':
		{
			dx = -2;
			break;
		}
		case 'd':
		{
			dx = 2;
			break;
		}
		default:
			break;
	}

	glm::mat4 mat = GetViewMatrix();

	glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
	glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

	const float speed = 0.12f; // how fast we move

	eyeVector += (-dz * forward + dx * strafe) * speed;

	UpdateView();
}

void Camera::MoveMouse()
{
	int x;
	int y;
	int width;
	int height;
	if (isMousePressed == false)
	{
		return;
	}

	glm::vec2 mouseDelta = glm::vec2(x, y) - mousePosition;

	const float mouseXSensitivity = 0.25f;
	const float mouseYSensitivity = 0.25f;

	yaw += mouseXSensitivity * mouseDelta.x;
	pitch += mouseYSensitivity * mouseDelta.y;

	mousePosition = glm::vec2(x, y);
	UpdateView();
}

void Camera::MousePressed()
{
	int button;
	int state;
	int x;
	int y;
	if (state == SDL_KEYUP)
	{
		isMousePressed = false;
	}
	if (state == SDL_KEYDOWN)
	{
		isMousePressed = true;
		mousePosition.x = x;
		mousePosition.y = y;
	}
}
