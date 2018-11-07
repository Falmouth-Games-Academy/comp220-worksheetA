#pragma once
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Globals.h"
#include "Graphics.h"
#include "GameObject.h"
#include "shader.h"
#include "camera.h"
#include "Vertex.h"
#include "Input.h"






class Game
{
public:

	Game();
	virtual ~Game();

	// main functions to get the game running
	virtual void init();
	void gameLoop();
	void gameCleanUp();
	
	SDL_Window* window;

	Input input;

	SDL_GLContext gl_Context;
	
	GLuint location;

	GameObject gameObject;

	ShaderManager shaderManager;

	// This will Identify out vertex buffer
	GLuint vertexbuffer;
	GLuint VertexArrayID;

	// element buffer
	GLuint elementbuffer;

	// Camera to view the screen
	Camera camera;

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 1.0f);
	float cubeRotateSpeed = 0.5f;

	float lastTime;
	float tickTime;
	float deltaTime;
	float fps;

	float cameraMovSpeed = 2.5f;
	glm::vec3 cameraMovementVec = glm::vec3(0.0f);

	
	MeshCollection * model;
	GLuint TextureID;

private:

	// the different initialises
	void initSDL();
	void initWindow();
	void initOpenGL();
	void initGlew();
	void initScene();

	// fullscreen toggle boolean and function
	bool fullScreenToggle = false;
	void fullScreen();

	// Gameloop running boolean
	bool running = true;

	// secene matrix locations
	GLuint modelMatrixUniformLocation;
	GLuint viewMatrixUniformLocation;
	GLuint projectionMatrixUniformLocation;
	GLint baseTextureLocation;

	glm::mat4 sceneMatrix;

	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;


protected:

	//virtual void update(float elapsedTime);
};