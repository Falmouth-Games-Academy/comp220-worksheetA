#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class ActorBase
{
public:
	ActorBase(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	ActorBase();
	~ActorBase();

	glm::vec3 position = glm::vec3(0.0f, -8.0f, -50.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 forwardVector();

	void setLocalRotation(float x, float y, float z);
	void setLocalTranslation(float x, float y, float z);

	void setWorldRotation(float x, float y, float z);
	void setWorldTranslation(float x, float y, float z);

	glm::mat4 translationMatrix();
	glm::mat4 rotationMatrix();
	glm::mat4 scaleMatrix();
	glm::mat4 modelMatrix();

};

