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
#include "shader.h"
#include "camera.h"
#include "Vertex.h"



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

	SDL_GLContext gl_Context;

	GLuint programID;
	GLuint location;

	// This will Identify out vertex buffer
	GLuint vertexbuffer;
	GLuint VertexArrayID;

	// Camera to view the screen
	Camera camera;

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
	GLuint modelMatrixLocation;
	GLuint viewMatrixLocation;
	GLuint ProjectionMatrixLocation;

	glm::mat4 Projection;
	glm::mat4 modelMatrix;


protected:

	//virtual void update(float elapsedTime);
};