#pragma once

#include "Base.h"
#include "GLUtils.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Transform
{
public:
	Transform() {};
	virtual ~Transform() {};

	///<summary>
	/// Returns the transformation matrix
	///</summary>
	glm::mat4 GetTransformation() { return translationMatrix * rotationMatrix * scaleMatrix; }
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
	///<summary>
	/// Move GameObject by certain amount
	///</summary>
	void Move(glm::vec3 velocity);
	///<summary>
	/// Move GameObject to certain position
	///</summary>
	void MoveTo(glm::vec3 position);
	///<summary>
	/// Rotate GameObject by anglees
	///</summary>
	void RotateAngles(glm::vec3 axis, float angle);
	///<summary>
	/// Scale GameObject
	///</summary>
	void Scale(glm::vec3 scale);

private:
	glm::vec3 position = glm::vec3(1.0);
	glm::vec3 scale = glm::vec3(1.0);
	glm::quat rotation = glm::quat(0, 0, 0, 0);

	glm::vec3 up = glm::vec3(0, 1, 0);

	// Matrix used for converting to and from model space
	// glm::mat4 modelMatrix = glm::mat4(1.0);

	glm::mat4 translationMatrix = glm::mat4(1.0);
	glm::mat4 rotationMatrix = glm::mat4(1.0);
	glm::mat4 scaleMatrix = glm::mat4(1.0);

	// List of all transforms parented to thi Transform
	std::vector<Transform*> children;
	// Parent Transform of this Transform
	Transform* parent;
};