#pragma once

#include "Libraries.h"

class Game
{
public:
	Game();
	~Game();

	int loop();
	int initialiseSDL();
	int initialiseGLEW();
	int initialise();
	int getVertex();
	int getShaders();
	int loading();

	void render();
	void clean();
	void SetFullscreen();

	bool SetOpenGLAttributes();

private:
	SDL_Window* mainWindow = nullptr;

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

	glm::mat4 modelMatrix;
	glm::mat4 translationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scaling;
	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;

	// Initialise times
	float lastTime = 0;
	float tickTime = 0;
	float deltaTime = 0;

	int verticesNum = 36;
	int indicesNum = 12;
	int IDNum = 8;

	bool isRunning = false;
	bool isFullscreen = false;
};

