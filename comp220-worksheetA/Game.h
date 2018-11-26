#pragma once

#include "Libraries.h"
#include "Model.h"
#include "Camera.h"
#include "GameObject.h"
#include "Texture.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();

	int loop();
	int initialiseSDL();
	int initialiseGLEW();
	int initialise();
	int getShaders();

	void render();
	void clean();
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

	GLuint VertexArrayID;
	GLuint programID;
	GLuint textureID;
	GLuint elementbuffer;
	GLuint vertexbuffer;

	GLint modelMatrixUniformLocation;
	GLint viewMatrixUniformLocation;
	GLint projectionMatrixUniformLocation;
	GLint textureUniformLocation;
	GLint ambientMaterialColorLocation;
	GLint ambientLightColorLocation;
	GLint diffuseMaterialColorLocation;
	GLint diffuseLightColorLocation;
	GLint lightDirectionLocation;

	glm::mat4 modelMatrix;
	glm::mat4 translationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 MVP;

	glm::vec4 ambientLightColor;
	glm::vec4 ambientMaterialColor;
	glm::vec4 diffuseLightColor;
	glm::vec4 diffuseMaterialColor;

	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation;
	glm::vec3 scaling;
	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;
	glm::vec3 eyeVector;
	glm::vec3 cameraLook;
	glm::vec3 lightDirection;

	glm::vec2 mousePosition;

	std::vector<Mesh*> meshes;
	std::vector<GameObject*> GameObjectList;

	MeshCollection * teapotMesh = new MeshCollection();

	float lastTime = 0;
	float tickTime = 0;
	float deltaTime = 0;
	float roll;
	float pitch;
	float yaw;

	int verticesNum = 36;
	int indicesNum = 12;
	int IDNum = 8;
	int x;
	int y;
	int width;
	int height;
	int button;
	int state;

	unsigned int numberOfVertices = 0;
	unsigned int numberOfIndices = 0;

	bool isRunning = false;
	bool isFullscreen = false;
	bool isMousePressed = false;
};

