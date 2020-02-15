#include <iostream>
#include <vector>
#include <array>

#include <sstream>
#include <fstream>

#include "Renderer.h"
#include "GameObject.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace FluidGL
{
	class Application
	{
	public:
		Application() {};
		~Application() {};

		// Initialize all required parameters
		void Init(const char* applicationName, int windowWidth, int windowHeight, bool fullscreen);

		// Main loop
		void Run();

		// Cleanup
		void Quit();
	private:
		Renderer* renderer;
	};
}