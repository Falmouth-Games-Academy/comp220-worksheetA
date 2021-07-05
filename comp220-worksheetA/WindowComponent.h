#pragma once
#include "SDL.h"
#include "ComponentType.h"

struct WindowComponent
{
	ComponentType id;
	const char* title;						// Window title
	int x, y, windowWidth, windowHeight;	// Screen space transform & dimensions
	bool fullscreen;						// Toggle fullscreen
	SDL_Window* window;						// SDL window pointer
	SDL_GLContext glContext;				// OpenGL context

	void Init(const char* _title, int _x, int _y, int _width, int _height, bool _fullscreen)
	{
		title = _title;
		x = _x;
		y = _y;
		windowWidth = _width;
		windowHeight = _height;
		fullscreen = _fullscreen;
	}
	void SetWindow(SDL_Window* _window)
	{
		window = _window;
	}
	void SetGLContext(SDL_GLContext context)
	{
		glContext = context;
	}
};