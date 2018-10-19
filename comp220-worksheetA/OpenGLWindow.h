#pragma once

#include <iostream>
#include <chrono> // Get time
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h> // Needs to go after glew include
#include <glm/glm.hpp> // Old header file standard (.hpp)

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Vertex.h"

class OpenGLWindow {

public:
	int createWindow(unsigned int sizeX, unsigned int sizeY);
	void fullScreen(bool enable);
	SDL_Window * getWindow();
	~OpenGLWindow();

private:
	SDL_Window * window;
	SDL_GLContext gl_Context;
protected:
};
