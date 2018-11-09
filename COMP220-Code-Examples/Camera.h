#pragma once
#include "ActorBase.h"
class Camera :
	public ActorBase
{
public:
	Camera();
	~Camera();

	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 viewMatrix();
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)800 / (float)640, 0.1f, 100.0f);
};

