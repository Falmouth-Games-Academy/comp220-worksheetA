#pragma once

#include <sstream>
#include <fstream>
#include <iostream>

#include <array>
#include <vector>
#include <map>

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

class GameObject
{
public:
	// Constructor & destructor
	GameObject() {};
	~GameObject();

	// Initialize gameObject
	void Init(const GLuint &inProgram);

	// Update GameObject
	void Update();
	// Render object
	void Render();

	// Get component of type T or a nullptr if none is found
	template<typename T>
	T* GetComponent(T);

	// Add a component of type T
	template<typename T>
	void AddComponent(T);

	// Deletes all created gameObjects
	static void DeleteAll();

protected:
private:
	static std::vector<GameObject*> gameObjects;
};