#pragma once
#include <SDL.h>
#include "Globals.h"
#include <GL\glew.h>
#include <SDL_opengl.h>

class Window
{
public:
	Window();
	~Window();

	SDL_Window *window;

private:
	void createWindow();
};