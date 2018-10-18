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

	bool running = true;

	virtual void init();

	void initSDL();
	void initWindow();
	void initOpenGL();
	void initGlew();

	void initScene();
	void gameLoop();
	void gameCleanUp();


	SDL_Window* window;

	bool fullScreenToggle = false;
	void fullScreen();

	SDL_GLContext gl_Context;

	GLuint programID;
	GLuint location;

	// This will Identify out vertex buffer
	GLuint vertexbuffer;
	GLuint VertexArrayID;

	Camera camera;

	GLuint modelMatrixLocation;
	GLuint viewMatrixLocation;
	GLuint ProjectionMatrixLocation;


	glm::mat4 Projection;
	glm::mat4 modelMatrix;

private:



protected:

	virtual void update(float elapsedTime);
};