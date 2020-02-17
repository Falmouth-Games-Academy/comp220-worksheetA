#include "Application.h"

ByGL::Application::Application()
{

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
	// Initialize the main window and check its success.
	glWindow.push_back(NewWindow("New Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_TRUE, SDL_WINDOW_OPENGL));
	if (glWindow.at(0) == nullptr)
		return Quit();
#pragma endregion
	return 1;
	running = true;
}

ByGL::OpenGLWindow* ByGL::Application::NewWindow(const char* title, int x, int y, int windowWidth, int windowHeight, SDL_bool fullscreen, SDL_WindowFlags flags)
{
	OpenGLWindow* newWindow = new OpenGLWindow(title, x, y, windowWidth, windowHeight, fullscreen, flags);
	if (newWindow != nullptr)
	{
		if (!newWindow->CheckSuccess())
		{
			// Should the window fail, quit the application
			delete newWindow;
		}
		return newWindow;
	}
	return nullptr;
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
		// Physics Update

		// Events loop
		Events();
		// Object Update

		// Update Screen
		glClearColor(0.0, 1.0, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int i = 0; i < glWindow.size(); i++)
			SDL_GL_SwapWindow(glWindow.at(i)->GetWindow());
	}
	for (int i = 0; i < glWindow.size(); i++)
		delete glWindow.at(i);
	glWindow.clear();
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
	running = false;
	SDL_Quit();
	return 0;
}
