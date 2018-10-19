#pragma once

#include <iostream>
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

class GameClass
{
private:

public:
	GameClass();
	~GameClass();

	SDL_Window* window = nullptr;
	SDL_GLContext gl_Context = nullptr;

	GLuint VertexArrayID;
	GLuint vertexbuffer;

	bool running = true;

	int init(int WindowWidth = 800, int WindowHeight = 560);
	void update();
	void render();
	void cleanup(bool WithError, std::string ErrorTitle = "", std::string ErrorMessage = "");

};

