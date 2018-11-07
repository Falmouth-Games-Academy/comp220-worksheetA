#pragma once
#include <GL\glew.h>
#include "Globals.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Camera
{
public:
	Camera();
	~Camera();

	mat4 CalculateViewMatrix();
	void Strafe(glm::vec3 mov, float delta);

	glm::mat4 Projection;

private:

	vec3 pos = glm::vec3(0, -3, 0);
	vec3 lookAt = glm::vec3(0, 0, 0);
	vec3 up = glm::vec3(0, 0, 1);
};