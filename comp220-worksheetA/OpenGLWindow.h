#pragma once
#include <SDL.h>
#include <GL\glew.h>

class OpenGLWindow {

public:
	~OpenGLWindow();
	bool CreateWindow(unsigned int sizeX, unsigned int sizeY);
	void FullScreen(bool enable);
	SDL_Window * GetWindow();
	void RemoveWindow();

	int Width() 
	{
		return width;
	};
	int Height()
	{
		return height;
	};

private:
	SDL_Window * window;
	SDL_GLContext gl_Context;

	int width;
	int height;
protected:
};