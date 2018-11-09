#include "Game.h"




Game::Game()
{

}


Game::~Game()
{
}

int Game::init(int WindowWidth, int WindowHeight)
{
	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	//https://wiki.libsdl.org/SDL_Init
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Display an error message box
		//https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return 1;
	}

	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);
		//Close the SDL Library
		//https://wiki.libsdl.org/SDL_Quit
		SDL_Quit();
		return 1;
	}

	//Request 3.2 Core OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	gl_Context = SDL_GL_CreateContext(window);
	if (gl_Context == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateContext Failed", SDL_GetError(), NULL);

		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	//init GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "GLEW Initialisation Failed", (char*)glewGetErrorString(err), NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	tea = new Actor();
	

	//Initialize SDL
	if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
	{
		printf("SDL No Joystick! SDL Error: %s\n", SDL_GetError());
		gGameController = SDL_JoystickOpen(0);
		if (gGameController == NULL)
		{
			printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			JOYSTICK = true;
		}
		
	}
	return 0;
}

void Game::update(double deltaTime)
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
			case SDLK_a:
				gameCamera->position.x -= 1.0f;
				break;
			case SDLK_d:
				gameCamera->position.x += 1.0f;
				break;
			case SDLK_w:
				gameCamera->position.z += 1.0f;
				break;
			case SDLK_s:
				gameCamera->position.z -= 1.0f;
				break;
			case SDLK_q:
				gameCamera->rotation.z += 1.0f;
				break;
			case SDLK_e:
				gameCamera->rotation.z -= 1.0f;
				break;
			}
		}
		if (JOYSTICK)
		{
			if (ev.jaxis.axis == 0)
			{
				//Left of dead zone
				if (ev.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{
					gameCamera->position.x += -1;
				}
				//Right of dead zone
				else if (ev.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					gameCamera->position.x += 1;
				}
				//Y axis motion
				else if (ev.jaxis.axis == 1)
				{
					//Below of dead zone
					if (ev.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						gameCamera->position.z += -1;
					}
					//Above of dead zone
					else if (ev.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						gameCamera->position.x += 1;
					}
				}
			}
		}
		else
		{
			if (ev.type == SDL_MOUSEMOTION)
			{
				MouseControls.x = ev.motion.xrel * MouseSpeed / deltaTime;
				MouseControls.y = ev.motion.yrel * MouseSpeed / deltaTime;
				gameCamera->rotation.x = gameCamera->rotation.x + MouseControls.x;
				gameCamera->rotation.y = gameCamera->rotation.y + MouseControls.y;
				//std::cout << "Mouse = (" << MouseControls.x << ", " << MouseControls.y << ")" << std::endl;
			}
		}
		
	}
	std::cout << "CamPos = (" << gameCamera->position.x << ", " << gameCamera->position.y << ", " << gameCamera->position.z << ")" << std::endl;
	std::cout << "CamRot = (" << gameCamera->rotation.x << ", " << gameCamera->rotation.y << ", " << gameCamera->rotation.z << ")" << std::endl;
}

void Game::render()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Do rendering here!

	tea->render(gameCamera);
	SDL_GL_SwapWindow(window);
}

void Game::exit()
{
	if (JOYSTICK)
	{
		SDL_JoystickClose(gGameController);
	}
	//Delete Context
	SDL_GL_DeleteContext(gl_Context);
	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();
}
