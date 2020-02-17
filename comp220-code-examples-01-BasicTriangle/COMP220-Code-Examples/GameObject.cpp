#include "GameObject.h"

std::vector<GameObject*> GameObject::gameObjects;

GameObject::~GameObject()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
}

void GameObject::Init(const std::vector<GLfloat>& inVertices, const GLuint& inProgram)
{
	// Add gameObject to list of created objects
	gameObjects.push_back(this);
	// Pass vertices to gameObject
	vertices = inVertices;

	// A Transform is a required component for all GameObjects
	AddComponent(Transform());
	transform = GetComponent(Transform());

	AddComponent(Model());
	
	shaderProgram = inProgram;

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
}

void GameObject::Render()
{
	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,
		3,	// Number of components that make up a vertex
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
	glDisableVertexAttribArray(0);
}

void GameObject::DeleteAll()
{
	for (auto& i : gameObjects)
		delete i;
}
