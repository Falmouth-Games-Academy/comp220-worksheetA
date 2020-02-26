#pragma once

#include "Base.h"
#include "IComponentCamera.h"

class Camera : public IComponentCamera
{
public:
	Camera() {};
	~Camera() {};

	void Init(GLuint programId) { this->programId = programId; };

	glm::mat4 GetProjectionMatrix(bool perspective, float fov, float aspectRatio, float nearClipPlane, float farClipPlane)
	{
		return glm::perspective(glm::radians(fov), aspectRatio, nearClipPlane, farClipPlane);
	}

	glm::mat4 GetViewMatrix(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp)
	{
		return glm::lookAt(cameraPosition, cameraTarget, cameraUp);
	}

	virtual void Update() override {};
protected:
	GLuint programId;
private:

};