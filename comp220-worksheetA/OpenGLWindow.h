#pragma once
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>

namespace ByGL
{
	class OpenGLWindow
	{
	public:
		OpenGLWindow(const char* title, int windowWidth, int windowHeight, SDL_WindowFlags flags, SDL_bool fullscreen);
		~OpenGLWindow();
		bool CheckSuccess();
		SDL_Window* GetWindow();
	private:
		SDL_Window* window;
	protected:
	};
}
