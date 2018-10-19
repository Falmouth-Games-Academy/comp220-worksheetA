#include "Game.h"

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
	initScene();
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
		//return 1;
	}
}

// initialises the SDL Window
void Game::initWindow()
{
	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	window = SDL_CreateWindow("Triangle Simulator - Press F to toggle fullscreen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_GetError(), "SDL_CreateWindow failed", NULL);
		//Close the SDL Library
		//https://wiki.libsdl.org/SDL_Quit
		SDL_Quit();
		//return 1;
	}
}

// function to toggle fullscreen On and Off
void Game::fullScreen()
{
	if (fullScreenToggle == false)
	{ 
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		glViewport(0, 0, globals::FULL_SCREEN_WIDTH, globals::FULL_SCREEN_HEIGHT);
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
		//return 1;
	}
}

// initialises the game scene and elements to be rendered
void Game::initScene()
{
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An Array of 3 vectors which represets 3 vertices and RGBA values for each vertex
	static const Vertex triangleVertices[] = {
		{ -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f }
	};

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// the following command will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex), triangleVertices, GL_STATIC_DRAW);

	// 1st attribute buffer: Vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)0
	);

	// 2nd attribute buffer: Colours
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(3 * sizeof(float))
	);
	
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 90.0f, 0.0f);
	float rot = 0.1f;

	modelMatrix = glm::translate(position);

	// loads in the shaders
	programID = LoadShaders("vert.glsl", "frag.glsl");
	glUseProgram(programID);
	location = glGetUniformLocation(programID, "color");
	modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");
	viewMatrixLocation = glGetUniformLocation(programID, "viewMatrix");
	ProjectionMatrixLocation = glGetUniformLocation(programID, "projectionMatrix");
}

// The main Gameloop
void Game::gameLoop()
{
	init();

	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;

	glm::vec3 movementVec = glm::vec3(0.0f);

	while (running)
	{
		//Poll for the events which have happened in this frame\\
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
				case SDLK_d:
					//camera.Xstrafe(0.1f);
					movementVec.x = 0.02f;
					break;
				case SDLK_a:
					movementVec.x = -0.02f;
					break;
				case SDLK_SPACE:
					movementVec.y = 0.02f;
					break;
				case SDLK_LSHIFT:
					movementVec.y = -0.02f;
					break;
				case SDLK_w:
					movementVec.z = -0.02f;
					break;
				case SDLK_s:
					movementVec.z = 0.02f;
					break;
				case SDLK_f:
					fullScreen();
					break;
				}
			}
		}
		camera.Strafe(movementVec, 1.0f);
		movementVec = glm::vec3(0.0f);

		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		if (fullScreenToggle == false)
		{
			Projection = glm::perspective(glm::radians(45.0f), globals::SCREEN_WIDTH / globals::SCREEN_HEIGHT, 0.1f, 100.0f);
		}
		else
		{
			Projection = glm::perspective(glm::radians(45.0f), globals::FULL_SCREEN_WIDTH / globals::FULL_SCREEN_HEIGHT, 0.1f, 100.0f);
		}

		// Or, for an ortho camera :
		//Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

		//glm::mat4 modelMatrix = glm::rotate(2.0f, rotation += rot);

		/* ------------------------------ /
			RENDERING PROCESS IN LOOP
		/ ------------------------------ */

		//Update Game and draw with OpenGL
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClearDepth(0.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);
		//Uniform3f(location, 1, 2, 3);

		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera.GetTheMatrix()));
		glUniformMatrix4fv(ProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(Projection));


		// 1st attribute buffer: vertices
		
		//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBindVertexArray(VertexArrayID);

		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from Vertex 0: 3 vertices total -> 1 triangle
		

		// Screen Refresh
		SDL_GL_SwapWindow(window);
	}

	gameCleanUp();
}

// CleanUp function, cleans up memory when the game loop is being closed/finished
void Game::gameCleanUp()
{

	glDeleteProgram(programID);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);

	//Delete Context
	SDL_GL_DeleteContext(gl_Context);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();
}
