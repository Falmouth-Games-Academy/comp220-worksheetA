#pragma once
#include "render.h";

class OpenGLWindow {

public:
	int createWindow(unsigned int sizeX, unsigned int sizeY);
	void fullScreen(bool enable);
	SDL_Window * getWindow();
	void removeWindow();

private:
	SDL_Window * window;
protected:
};