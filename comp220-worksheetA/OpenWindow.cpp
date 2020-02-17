#include "OpenWindow.h"

OGL::OpenWindow::OpenWindow(const char* title, int windowWidth, int windowHeight, SDL_WindowFlags flags)
{
#pragma region Window Setup

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, flags);

	//SDL_SetWindowResizable(window);
	SDL_GLContext mainContext = SDL_GL_CreateContext(window);

#pragma end region
	CheckSuccess();
}

OGL::OpenWindow::~OpenWindow()
{
	SDL_DestroyWindow(window);

		SDL_Quit();
}

bool OGL::OpenWindow::CheckSuccess()
{
	if (window == nullptr)
	{
		//Shows the error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);

		SDL_Quit();

		return false;
	}

	return true;
}
	 
	SDL_Window* OGL::OpenWindow::GetWindow()
	{
		return window;
	}