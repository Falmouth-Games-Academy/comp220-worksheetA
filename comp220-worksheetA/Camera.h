#pragma once
#include <GL\glew.h>
#include "Globals.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace glm;

class Camera
{
public:
	Camera();
	~Camera();

	mat4 CalculateViewMatrix();
	void Strafe(glm::vec3 mov, float delta);

	glm::mat4 Projection;

	glm::quat rotation = glm::identity<quat>();
	
	void MouseMovement(int x, int y);


private:

	vec3 pos = glm::vec3(-5, 0, 0);
	vec3 lookAt = glm::vec3(0, 0, 0);

	vec3 cameraUp = glm::vec3(0, 1, 0);
	vec3 cameraForward = glm::vec3(1, 0, 0);
	vec3 cameraRight = glm::vec3(0, 0, 1);
};