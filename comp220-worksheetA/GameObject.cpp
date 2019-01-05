#include "GameObject.h"

// The initial set values of a GameObject
GameObject::GameObject()
{
	Position = glm::vec3(0.0f);
	Scale = glm::vec3(1.0f);
	Rotation = glm::vec3(0.0f);

	TranslationMatrix = glm::mat4(0.0f);
	RotationMatrix = glm::mat4(0.0f);
	ScaleMatrix = glm::mat4(0.0f);
	ModelMatrix = glm::mat4(0.0f);

	Meshes = nullptr;
	//ShaderProgram = nullptr;
	diffuseTexture = 0;
}

GameObject::~GameObject()
{
	glDeleteTextures(1, &diffuseTexture);
}

// List of functions to create gameObjects using different parameters //
void GameObject::CreateGameObject(std::string name, glm::vec3 pos)
{
	setName(name);
	SetPosition(pos.x,pos.y,pos.z);
}

void GameObject::CreateGameObject(std::string name, glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation, MeshCollection * model, std::string shader)
{
	CreateGameObject(name, pos);
	SetScale(scale.x, scale.y, scale.z);
	SetRotation(rotation.x, rotation.y, rotation.z);
	SetMesh(model);
	setShader(shader);
}

void GameObject::CreateGameObject(std::string name, glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation, MeshCollection * model, std::string shader, std::string texture)
{
	CreateGameObject(name, pos, scale, rotation, model, shader);
	SetDiffuseTexture(texture);
}

// Update for a gameobject
void GameObject::Update(float deltaTime)
{
	TranslationMatrix = glm::translate(Position);
	RotationMatrix = (
		 glm::rotate(Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::rotate(Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::rotate(Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f))
		);
	
	ScaleMatrix = glm::scale(Scale);

	//combine the above matrices into the model matrix (order is important!!!! - TRS)
	ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;
}

// Rendering function to render the mesh of a gameObject
void GameObject::Render()
{
	if (Meshes)
	{
		Meshes->render();
	}
}


