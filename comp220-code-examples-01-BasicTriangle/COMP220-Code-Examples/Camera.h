#pragma once

#include <sstream>
#include <fstream>
#include <iostream>

#include <vector>
#include <map>

#include "IComponent.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

class Camera : public IComponent
{
public:
	Camera() { componentFlags = ComponentFlags::CAMERA; };
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

	void Update();
protected:
	GLuint programId;
private:

};