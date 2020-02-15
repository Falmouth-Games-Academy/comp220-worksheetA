#pragma once

#include <sstream>
#include <fstream>
#include <iostream>

#include <array>
#include <vector>
#include <map>

#include "Transform.h"
#include "Model.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

class GameObject
{
public:
	// Constructor & destructor
	GameObject() {};
	~GameObject();

	// Initialize mesh
	void Init(const std::vector<GLfloat> &inVertices, const GLuint &inProgram);

	// Render object
	void Render();

	// Get component of type T or a nullptr if none is found
	template<typename T>
	T* GetComponent(T);

	// Add a component of type T
	template<typename T>
	void AddComponent(T);

	static void DeleteAll();

	Transform* transform;

protected:
	GLuint vertexArray = -1;
	GLuint vertexBuffer = -1;
	std::vector<GLfloat> vertices;
	GLuint shaderProgram = -1;
private:
	static std::vector<GameObject*> gameObjects;
	std::vector<IComponent*> components;
};

template<typename T>
inline T* GameObject::GetComponent(T)
{
	for (auto& i : components) 
		if (dynamic_cast<T*>(i) != NULL && typeid(dynamic_cast<T*>(i)) == typeid(T*))
			return dynamic_cast<T*>(i);

	return nullptr;
}

template<typename T>
inline void GameObject::AddComponent(T)
{
	components.push_back(new T());
}
