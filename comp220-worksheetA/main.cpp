#include <iostream>
#include <chrono> // Get time
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h> // Needs to go after glew include
#include <glm/glm.hpp> // Old header file standard (.hpp)

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Vertex.h"
#include "OpenGLWindow.h"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

SDL_Window * window;
OpenGLWindow * windowConstructor;

void Cleanup()
{
	// Delete the window pointer
	if (window)
	{
		window = nullptr;
		delete(window);
	}

	// Delete the window constructor pointer
	if (windowConstructor)
	{
		windowConstructor = nullptr;
		delete(windowConstructor);
	}
}

int main(int argc, char ** argsv)
{
	// Create the OpenGLWindow
	windowConstructor = new OpenGLWindow;
	int success = windowConstructor->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	// If the window hasn't been created, exit the program
	if (!success)
	{
		Cleanup();
		return -1;
	}

	// Fetch the SDL window and save it for later
	window = windowConstructor->getWindow();

	bool fullScreen = false;
	
	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;
	while (running)
	{

		//Poll for the events which have happened in this frame
		//https://wiki.libsdl.org/SDL_PollEvent
		while (SDL_PollEvent(&ev))
		{
			//Switch case for every message we are intereted in
			switch (ev.type)
			{
				//QUIT Message, usually called when the window has been closed
			case SDL_QUIT:
				running = false;
				break;
				//KEYDOWN Message, called when a key has been pressed down
			case SDL_KEYDOWN:
				//Check the actual key code of the key that has been pressed
				switch (ev.key.keysym.sym)
				{
					//Escape key
				case SDLK_ESCAPE:
					running = false;
					break;
					// Toggle fullscreen mode
				case SDLK_F11:
					fullScreen = !fullScreen;
					windowConstructor->fullScreen(fullScreen);
					break;
				}
			}
		}
	}

	Cleanup();

	return 0;
}
