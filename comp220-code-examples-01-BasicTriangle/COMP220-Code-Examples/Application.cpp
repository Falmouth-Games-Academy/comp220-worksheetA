#include "Application.h"

void FluidGL::Application::Init(const char* applicationName, int windowWidth, int windowHeight, bool fullscreen)
{
	renderer = new Renderer();

	renderer->Init(applicationName, windowWidth, windowHeight, fullscreen);
	renderer->LoadProgram("BasicShader");
}

void FluidGL::Application::Run()
{
	GameObject* gameObject = new GameObject();

	std::vector<GLfloat> vertices = {
	   -1, -1, 0,
	   0, -1, 0,
	   -1, 0, 0,
	   0, -1, 0,
	   1, -1, 0,
	   1, 0, 0
	};

	gameObject->Init(vertices, renderer->GetProgram("BasicShader"));

	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;

 	while (running)
	{
		//Poll for the events which have happened in this frame
		//https://wiki.libsdl.org/SDL_PollEvent
		while (SDL_PollEvent(&ev))
		{
			//Switch case for every message we are intereted in
			switch (ev.type)
			{
				//QUIT Message, usually called when the window has been closed
			case SDL_QUIT:
				running = false;
				break;
				//KEYDOWN Message, called when a key has been pressed down
			case SDL_KEYDOWN:
				//Check the actual key code of the key that has been pressed
				switch (ev.key.keysym.sym)
				{
					//Escape key
				case SDLK_ESCAPE:
					running = false;
					break;
				case SDLK_SPACE:
					renderer->SetFullscreen(!renderer->IsFullscreen());
					break;
				}
			}
		}

		renderer->ClearScreen(1, 0, 0, 1);
		gameObject->Render();
		renderer->SwapBuffers();
	}
}

void FluidGL::Application::Quit()
{
	delete renderer;
	GameObject::DeleteAll();
}
