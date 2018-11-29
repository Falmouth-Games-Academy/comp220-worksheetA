#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Mesh.h"
#include "Shaders.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update(float deltaTime);
	void Render();

	// Position
	void SetPosition(float x, float y, float z)
	{
		Position = glm::vec3(x, y, z);
	};

	glm::vec3& GetPosition()	// Returns a reference instead of a copy (faster)
	{
		return Position;
	};

	// Rotation
	void SetRotation(float x, float y, float z)
	{
		Rotation = glm::vec3(x, y, z);
	};

	glm::vec3& GetRotation()
	{
		return Rotation;
	};

	// Scale
	void SetScale(float x, float y, float z)
	{
		Scale = glm::vec3(x, y, z);
	};

	glm::vec3& GetScale()
	{
		return Scale;
	};

	// Model transformation
	glm::mat4& GetModelTransformation()
	{
		return ModelMatrix;
	};

	// Set Mesh
	void SetMesh(MeshCollection * meshes)
	{
		Meshes = meshes;
	};

	// Shader
	void SetShader(Shader * shader)
	{
		ShaderProgram = shader;
	};

	Shader * GetShader()
	{
		return ShaderProgram;
	};

	// Diffuse texture
	void SetDiffuseTexture(GLuint texture)
	{
		DiffuseTexture = texture;
	};

	GLuint GetDiffuseTexture()
	{
		return DiffuseTexture;
	};

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

	// Should make a manager class for handling Meshes,ShaderProgram and DiffuseTexture
	// So then the game object won't own them and won't need to handle deleting them
	// Should only import 1x teapot mesh which then is used for multiple instances/objects (example)

	//Mesh
	MeshCollection * Meshes;

	//Shader
	Shader * ShaderProgram;

	//Texture
	GLuint DiffuseTexture;
};