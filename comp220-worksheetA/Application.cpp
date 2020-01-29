#include "Application.h"

ByGL::Application::Application()
{
	glWindow = nullptr;
}

ByGL::Application::~Application()
{
}

int ByGL::Application::Init()
{
#pragma region SDL Setup
	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	//https://wiki.libsdl.org/SDL_Init
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		//Display an error message box
		//https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return Quit();
	}
#pragma endregion

#pragma region Window Setup
	// Initialize a window and check its success
	glWindow = new OpenGLWindow("New Game", 1280, 720, SDL_TRUE);
	if (!glWindow->CheckSuccess())
	{
		// Should the window fail, quit the application
		delete glWindow;
		return Quit();
	}
#pragma endregion

#pragma region GLEW Setup
	glewExperimental = GL_TRUE;
	glewInit();
#pragma endregion
	return 1;
	running = true;
}


int ByGL::Application::Run()
{
	// Initialize
	if (!Init())
	{
		return Quit();
	}
	
	while (running)
	{
		// Run Events
		Events();
		// Update World
		// Update Screen
		glClearColor(0.0, 1.0, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SDL_GL_SwapWindow(glWindow->GetWindow());
	}
	delete glWindow;
	return Quit();
}

void ByGL::Application::Events()
{
	// Resolve Events
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
			}
		}
	}
}

int ByGL::Application::Quit()
{
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();
	return 0;
}
