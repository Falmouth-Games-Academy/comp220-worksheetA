#pragma once
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>

namespace OGL
{
	class OpenWindow
	{
	public:
		OpenWindow(const char* title, int windowWidth, int windowHeight, SDL_WindowFlags flags);
		~OpenWindow();
		bool CheckSuccess();
		SDL_Window* GetWindow();

	private:
		SDL_Window * window;

	protected:

	};
}