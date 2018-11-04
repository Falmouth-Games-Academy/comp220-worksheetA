#pragma once
#include<glew.h> // load the openGl exentsion Wrangler
#include <SDL_opengl.h>//load open Gl

#include "SDL_initialiser.h"

#include <string>
#include <vector>
#include <fstream>

class GlewInit
{
public:
	static void GlewInitialiser(SDL_Window ** window);
};
