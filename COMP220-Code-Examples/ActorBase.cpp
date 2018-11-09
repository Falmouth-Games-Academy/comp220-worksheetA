#include "ActorBase.h"



ActorBase::ActorBase()
{
}


ActorBase::ActorBase(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
}

ActorBase::~ActorBase()
{
}

glm::vec3 ActorBase::forwardVector()
{
	return glm::vec3();
}

void ActorBase::setLocalRotation(float x, float y, float z)
{

}

void ActorBase::setLocalTranslation(float x, float y, float z)
{

}

void ActorBase::setWorldRotation(float x, float y, float z)
{
}

void ActorBase::setWorldTranslation(float x, float y, float z)
{
}

glm::mat4 ActorBase::translationMatrix()
{
	return glm::translate(position);
}

glm::mat4 ActorBase::rotationMatrix()
{
	return glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 ActorBase::scaleMatrix()
{
	return glm::scale(scale);
}

glm::mat4 ActorBase::modelMatrix()
{
	return translationMatrix() * rotationMatrix() * scaleMatrix();
}
