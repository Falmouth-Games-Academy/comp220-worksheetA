#include "Game.h"
#include "Variables.h"

Game::Game()
{
}

Game::~Game()
{
}

int Game::loop()
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
		Game::render();
	}

	Game::clean();
	return 0;
}

int Game::initialiseSDL()
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

int Game::initialiseGLEW()
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

int Game::initialise()
{
	// Initialising random seed
	std::srand(time(NULL));

	// Initialising IMG library
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	//Initalise the SDL components
	if (initialiseSDL() < 0)
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
	Game::initialiseGLEW();

	// Enabling OpenGL Depth function
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);

	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	return 0;
}

int Game::getShaders()
{
	// Mouse setup
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//Load Mesh
	
	loadMeshesFromFile("Models/utah-teapot.fbx", teapotMesh);

	textureID = loadTextureFromFile("Textures/Tank1DF.png");

	//Shader * texturedShader = new Shader();
	//texturedShader->Load("blinnPhongVert.glsl", "blinnPhongFrag.glsl");

	programID = LoadShaders("blinnPhongVert.glsl", "blinnPhongFrag.glsl");

	/*GameObject * tankGO = new GameObject();
	tankGO->SetPosition(0.0f, 0.0f, 0.0f);
	tankGO->SetMesh(tank);
	tankGO->SetShader(texturedShader);*/
	//tankGO->SetDiffuseTexture(textureID);

	//GameObjectList.push_back(tankGO);

	//Calculate our perspective matrix
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)800 / (float)640, 0.1f, 100.0f);

	// Ambient
	ambientLightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	ambientMaterialColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

	// Diffuse
	diffuseLightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	diffuseMaterialColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);

	lightDirection = glm::vec3(0.0f, 0.0f, -1.0f);

	// Get the uniforms from the shader
	modelMatrixUniformLocation = glGetUniformLocation(programID, "modelMatrix");
	viewMatrixUniformLocation = glGetUniformLocation(programID, "viewMatrix");
	projectionMatrixUniformLocation = glGetUniformLocation(programID, "projectionMatrix");

	textureUniformLocation = glGetUniformLocation(programID, "textureSampler");

	ambientMaterialColorLocation = glGetUniformLocation(programID, "ambientMaterialColor");
	ambientLightColorLocation = glGetUniformLocation(programID, "ambientLightColor");

	diffuseMaterialColorLocation = glGetUniformLocation(programID, "diffuseMaterialColor");
	diffuseLightColorLocation = glGetUniformLocation(programID, "diffuseLightColor");

	lightDirectionLocation = glGetUniformLocation(programID, "lightDirection");


	return 0;
}

void Game::render()
{
	//combine the above matrices into the model matrix (order is important!!!! - TRS)
	//modelMatrix = translationMatrix * rotationMatrix*scaleMatrix;
	//glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	modelMatrix = glm::translate(position);

	viewMatrix = glm::lookAt(camera.GetCameraPosition(), camera.GetCameraPosition() + camera.GetCameraFront(), camera.GetCameraUp());

	//for (GameObject * obj : GameObjectList) {

	//	Shader * currentShader = obj->GetShader();
	//	currentShader->Use();

	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, textureID);

	//	glUniformMatrix4fv(currentShader->GetUniform("modelMatrix"), 1, GL_FALSE, glm::value_ptr(obj->GetModelTransformation()));
	//	glUniformMatrix4fv(currentShader->GetUniform("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	//	glUniformMatrix4fv(currentShader->GetUniform("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	//	//glUniform1f(currentShader->GetUniform("morphBlendAlpha"), morphBlendAlpha);
	//	glUniform1i(currentShader->GetUniform("diffuseTexture"), 0);


	//	obj->Render();
	//}

	//send the uniforms across
	glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glUniform1i(textureUniformLocation, 0);

	glUniform4fv(ambientMaterialColorLocation, 1, glm::value_ptr(ambientMaterialColor));
	glUniform4fv(ambientLightColorLocation, 1, glm::value_ptr(ambientLightColor));
	glUniform3fv(lightDirectionLocation, 1, glm::value_ptr(lightDirection));

	glUniform4fv(diffuseMaterialColorLocation, 1, glm::value_ptr(diffuseMaterialColor));
	glUniform4fv(diffuseLightColorLocation, 1, glm::value_ptr(diffuseLightColor));

	teapotMesh->render();
	SDL_GL_SwapWindow(mainWindow);
}

void Game::clean()
{
	// Cleanup
	std::cout << "Cleaning SDL \n";
	if (teapotMesh)
	{
		delete teapotMesh;
		teapotMesh = nullptr;
	}
	glDeleteTextures(1, &textureID);
	glDeleteProgram(programID);
	// GameObjectList.clear();
	meshes.clear();
	player.ClearEvents();
	SDL_GL_DeleteContext(gl_Context);
	SDL_DestroyWindow(mainWindow);
	IMG_Quit();
	SDL_Quit();
}
