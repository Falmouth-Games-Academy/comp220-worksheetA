#pragma once
#include <string>
#include <GL\glew.h>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "texture.h"
#include "Model.h"
#include "Mesh.h"
#include "shader.h"


class GameObject
{
public:
	GameObject();
	~GameObject();

	MeshCollection * model;

	void update();
	void render();
	void attachMesh(MeshCollection *mesh)
	{
		model = mesh;
	};
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

	//Set up positions for position, rotation and scale
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::mat4 modelMatrix;

	void setShader(std::string name)
	{
		shaderName = name;
	};
		

	std::string getShader()
	{
		return shaderName;
	};


private:

	std::string shaderName;

};