#include "Base.h"

#include "Renderer.h"
#include "GameObject.h"
#include "GLUtils.h"
#include "Components.h"
#include "Time.h"
#include <filesystem>
#include <cstdint>
#include <filesystem>

namespace FluidGL
{
	namespace fs = std::filesystem;

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