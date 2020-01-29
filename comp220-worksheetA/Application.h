#pragma once
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include "OpenGLWindow.h"

namespace ByGL
{
	class Application
	{
	public:
		Application();
		~Application();
		int Init();
		int Run();

	private:
		void Events();
		int Quit();
		OpenGLWindow* glWindow;
		SDL_Event ev;
		bool running;

	protected:

	};
}