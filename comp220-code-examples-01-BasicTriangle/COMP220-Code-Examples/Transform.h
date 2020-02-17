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

class Transform : public IComponent
{
public:
	Transform() { componentFlags = ComponentFlags::TRANSLATION; };
	~Transform() {};
	///<summary>
	/// Returns the transform location in world space
	///</summary>
	glm::vec3 Position() { return position; }
	///<summary>
	/// Returns the transform scale
	///</summary>
	glm::vec3 Scale() { return scale; }
	///<summary>
	/// Returns the transform rotation as a quaternion
	///</summary>
	glm::quat Rotation() { return rotation; }
	///<summary>
	/// Returns the transform rotation as a vec3 of euler angles
	///</summary>
	glm::vec3 EulerRotation() { return glm::eulerAngles(rotation); }
private:
	glm::vec3 position= glm::vec3(1.0);
	glm::vec3 scale = glm::vec3(1.0);
	glm::quat rotation;

	// Matrix used for converting to and from model space
	glm::mat4 modelMatrix = glm::mat4(1.0);

	glm::mat4 translationMatrix = glm::mat4(1.0);
	glm::mat4 rotationMatrix = glm::mat4(1.0);
	glm::mat4 scaleMatrix = glm::mat4(1.0);
};