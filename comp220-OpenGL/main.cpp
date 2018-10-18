#include <iostream>
#include <SDL.h>
#include "main.h"

int main(int argc, char ** argsv)
{
	//Starting the SDL Library, using SDL_INIT_VIDEO to only run the video parts
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//If SDL failed to initialize, this error will show
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return 1;
	}

	//Creating the window, have to remember to quit the window at the end to return the pointer by destroying it(the best way)
	SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
	if (window == nullptr)
	{
		//Show error if SDL didnt create the window
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);

		SDL_Quit(); //quit SDL
		return 1;
	}

	//Requesting 3.2 Core OpenGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GLContext gl_Context = SDL_GL_CreateContext(window);
	if (gl_Context == nullptr) //if the glew context has a null value, show error and then destroy window
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Create_Context failed, check to make sure the context is assigned correctly!", SDL_GetError(), NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;

	}

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) //if Glew is not okay, show error and close window
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Glew start-up failed, check to make sure Glew is started properly!", (char*)glewGetErrorString(err), NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	//Running is always true as long as Escape is not pressed 
	bool running = true;
	//SDL Event structure initiation
	SDL_Event ev;
	while (running)
	{
		//Poll for the events
		while (SDL_PollEvent(&ev))
		{
			//Switch case for event type
			switch (ev.type)
			{
				//If the case is SDL_QUIT then running will be false
			case SDL_QUIT:
				running = false;
				break;
				//Checks the keydown inputs
			case SDL_KEYDOWN:
				//Checks which button has been pressed
				switch (ev.key.keysym.sym)
				{
					//In case of ESC being pressed, the program will close
				case SDLK_ESCAPE:
					running = false;
					break;
			
				}
			}
		}

		//Rendering goes here, noice
		glClearColor(1.0, 1.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
		SDL_SetWindowResizable(window, SDL_TRUE);
	}

	//Deleting the context
	SDL_GL_DeleteContext(gl_Context);
	//Clean up, deactivating the library and the window
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

