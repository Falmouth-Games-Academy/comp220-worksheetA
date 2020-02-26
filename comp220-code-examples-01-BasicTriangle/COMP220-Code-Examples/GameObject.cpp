#include "GameObject.h"

std::vector<GameObject*> GameObject::gameObjects;

GameObject::~GameObject()
{
	/*glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexArray);*/
}

void GameObject::Init(const GLuint& inProgram)
{
	// Add gameObject to list of created objects
	gameObjects.push_back(this);
}

void GameObject::Update()
{

}

void GameObject::Render()
{
	
}

void GameObject::DeleteAll()
{
	for (auto& i : gameObjects)
		delete i;
}
