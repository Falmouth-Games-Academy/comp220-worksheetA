#include "Game.h"
#include "Variables.h"

Game::Game()
{
}

Game::~Game()
{
}

int Game::InitialiseSDL()
{
	// initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success \n";

		// Create a window
		mainWindow = SDL_CreateWindow(
			variables::title,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			variables::SCREEN_WIDTH,
			variables::SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
		);

		// if window succesful..
		if (mainWindow != 0) {
			std::cout << "Window creation success \n";

		}
		else {
			std::cout << "window failed \n";
			return false;
		}

	}
	else {
		std::cout << "SDL fail \n";
		return false;
	}

	isRunning = true;
	std::cout << "SDL init success \n";

	return 0;
}

int Game::InitialiseGLEW()
{
	// Initialising GLEW
	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "GLEW Initialisation Failed", (char*)glewGetErrorString(error), NULL);
	}

	return 0;
}

bool Game::SetOpenGLAttributes()
{
	// Request 3.2 Core OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Set our OpenGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	return true;
}

void Game::SetFullscreen()
{
	// Turns on/off fullscreen
	if (!isFullscreen)
	{
		SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		glViewport(0, 0, variables::FULLSCREEN_WIDTH, variables::FULLSCREEN_HEIGHT);
		isFullscreen = true;
	}
	else if (isFullscreen)
	{
		SDL_SetWindowFullscreen(mainWindow, 0);
		glViewport(0, 0, variables::SCREEN_WIDTH, variables::SCREEN_HEIGHT);
		isFullscreen = false;
	}
}

int Game::Initialise()
{
	// Initialising random seed
	std::srand(time(NULL));

	// Initialising IMG library
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	//Initalise the SDL components
	if (InitialiseSDL() < 0)
	{
		std::cout << "SDL initalisation failed." << std::endl;
		return 1;
	}

	Game::SetOpenGLAttributes();

	// Initialise GLEW
	gl_Context = SDL_GL_CreateContext(mainWindow);
	if (gl_Context == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateContext Failed", SDL_GetError(), NULL);
		return 1;
	}
	Game::InitialiseGLEW();

	// Enabling OpenGL Depth function
	glEnable(GL_DEPTH_TEST);

	// Enabling Culling Face
	glEnable(GL_CULL_FACE);

	// Mouse setup
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	skybox = new Skybox();

	return 0;
}

int Game::Loop()
{
	//Current sdl event
	SDL_Event event;

	/*------------------------
	Main game loop
	------------------------*/
	while (isRunning)
	{
		//Calculate deltaTime
		lastTime = tickTime;
		tickTime = SDL_GetTicks();
		deltaTime = (tickTime - lastTime);

		//Check for SDL events
		if (SDL_PollEvent(&event))
		{
			//Events found
			switch (event.type)
			{
				//Window closed
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_MOUSEMOTION:
				player.MouseMovement(event.motion.xrel, event.motion.yrel);
				break;
				
			case SDL_KEYDOWN:

				player.KeyboardEvents(event);


				//Check individual keys by code (can be moved out into main switch statement if fewer keys need to be checked.)
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						isRunning = false;
						break;

					case SDLK_F11: // Toggle fullscreen
						SetFullscreen();
						break;
						
				}
				break;
				
			case SDL_KEYUP:
				player.KeyboardEvents(event);
				break;
			}
		}
		player.ProcessInputs(deltaTime);
		Game::Render();
	}

	Game::Clean();
	return 0;
}

