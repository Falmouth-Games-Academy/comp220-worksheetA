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
#include "Timer.h"
#include "Controls.h"

class Game
{
public:

	Game();
	virtual ~Game();

	// main functions to get the game running
	virtual void init();
	void gameLoop();
	void gameCleanUp();
	void CheckEvents();
	virtual void update();
	virtual void render();
	void startRender();
	void endRender();
	
	SDL_Window* window;

	Input input;

	Timer time;

	SDL_GLContext gl_Context;
	
	GLuint location;

	std::vector<GameObject *> objs;
	GameObject gameObject;

	ShaderManager shaderManager;

	Controls controls;

	// Camera to view the screen
	Camera camera;

	// mouse x and y vars
	int mouseX = 0;
	int mouseY = 0;

private:

	SDL_DisplayMode DM;

	// the different initialises
	void initSDL();
	void initWindow();
	void initOpenGL();
	void initGlew();

	float fps;

	// fullscreen toggle boolean and function
	bool fullScreenToggle = false;
	void fullScreen();

	// Gameloop running boolean
	bool running = true;


protected:

};