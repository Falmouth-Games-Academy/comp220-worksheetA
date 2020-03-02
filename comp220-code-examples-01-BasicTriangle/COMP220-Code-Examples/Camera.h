#pragma once

#include "Base.h"
#include "IComponentCamera.h"

class Camera : public IComponentCamera
{
public:
	Camera() {};
	~Camera() {};

	void Init(GLuint programId) { this->programId = programId; };

	glm::mat4 GetProjectionMatrix()
	{
		return glm::perspective(glm::radians(fov), aspectRatio, nearClipPlane, farClipPlane);
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(transform->Position(), transform->Position() + transform->Forward(), glm::vec3(0, 1, 0));
	}

	virtual void Update() override {};
protected:
	GLuint programId;
private:
	bool perspective = true;
	float fov = 45;
	float aspectRatio = 16.0 / 9.0;
	float nearClipPlane = 0.01;
	float farClipPlane = 100.0;
};