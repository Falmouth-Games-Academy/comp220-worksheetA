#include "OpenGLWindow.h";


int OpenGLWindow::createWindow(unsigned int sizeX, unsigned int sizeY)
{
	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	//https://wiki.libsdl.org/SDL_Init
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Display an error message box
		//https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return -1;
	}

	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);
		//Close the SDL Library
		//https://wiki.libsdl.org/SDL_Quit
		SDL_Quit();
		return -1;
	}

	// Request 3.2 Core OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GLContext gl_Context = SDL_GL_CreateContext(window);
	if (gl_Context == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreatedContext Failed", SDL_GetError(), NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return -1;
	}

	// Init GLEW
	glewExperimental = GL_TRUE;
	// Make sure GLEW is being initalised correctly
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		// Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", (char*)glewGetErrorString(err), NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return -1;
	}

	return 1;
}

SDL_Window * OpenGLWindow::getWindow()
{
	return window;
}


void OpenGLWindow::fullScreen(bool enable)
{
	if (enable)
	{
		SDL_SetWindowFullscreen(window, 0);
	}
	else
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
}

void OpenGLWindow::removeWindow()
{

}

