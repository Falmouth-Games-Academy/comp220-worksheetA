#include "Game.h"
#include <iostream>

Game::Game()
{

}

Game::~Game()
{

}

// Main game Initializer
void Game::init()
{
	initSDL();
	initWindow();
	initOpenGL();
	initGlew();
}

// initialises SDL
void Game::initSDL()
{
	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	//https://wiki.libsdl.org/SDL_Init
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Display an error message box
		//https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_GetError(), "SDL_Init failed", NULL);
	}
}

// initialises the SDL Window
void Game::initWindow()
{
	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	window = SDL_CreateWindow("Graphics Demo Aplication", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_GetError(), "SDL_CreateWindow failed", NULL);
		SDL_Quit();
	}
}

// function to toggle fullscreen On and Off
void Game::fullScreen()
{
	if (fullScreenToggle == false)
	{ 
		SDL_GetCurrentDisplayMode(0, &DM);
		auto Width = DM.w;
		auto Height = DM.h;

		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		glViewport(0, 0, DM.w, DM.h);

		fullScreenToggle = true;
	}
	else if (fullScreenToggle == true)
	{
		SDL_SetWindowFullscreen(window, 0);
		glViewport(0, 0, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);

		fullScreenToggle = false;
	}
}

// initialises OpenGL
void Game::initOpenGL()
{
	//requests 3.2 core OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	gl_Context = SDL_GL_CreateContext(window);
	if (gl_Context == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Create Context failed", SDL_GetError(), NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();
		//return 1;
	}

	glEnable(GL_DEPTH_TEST);
}

// initialises Glew
void Game::initGlew()
{
	//Init GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "GLEW Initialisation failed", (char*)glewGetErrorString(err), NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}

// The main Gameloop
void Game::gameLoop()
{
	init();
	time.Start();

	while (running)
	{
		mouseX = 0;
		mouseY = 0;

		//fps = 1 / time.GetDeltaTime;
		
		// prints FPS to the console
		//std::cout << "fps:" << fps << std::endl;		

		// Check for Input events
		CheckEvents();

		// Update calculations and gameobjects
		update();

		// Render function, does all the rendering code
		render();
		
	}

	gameCleanUp();
}

void Game::CheckEvents()
{
	SDL_Event ev;
	input.beginNewFrame();

	// Poll for the events which have happened in this frame
	while (SDL_PollEvent(&ev))
	{
		// Switch case for every message we are intereted in
		switch (ev.type)
		{
			// when SDL window is QUIT set running to false to end the gameloop
		case SDL_QUIT:
			running = false;
			break;

			// checks mouse movement
		case SDL_MOUSEMOTION:
			mouseX = ev.motion.xrel;
			mouseY = ev.motion.yrel;
			break;

			// KEYDOWN Message, called when a key has been pressed down
		case SDL_KEYDOWN:
			input.KeyDownEvent(ev);

			// Check the actual key code of the key that has been pressed
			switch (ev.key.keysym.sym)
			{
				//Escape key
			case SDLK_ESCAPE:
				running = false;
				break;

				// fullscreen toggle key
			case SDLK_f:
				fullScreen();
				break;
			}
			break;
		case SDL_KEYUP:
			input.KeyUpEvent(ev);
			break;
		}
	}
}

void Game::update()
{	
	time.Update();

	// Controls of camera movement
	controls.cameraControls(input, camera, time.GetDeltaTime());

	camera.MouseMovement(mouseX, mouseY);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	if (fullScreenToggle == false)
	{
		camera.Projection = glm::perspective(glm::radians(45.0f), globals::SCREEN_WIDTH / globals::SCREEN_HEIGHT, 0.2f, 1000.0f);
	}
	else
	{
		camera.Projection = glm::perspective(glm::radians(45.0f), (float)DM.w / (float)DM.h, 0.2f, 1000.0f);
	}

	// Or, for an ortho camera :
	//Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

}

void Game::render()
{
	startRender();
	endRender();
}

void Game::startRender()
{
	//render with OpenGL
	glClearColor(0.2, 0.2, 0.25, 1.0);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Game::endRender()
{
	// Screen Refresh
	SDL_GL_SwapWindow(window);
}

// CleanUp function, cleans up memory when the game loop is being closed/finished
void Game::gameCleanUp()
{
	auto iter = objs.begin();
	while (iter != objs.end())
	{
		if ((*iter))
		{
			delete (*iter);
			iter = objs.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	
	objs.clear();

	//glDeleteProgram(shaderManager.GetShader("defShader"));
	shaderManager.destroy();


	//Delete Context
	SDL_GL_DeleteContext(gl_Context);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();
}