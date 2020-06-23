#pragma once
#include "System.h"
#include "Coordinator.h"
#include "WindowComponent.h"
#include <SDL.h>
#include <GL/glew.h>


class WindowUpdateSystem : public System
{
public:
	WindowUpdateSystem();
	~WindowUpdateSystem();
	void StartRender();
	
	void UpdateWindow(Coordinator* coord);

	void EndRender();
	SDL_Window* CreateWindow(Coordinator* man, Entity ent);
private:
	// Have a window component reference
protected:

};