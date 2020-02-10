#pragma once
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>

namespace ByGL
{
	class OpenGLWindow
	{
	public:
		OpenGLWindow(const char* title, int x, int y, int windowWidth, int windowHeight, SDL_bool fullscreen, SDL_WindowFlags flags);
		~OpenGLWindow();
		bool CheckSuccess();
		SDL_Window* GetWindow();
		void CleanUp();
	private:
		SDL_Window* window;
		bool SetOpenGlAttributes();
	protected:
	};
}