void Game::LoadingScene()
{
	// Mesh
	loadMeshesFromFile("Models/utah-teapot.fbx", teapotMesh);

	// Textures
	diffuseTextureID = loadTextureFromFile("Textures/Tank1DF.png");
	specularTextureID = loadTextureFromFile("Textures/specMap.png");

	// Shader
	texturedShader->Load("blinnPhongVert.glsl", "blinnPhongFrag.glsl");

	// Game Object
	teapotGO->SetPosition(-2.0f, -8.0f, -50.0f);
	teapotGO->SetMesh(teapotMesh);
	teapotGO->SetShader(texturedShader);
	teapotGO->SetDiffuseTexture(diffuseTextureID);

	teapotGO1->SetPosition(-10.0f, -20.0f, -50.0f);
	teapotGO1->SetRotation(0.0f, 0.0f, 90.0f);
	teapotGO1->SetScale(0.5f, 0.5f, 0.5f);
	teapotGO1->SetMesh(teapotMesh);
	teapotGO1->SetShader(texturedShader);
	teapotGO1->SetDiffuseTexture(diffuseTextureID);

	GameObjectList.push_back(teapotGO);
	GameObjectList.push_back(teapotGO1);

	// Set up vectors for our camera position
	cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
	cameraLook = glm::vec3(0.0f, 0.0f, -10.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// Ambient
	ambientLightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	ambientMaterialColor = glm::vec4(0.1f, 0.0f, 0.0f, 1.0f);

	// Diffuse
	diffuseLightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	diffuseMaterialColor = glm::vec4(0.8f, 0.0f, 0.0f, 1.0f);

	// Specular
	specularMaterialColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	specularLightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	specularMaterialPower = 25.0f;

	// Light
	lightDirection = glm::vec3(0.0f, 0.0f, -1.0f);
}

void Game::Render()
{
	for (GameObject* obj : GameObjectList)
	{
		obj->Update(deltaTime);
	}

	//glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Calculate the view matrix and projection matrix
	viewMatrix = player.camera.GetViewMatrix();
	projectionMatrix = glm::perspective(
		glm::radians(45.0f),
		(float)800 / (float)640,
		0.1f,
		1000.0f
	);

	// Draw skybox
	skybox->RenderSkybox(viewMatrix, projectionMatrix);

	for (GameObject* obj : GameObjectList)
	{
		// Getting shaders
		Shader* currentShader = obj->GetShader();
		currentShader->Use();

		// Binding textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, obj->GetDiffuseTexture());

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularTextureID);

		// Send uniforms across
		// Model, view and projection locations
		glUniformMatrix4fv(currentShader->GetUniform("modelMatrix"), 1, GL_FALSE, glm::value_ptr(obj->GetModelTransformation()));
		glUniformMatrix4fv(currentShader->GetUniform("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(currentShader->GetUniform("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		// Texture locations
		glUniform1i(currentShader->GetUniform("diffuseTexture"), 0);
		glUniform1i(currentShader->GetUniform("specularTexture"), 1);

		// Ambient location
		glUniform4fv(currentShader->GetUniform("ambientMaterialColor"), 1, glm::value_ptr(ambientMaterialColor));
		glUniform4fv(currentShader->GetUniform("ambientLightColor"), 1, glm::value_ptr(ambientLightColor));

		// Diffuse location
		glUniform4fv(currentShader->GetUniform("diffuseMaterialColor"), 1, glm::value_ptr(diffuseMaterialColor));
		glUniform4fv(currentShader->GetUniform("diffuseLightColor"), 1, glm::value_ptr(diffuseLightColor));

		// Specular location
		glUniform4fv(currentShader->GetUniform("specularMaterialColor"), 1, glm::value_ptr(specularMaterialColor));
		glUniform4fv(currentShader->GetUniform("specularLightColor"), 1, glm::value_ptr(specularLightColor));

		// Specular power location
		glUniform1f(currentShader->GetUniform("specularMaterialPower"), specularMaterialPower);

		// Light and camera locations
		glUniform3fv(currentShader->GetUniform("lightDirection"), 1, glm::value_ptr(lightDirection));
		glUniform3fv(currentShader->GetUniform("cameraPosition"), 1, glm::value_ptr(cameraPosition));

		obj->Render();
	}

	SDL_GL_SwapWindow(mainWindow);
}

void Game::Clean()
{
	// Cleanup
	std::cout << "Cleaning SDL \n";

	// Cleaning with iter gives an error after closing an application
	/*auto iter = GameObjectList.begin();
	while (iter != GameObjectList.end())
	{
		if ((*iter))
		{
			delete (*iter);
			iter = GameObjectList.erase(iter);
		}
		else
		{
			iter++;
		}
	}*/
	GameObjectList.clear();

	delete skybox;

	glDeleteTextures(1, &diffuseTextureID);
	glDeleteTextures(1, &specularTextureID);

	player.ClearEvents();

	SDL_GL_DeleteContext(gl_Context);
	SDL_DestroyWindow(mainWindow);
	IMG_Quit();
	SDL_Quit();
}
