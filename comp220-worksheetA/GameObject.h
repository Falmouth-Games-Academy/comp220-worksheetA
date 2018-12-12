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

	// Position Rotation and Scale
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

	// Mesh
	MeshCollection * GetMeshes() 
	{
		return Meshes;
	};

	glm::mat4& GetModelTransformation()
	{
		return ModelMatrix;
	};

	void SetMesh(MeshCollection * meshes)
	{
		Meshes = meshes;
	};

	// Shader
	void setShader(std::string name)
	{
		shaderName = name;
	};


	std::string getShader()
	{
		return shaderName;
	};

	// Textures
	void SetDiffuseTexture(std::string texture)
	{
		diffuseTexture = loadTextureFromFile(texture);
	};

	GLuint GetDiffuseTexture()
	{
		return diffuseTexture;
	};

	void SetDiffuseTextures(std::string texture)
	{
		diffuseTexture = loadTextureFromFile(texture);
		textureList.push_back(diffuseTexture);
	};

	void SetActiveTexture(int textureNum)
	{
		diffuseTexture = textureList[textureNum];
	};

	// GameObject Name
	void setName(std::string gameObjectName)
	{
		Name = gameObjectName;
	};

	std::string getName()
	{
		return Name;
	};

	void Render();

private:

	// the name of the gameobject
	std::string Name;

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
	GLuint diffuseTexture;
	GLuint activeDiffuseTexture;
	std::vector<GLuint> textureList;

};