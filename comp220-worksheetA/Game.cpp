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
		SDL_Quit();
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

// initialises the game scene and elements to be rendered
void Game::initScene()
{

	/* ----------- OLD CUBE ----------------
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const Vertex cubeVertexArray[] = 
	{
		{ -0.5f,-0.5f,0.0f,  1.0f,0.0f,1.0f,1.0f },
		{ 0.5f,-0.5f,0.0f,  0.0f,1.0f,1.0f,1.0f },
		{ 0.5f,0.5f,0.0f,  1.0f,1.0f,0.0f,1.0f },
		{ -0.5f,0.5f,0.0f,  1.0f,1.0f,1.0f,1.0f },

		{ -0.5f,-0.5f,-1.0f,  1.0f,0.0f,0.0f,1.0f },
		{ 0.5f,-0.5f,-1.0f,  1.0f,1.0f,0.0f,1.0f },
		{ 0.5f,0.5f,-1.0f,  0.0f,0.0f,1.0f,1.0f },
		{ -0.5f,0.5f,-1.0f,  0.0f,1.0f,0.0f,1.0f }
	};
	
	// Indicies must be set in anti-clockwise if on the outside of the cube order due to back-face culling
	static const int cubeIndiciesArray[] =
	{
		0,1,2, // Represenative of one triangle
		2,3,0,

		6,5,4,
		4,7,6,

		7,3,2,
		2,6,7,

		6,2,1,
		1,5,6,

		3,7,4,
		4,0,3,

		1,0,5,
		5,0,4
	};
	

	// Culls the clockwise facing side of the triangle
	//glEnable(GL_CULL_FACE);

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, (8 * sizeof(Vertex)), cubeVertexArray, GL_STATIC_DRAW);

	GLuint elementbuffer;
	// Generate 1 buffer, put the resulting identifier in elementbuffer
	glGenBuffers(1, &elementbuffer);
	// The following commands will talk about our 'elementbuffer' buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	// Give our elements to OpenGL.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (36 * sizeof(int)), cubeIndiciesArray, GL_STATIC_DRAW);
	  ----------- END OF OLD CUBE ----------------*/

	//------------------ Start of model loading----------------------------//

	//MeshCollection * tankMes=loadMeshFromFile("Tank.fbx");
	//GameObject* go=new GameObject;
	//go->attachMesh(tankMesh);

	//GameObject* go2 =new GameObject
	//go->attachMesh(tankMesh);

	//Mesh

	//Load Mesh
	dinoModel = new MeshCollection();
	loadMeshFromFile("tomModel.FBX", dinoModel);
	TextureID = loadTextureFromFile("tomTexture.png");

	teaPotModel = new MeshCollection();
	loadMeshFromFile("teaPotModel.FBX", teaPotModel);

	// Culls the clockwise facing side of the triangles
	glEnable(GL_CULL_FACE);

	// loads in the shaders
	//programID = LoadShaders("vert.glsl", "frag.glsl");
	shaderManager.LoadShaders("defShader", "vert.glsl", "frag.glsl");

	//------------------end of model loading----------------------------//

	//modelMatrix = glm::translate(position);

	// ModelMatrix setup
	//modelMatrixLocation = glGetUniformLocation(shaderManager.GetShader("defShader"), "modelMatrix");
	//viewMatrixLocation = glGetUniformLocation(shaderManager.GetShader("defShader"), "viewMatrix");
	//ProjectionMatrixLocation = glGetUniformLocation(shaderManager.GetShader("defShader"), "projMatrix");

	//Get the uniforms from the shader
	modelMatrixUniformLocation = glGetUniformLocation(shaderManager.GetShader("defShader"), "modelMatrix");
	viewMatrixUniformLocation = glGetUniformLocation(shaderManager.GetShader("defShader"), "viewMatrix");
	projectionMatrixUniformLocation = glGetUniformLocation(shaderManager.GetShader("defShader"), "projMatrix");
	//baseTextureLocation = glGetUniformLocation(shaderManager.GetShader("defShader"), "baseTexture");

	SDL_SetRelativeMouseMode(SDL_TRUE);
}

