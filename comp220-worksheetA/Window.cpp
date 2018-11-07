#include "Window.h"

Window::Window()
{
	createWindow();
}

Window::~Window()
{
	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);
}

void Window::createWindow()
{
	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	window = SDL_CreateWindow("Triangle Simulator - Press F to toggle fullscreen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_GetError(), "SDL_CreateWindow failed", NULL);
		SDL_Quit();
	}
}
