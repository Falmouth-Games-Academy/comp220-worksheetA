#include "GameObject.h"

std::vector<GameObject*> GameObject::gameObjects;

GameObject::~GameObject()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
}

void GameObject::Init(const GLuint& inProgram)
{
	// Add gameObject to list of created objects
	gameObjects.push_back(this);

	// A Transform is a required component for all GameObjects
	AddComponent(Transform());
	transform = GetComponent(Transform());
}

void GameObject::Render()
{
	GetComponent(Model())->Render();
}

void GameObject::DeleteAll()
{
	for (auto& i : gameObjects)
		delete i;
}
