#pragma once

#include "Libraries.h"
#include "Model.h"
#include "Camera.h"
#include "GameObject.h"
#include "Texture.h"
#include "Player.h"
#include "Shader.h"
#include "Mesh.h"
#include "Skybox.h"

class Game
{
public:
	Game();
	~Game();

	int Loop();
	int InitialiseSDL();
	int InitialiseGLEW();
	int Initialise();

	void LoadingScene();
	void Render();
	void Clean();
	void SetFullscreen();

	glm::mat4 GetViewMatrix()
	{
		return viewMatrix;
	}
	

	bool SetOpenGLAttributes();

private:
	SDL_Window* mainWindow = nullptr;
	Camera camera;
	Player player;

	SDL_GLContext gl_Context;

	//GLuint textureID;
	GLuint diffuseTextureID;
	GLuint specularTextureID;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	glm::vec4 ambientLightColor;
	glm::vec4 ambientMaterialColor;
	glm::vec4 diffuseLightColor;
	glm::vec4 diffuseMaterialColor;
	glm::vec4 specularLightColor;
	glm::vec4 specularMaterialColor;

	glm::vec3 cameraPosition;
	glm::vec3 cameraUp;
	glm::vec3 cameraLook;
	glm::vec3 lightDirection;

	std::vector<GameObject*> GameObjectList;

	Skybox* skybox;
	MeshCollection* teapotMesh = new MeshCollection();
	Shader* texturedShader = new Shader();
	GameObject* teapotGO = new GameObject();
	GameObject* teapotGO1 = new GameObject();

	float lastTime = 0;
	float tickTime = 0;
	float deltaTime = 0;
	float specularMaterialPower;

	bool isRunning = false;
	bool isFullscreen = false;
};

