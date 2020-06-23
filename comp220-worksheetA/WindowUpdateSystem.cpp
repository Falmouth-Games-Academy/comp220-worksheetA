#include "WindowUpdateSystem.h"

WindowUpdateSystem::WindowUpdateSystem()
{

}

WindowUpdateSystem::~WindowUpdateSystem()
{

}

void WindowUpdateSystem::StartRender()
{
	//glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 1.0, 0.5, 0.0);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowUpdateSystem::UpdateWindow(Coordinator* coord)
{
	for (Entity ent : sy_Entities)
	{
		SDL_Window* wind = coord->GetComponent<WindowComponent>(ent).window;
		SDL_GL_SwapWindow(wind);
	}
}

void WindowUpdateSystem::EndRender()
{
	glDisable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glClearColor(0.0, 1.0, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

SDL_Window* WindowUpdateSystem::CreateWindow(Coordinator* man, Entity ent)
{
	WindowComponent windowComp = man->GetComponent<WindowComponent>(ent);
	SDL_Window* window = SDL_CreateWindow(windowComp.title, windowComp.x, windowComp.y, windowComp.windowWidth, windowComp.windowHeight, SDL_WINDOW_OPENGL);
	SDL_SetWindowResizable(window, SDL_bool(windowComp.fullscreen));
	windowComp.SetGLContext(SDL_GL_CreateContext(window));
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();

	if (glewError != GLEW_OK)
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unable to init glew", (char*)glewGetErrorString(glewError), NULL);

	std::cout << "Window Created" << std::endl;
	return window;
}
