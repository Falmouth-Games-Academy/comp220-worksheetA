
#include "Window_Spawner.h"

void WindowInit::WindowSpawner(SDL_Window **	window) {
	//this function creates and stores a pointer to a Window. It takes a Title, a position of the window, the dimensions and the flags of how it's displayed
	*window = SDL_CreateWindow("SDL2 Alessio's Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	//check if the window is created, remeber to always check if everything has been created
	if (window == nullptr)	//if the window exist, it would be stored in memory, check if the window exist in memory
	{
		//show a message 
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window has failed", SDL_GetError(), NULL);

		//Close the library 
		SDL_Quit();
		//Close the application
	}
	return;
}