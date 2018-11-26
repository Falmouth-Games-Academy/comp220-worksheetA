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

// initialises the game scene and elements to be rendered
void Game::initScene()
{
	//Load Mesh
	dinoModel = new MeshCollection();
	loadMeshFromFile("TomModel.FBX", dinoModel);

	teaPotModel = new MeshCollection();
	loadMeshFromFile("teaPotModel.FBX", teaPotModel);

	BunnyModel = new MeshCollection();
	loadMeshFromFile("stanfordBunny.FBX", BunnyModel);

	GroundModel = new MeshCollection();
	loadMeshFromFile("Ground.FBX", GroundModel);

	TankModel = new MeshCollection();
	loadMeshFromFile("Tank1.FBX", TankModel);

	// Culls the clockwise facing side of the triangles
	glEnable(GL_CULL_FACE);


	// loads in the shaders
	shaderManager.LoadShaders("defShader", "vert.glsl", "frag.glsl");
	shaderManager.GetShader("defShader")->IsLit = true;

	shaderManager.LoadShaders("texturedShader", "texturedVert.glsl", "texturedFrag.glsl");

	SDL_SetRelativeMouseMode(SDL_TRUE);
}

// The main Gameloop
void Game::gameLoop()
{
	init();

	GameObject* GO1 = new GameObject;
	GO1->SetMesh(teaPotModel);
	GO1->setShader("defShader");
	GO1->SetScale(0.2f, 0.2f, 0.2f);

	GameObject* GO2 = new GameObject;
	GO2->SetMesh(dinoModel);
	GO2->SetDiffuseTexture("tomTexture.png");
	GO2->setShader("texturedShader");
	GO2->SetRotation(0.0f, 0.0f, 3.14f);

	GameObject* GO3 = new GameObject;
	GO3->SetMesh(TankModel);
	GO3->SetDiffuseTexture("Tank1DF.png");
	GO3->setShader("texturedShader");
	//GO3->SetScale(0.2f, 0.2f, 0.2f);

	GameObject* GO4 = new GameObject;
	GO4->SetMesh(BunnyModel);
	GO4->setShader("defShader");
	GO4->SetScale(0.012f, 0.012f, 0.012f);

	GameObject* GO5 = new GameObject;
	GO5->SetMesh(GroundModel);
	GO5->setShader("defShader");

	objs.push_back(GO5);
	objs.push_back(GO4);
	objs.push_back(GO2);
	objs.push_back(GO1);
	objs.push_back(GO3);


	int count = 0;
	for (GameObject * obj : objs)
	{
		objs[1]->SetPosition(0.0f, 3.0f, 0);
		objs[2]->SetPosition(0.0f, 0.0f, 5);
		objs[3]->SetPosition(0.0f, 0.0f, 14);
		objs[4]->SetPosition(0.0f, 0.0f, -7);
	}

	while (running)
	{
		mouseX = 0;
		mouseY = 0;

		// time calculations
		lastTime = tickTime;
		tickTime = static_cast<float>(SDL_GetTicks()) / 1000;
		deltaTime = (tickTime - lastTime);

		fps = 1 / deltaTime;
		
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
}

void Game::update()
{
	// Controls of camera movement
	controls.cameraControls(input, camera, deltaTime);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	if (fullScreenToggle == false)
	{
		camera.Projection = glm::perspective(glm::radians(45.0f), globals::SCREEN_WIDTH / globals::SCREEN_HEIGHT, 0.1f, 100.0f);
	}
	else
	{
		camera.Projection = glm::perspective(glm::radians(45.0f), (float)DM.w / (float)DM.h, 0.1f, 100.0f);
	}

	// Or, for an ortho camera :
	//Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	objs[1]->SetRotation(0.0f, (0.3f * tickTime), 0.0f);
	//objs[2]->SetRotation(0.0f, (0.3f * tickTime), (0.3f * tickTime));

	// Go through each object and update them
	for (GameObject * obj : objs)
	{
		obj->Update(deltaTime);
	}

	camera.MouseMovement(mouseX, mouseY);
}

void Game::render()
{
	//render with OpenGL
	glClearColor(0.2, 0.2, 0.25, 1.0);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (GameObject * obj : objs)
	{
		Shader * currentShader = shaderManager.GetShader(obj->getShader());

		glUseProgram(currentShader->getProgramID());



		// send the uniforms across
		glUniformMatrix4fv(currentShader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(obj->GetModelTransformation()));
		glUniformMatrix4fv(currentShader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
		glUniformMatrix4fv(currentShader->getUniformLocation("projMatrix"), 1, GL_FALSE, glm::value_ptr(camera.Projection));
		glUniform3fv(currentShader->getUniformLocation("cameraPosition"), 1, glm::value_ptr(camera.pos));
		glUniform4fv(currentShader->getUniformLocation("ambientLightColour"), 1, glm::value_ptr(ambientLightColour));
		glUniform4fv(currentShader->getUniformLocation("diffuseLightColour"), 1, glm::value_ptr(diffuseLightColour));
		glUniform4fv(currentShader->getUniformLocation("specularLightColour"), 1, glm::value_ptr(specularLightColour));
		GLint ambientLocation = currentShader->getUniformLocation("ambientMaterialColour");
		glUniform4fv(currentShader->getUniformLocation("ambientMaterialColour"), 1, glm::value_ptr(ambientMaterialColour));
		glUniform4fv(currentShader->getUniformLocation("diffuseMaterialColour"), 1, glm::value_ptr(diffuseMaterialColour));
		glUniform4fv(currentShader->getUniformLocation("specularMaterialColour"), 1, glm::value_ptr(specularMaterialColour));
		glUniform1f(currentShader->getUniformLocation("specularMaterialPower"), specularMaterialPower);

		glUniform3fv(currentShader->getUniformLocation("lightDirection"), 1, glm::value_ptr(lightDirection));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, obj->GetDiffuseTexture());

		obj->Render();
	}

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