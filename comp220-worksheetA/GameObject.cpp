#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::update()
{
	//calculate the translation, rotation and scale matrices using the above vectores
	translationMatrix = glm::translate(position);
	rotationMatrix = 
		 glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	scaleMatrix = glm::scale(scale);

	//combine the above matrices into the model matrix (order is important!!!! - TRS)
	modelMatrix = translationMatrix*rotationMatrix*scaleMatrix;
}

void GameObject::render()
{
	model->render();
}
