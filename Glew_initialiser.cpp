//** GLEW initialisation **//
#include "Glew_Initialiser.h"

void GlewInit::GlewInitialiser(SDL_Window **window) {


	//once GLEW is inistialised, we are going to create a contex mask, this will allow us to just use the functions of a version and to deprecate the old ones
	//we request 3.2 core at the moment
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//this is required by open GL to render. It creates a contenxt where OpenGL can draw, and we are going to pass our window
	SDL_GLContext gl_Context = SDL_GL_CreateContext(*window);

	//check if the openGl renderer has been created 
	if (gl_Context == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Create context has failed", SDL_GetError(), NULL);
		//if the error happens, close the program
		SDL_DestroyWindow(*window);
		SDL_Quit();
	}

	//initialise GLEW
	glewExperimental = GL_TRUE; //this command allows us to use the newer versions of Glew. also, when using GL booleans remeber to use "GL_"

	//cache the initialisation
	GLenum err = glewInit();

	if (err != GLEW_OK) //check if the glew libray is been activated 
	{
		//show error, rememeber to cast glewGetErrorString to a char because Glenum is not compatible dirrectly
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Glew failed to initialise", (char*)glewGetErrorString(err), NULL);
		//if the error happens, close the program
		SDL_DestroyWindow(*window);
		SDL_Quit();
	}
}