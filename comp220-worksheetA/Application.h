#pragma once
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <list>
#include <vector>
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
		std::vector<OpenGLWindow*> glWindow;
		OpenGLWindow* NewWindow(const char* title, int x, int y, int windowWidth, int windowHeight, SDL_bool fullscreen, SDL_WindowFlags flags);
		SDL_Event ev;
		bool running;

	protected:

	};
}