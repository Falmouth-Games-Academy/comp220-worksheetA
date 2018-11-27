#pragma once
#include <SDL.h>
#include <GL\glew.h>

class OpenGLWindow {

public:
	~OpenGLWindow();
	bool createWindow(unsigned int sizeX, unsigned int sizeY);
	void fullScreen(bool enable);
	SDL_Window * getWindow();
	void removeWindow();

private:
	SDL_Window * window;
	SDL_GLContext gl_Context;
protected:
};