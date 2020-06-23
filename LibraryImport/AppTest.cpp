#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <list>
#include <vector>
#include <Application.h>
#include <OpenGLWindow.h>

int main()
{
	ByGL::Application app;
	app.Init();
	app.Run();

	return 0;
}