#include "OpenGLWindow.h"

ByGL::OpenGLWindow::OpenGLWindow(const char* title, int windowWidth, int windowHeight, SDL_bool fullscreen)
{
#pragma region Window Setup
	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	///<summary>
	///SLD Window to be rendered to.
	///</summary>
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	SDL_SetWindowResizable(window, fullscreen);
	
#pragma endregion
	if (!SetOpenGlAttributes())
		CleanUp();
	SDL_GLContext mainContext = SDL_GL_CreateContext(window);
}

ByGL::OpenGLWindow::~OpenGLWindow()
{
	CleanUp();
}

bool ByGL::OpenGLWindow::CheckSuccess()
{
	// If 
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "failed", SDL_GetError(), NULL);
		//Close the SDL Library
		//https://wiki.libsdl.org/SDL_Quit
		return false;
	}
	//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Success", SDL_GetError(), NULL);
	return true;
}

SDL_Window* ByGL::OpenGLWindow::GetWindow()
{
	return window;
}

void ByGL::OpenGLWindow::CleanUp()
{
	std::cout << "am Called" << std::endl;
	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);
}

bool ByGL::OpenGLWindow::SetOpenGlAttributes()
{
#pragma region GL Attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
#pragma endregion
	return true;
}