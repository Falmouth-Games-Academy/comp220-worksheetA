#include "SDL_initialiser.h"

int SDLInitialiser() {


	//let's initialise the SDL library
	if (SDL_Init(SDL_INIT_VIDEO) < 0)// < this part call the video library of SDL at initialisation
	{

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Sdl init failed", SDL_GetError(), NULL); //this will show an error message box if there is an
																								//error with initialisation, remember to add this message boxes
		//quit the application																						
		return 1;
	}

	return 0;
}