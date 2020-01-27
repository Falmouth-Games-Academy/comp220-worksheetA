#include "OpenGLWindow.h"

ByGL::OpenGLWindow::OpenGLWindow(const char* title, int windowWidth, int windowHeight, SDL_WindowFlags flags, SDL_bool fullscreen)
{
#pragma region Window Setup
	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	///<summary>
	///SLD Window to be rendered to.
	///</summary>
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, flags);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	SDL_SetWindowResizable(window, fullscreen);
	SDL_GLContext mainContext = SDL_GL_CreateContext(window);
#pragma endregion
	CheckSuccess();
}

ByGL::OpenGLWindow::~OpenGLWindow()
{
	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();
}

bool ByGL::OpenGLWindow::CheckSuccess()
{
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);
		//Close the SDL Library
		//https://wiki.libsdl.org/SDL_Quit
		SDL_Quit();
		return false;
	}
	return true;
}

SDL_Window* ByGL::OpenGLWindow::GetWindow()
{
	return window;
}
