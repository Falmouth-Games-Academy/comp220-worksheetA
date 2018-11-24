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

	void Update(float deltaTime);

	void SetPosition(float x, float y, float z)
	{
		Position = glm::vec3(x, y, z);
	};

	void SetRotation(float x, float y, float z)
	{
		Rotation = glm::vec3(x, y, z);
	};

	void SetScale(float x, float y, float z)
	{
		Scale = glm::vec3(x, y, z);
	};

	glm::vec3& GetPosition()
	{
		return Position;
	};

	glm::mat4& GetModelTransformation()
	{
		return ModelMatrix;
	};

	void SetMesh(MeshCollection * meshes)
	{
		Meshes = meshes;
	};

	void setShader(std::string name)
	{
		shaderName = name;
	};


	std::string getShader()
	{
		return shaderName;
	};

	void SetDiffuseTexture(GLuint texture)
	{
		DiffuseTexture = texture;
	};

	GLuint GetDiffuseTexture()
	{
		return DiffuseTexture;
	};

	void Render();

private:
	//Set up positions for position, rotation and scale
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	//calculate the translation, rotation and scale matrices using the above vectores
	glm::mat4 TranslationMatrix;
	glm::mat4 RotationMatrix;
	glm::mat4 ScaleMatrix;
	//combine the above matrices into the model matrix (order is important!!!! - TRS)
	glm::mat4 ModelMatrix;

	//Mesh
	MeshCollection * Meshes;

	//Shader
	std::string shaderName;

	//Texture
	GLuint DiffuseTexture;
};