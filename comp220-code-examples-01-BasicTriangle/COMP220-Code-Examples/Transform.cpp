#include "Transform.h"

void Transform::Move(glm::vec3 velocity)
{
	translationMatrix = glm::translate(translationMatrix, velocity);
	this->position = this->position + velocity;
}

void Transform::MoveTo(glm::vec3 position)
{
	translationMatrix = glm::translate(translationMatrix, position - this->position);
	this->position = position;
}

void Transform::RotateAngles(glm::vec3 axis, float angle)
{
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), axis);
	rotation = glm::quat_cast(rotationMatrix);
}

void Transform::Scale(glm::vec3 scale)
{
	scaleMatrix = glm::scale(scaleMatrix, scale);
	this->scale = scale;
}