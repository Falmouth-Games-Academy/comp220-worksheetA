#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include "OpenGLWindow.h"
#include "Application.h"

using namespace ByGL;

int main(int argc, char ** argsv)
{
	
	Application app;

	app.Run();

	return 0;
	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	
	//SDL Event structure, this will be checked in the while loop
}