// The main Gameloop
void Game::gameLoop()
{
	init();

	GameObject* dinoGO1 = new GameObject;
	dinoGO1->attachMesh(teaPotModel);

	GameObject* dinoGO2 = new GameObject;
	dinoGO2->attachMesh(dinoModel);

	GameObject* dinoGO3 = new GameObject;
	dinoGO3->attachMesh(teaPotModel);

	GameObject* dinoGO4 = new GameObject;
	dinoGO4->attachMesh(dinoModel);

	std::vector<GameObject *> objs;
	objs.push_back(dinoGO1);
	objs.push_back(dinoGO2);
	objs.push_back(dinoGO3);
	objs.push_back(dinoGO4);

	while (running)
	{
		lastTime = tickTime;
		tickTime = static_cast<float>(SDL_GetTicks()) / 1000;
		deltaTime = (tickTime - lastTime);

		fps = 1 / deltaTime;

		float deltaCamSpeed = cameraMovSpeed * deltaTime;

		mouseX = 0;
		mouseY = 0;
		
		// prints FPS to the console
		//std::cout << "fps:" << fps << std::endl;

		input.beginNewFrame();
		// Poll for the events which have happened in this frame
		while (SDL_PollEvent(&ev))
		{
			// Switch case for every message we are intereted in
			switch (ev.type)
			{
				// QUIT Message, usually called when the window has been closed
			case SDL_QUIT:
				running = false;
				break;

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

		cameraMovementVec.x = 0.0f;
		cameraMovementVec.y = 0.0f;
		cameraMovementVec.z = 0.0f;
		if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true || input.isKeyHeld(SDL_SCANCODE_A) == true)
		{
			cameraMovementVec.z -= deltaCamSpeed;
		}

		if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true || input.isKeyHeld(SDL_SCANCODE_D) == true)
		{
			cameraMovementVec.z += deltaCamSpeed;
		}

		if (input.isKeyHeld(SDL_SCANCODE_UP) == true || input.isKeyHeld(SDL_SCANCODE_W) == true)
		{
			cameraMovementVec.x += deltaCamSpeed;
		}

		if (input.isKeyHeld(SDL_SCANCODE_DOWN) == true || input.isKeyHeld(SDL_SCANCODE_S) == true)
		{
			cameraMovementVec.x -= deltaCamSpeed;
		}

		if (input.isKeyHeld(SDL_SCANCODE_LCTRL) == true)
		{
			cameraMovementVec.y -= deltaCamSpeed;
		}

		if (input.isKeyHeld(SDL_SCANCODE_SPACE) == true)
		{
			cameraMovementVec.y += deltaCamSpeed;
		}

		camera.Strafe(cameraMovementVec, 1.0f);

		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		if (fullScreenToggle == false)
		{
			camera.Projection = glm::perspective(glm::radians(45.0f), globals::SCREEN_WIDTH / globals::SCREEN_HEIGHT, 0.1f, 100.0f);
		}
		else
		{
			camera.Projection = glm::perspective(glm::radians(45.0f), globals::FULL_SCREEN_WIDTH / globals::FULL_SCREEN_HEIGHT, 0.1f, 100.0f);
		}

		// Or, for an ortho camera :
		//Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

		/* ------------------------------ /
			RENDERING PROCESS IN LOOP
		/ ------------------------------ */
		//Update Game and draw with OpenGL
		glClearColor(0.2, 0.2, 0.25, 1.0);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

		//sceneMatrix = glm::rotate( -0.95f , glm::vec3(1, 0, 0));
		sceneMatrix = glm::rotate(cubeRotateSpeed * tickTime, rotation) * sceneMatrix;

		glUseProgram(shaderManager.GetShader("defShader"));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureID);


		//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(sceneMatrix));
		//glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
		//glUniformMatrix4fv(ProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera.Projection));


		//send the uniforms across
		glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
		glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(camera.Projection));
		//glUniform1i(baseTextureLocation, 0);
		

		int count = 0;
		for (GameObject * obj : objs)
		{
			
			glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(obj->modelMatrix));
			
			//obj->rotation.z = 0.8;
			obj->scale = glm::vec3(0.1f);
			obj->position = glm::vec3(0, 0, count);
			count += 3;
			obj->update();
		}

		//for (GameObject * obj : displayList)
		//{
		// 		glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(obj->modelMatrix));
		//		obj->update();
		//}
		// Draw the Cube
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

		camera.MouseMovement(mouseX, mouseY);

		// Screen Refresh
		SDL_GL_SwapWindow(window);
	}

	gameCleanUp();
}

// CleanUp function, cleans up memory when the game loop is being closed/finished
void Game::gameCleanUp()
{

	glDeleteProgram(shaderManager.GetShader("defShader"));
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