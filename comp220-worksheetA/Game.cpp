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
				
			case SDL_KEYDOWN:

				//Check individual keys by code (can be moved out into main switch statement if fewer keys need to be checked.)
				switch (event.key.keysym.sym)
				{
					case SDLK_w:
						key = "w";
						Game::KeyPressed(key);
						break;
					case SDLK_s:
						key = "s";
						Game::KeyPressed(key);
						break;
					case SDLK_a:
						key = "a";
						Game::KeyPressed(key);
						break;
					case SDLK_d:
						key = "d";
						Game::KeyPressed(key);
						break;
					/*
					case SDLK_ESCAPE: // Escape key
						isRunning = false;
						break;

					case SDLK_w: // Arrow key up
						position.y += 0.05f;
						break;

					case SDLK_s: // Arrow key down
						position.y -= 0.05f;
						break;

					case SDLK_d: // Arrow key right
						position.x -= 0.05f;
						break;

					case SDLK_a: // Arrow key left
						position.x += 0.05f;
						break;

					case SDLK_KP_4: // Rotate left
						rotation.y -= 0.1f;
						break;

					case SDLK_KP_6: // Rotate right
						rotation.y += 0.1f;
						break;

					case SDLK_KP_8: // Rotate up
						rotation.x -= 0.1f;
						break;

					case SDLK_KP_2: // Rotate down
						rotation.x += 0.1f;
						break;

					case SDLK_F11: // Toggle fullscreen
						SetFullscreen();
						break;
						*/
				}
				break;
				
			}
			/*
			if (event.type == SDL_MOUSEWHEEL) // Doesn't work right now
			{
				if (event.wheel.y > 0) // Scroll up
				{
					// Scale up the triangle
					scaling = glm::vec3(1.05f, 1.05f, 1.05f);
					std::cout << "mouse wheel up" << std::endl;
				}

				if (event.wheel.y < 0) // Scroll down
				{
					// Scale down the triangle
					scaling = glm::vec3(0.95f, 0.95f, 0.95f);
					std::cout << "mouse wheel down" << std::endl;
				}
			}
			
			modelMatrix = glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // Rotates the cube in X axis
			modelMatrix *= glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotates the cube in Y axis 
			modelMatrix *= glm::translate(position); // Translates the position of the cube
			*/
		}
		
		Game::MoveMouse(x, y, width, height);
		Game::MousePressed(button, state, x, y);

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

	return 0;
}

int Game::getVertex()
{
	// Generate vertex array SHOULD BE DELETED
	// glGenVertexArrays(1, &VertexArrayID);
	// glBindVertexArray(VertexArrayID);
	/*
	// An array of 3 vectors which represents 3 vertices
	static const Vertex v[] = {
		{ -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },

		{ -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f }, // Front square

		{ 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },

		{ 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f }, // Back square

		{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },

		{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, .0f, 1.0f }, // Right square

		{ -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },

		{ -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f }, // Left square

		{ -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f },

		{ -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f }, // Upper square

		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f },

		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f }, // Bottom square
	};
	*/

	/*
	static const Vertex CubeID[] = 
	{
		// Upper vertices

		// 0 -> front-top-left
		{-0.5f, 0.5f, 0.5f, // x, y, z
		0.0f, 0.0f, 1.0f, 1.0f, // r, g, b, a
		0.0f, 1.0f},  // tu, tv

		// 1 -> back-top-left
		{-0.5f, 0.5f, -0.5f, // x, y, z
		0.0f, 1.0f, 0.0f, 1.0f, // r, g, b, a
		0.0f, 1.0f},  // tu, tv

		// 2 -> back-top-right
		{0.5f, 0.5f, -0.5f, // x, y, z
		1.0f, 0.0f, 0.0f, 1.0f, // r, g, b, a
		1.0f, 1.0f},  // tu, tv

		// 3 -> front-top-right
		{0.5f, 0.5f, 0.5f, // x, y, z
		0.0f, 1.0f, 0.0f, 1.0f, // r, g, b, a
		1.0f, 1.0f}, // tu, tv


		// Bottom vertices

		// 4 -> front-bottom-left
		{-0.5f, -0.5f, 0.5f, // x, y, z
		0.0f, 0.0f, 1.0f, 1.0f, // r, g, b, a
		0.0f, 0.0f}, // tu, tv

		// 5 -> back-bottom-left
		{-0.5f, -0.5f, -0.5f, // x, y, z
		0.0f, 1.0f, 0.0f, 1.0f, // r, g, b, a
		0.0f, 0.0f}, // tu, tv

		// 6 -> back-bottom-right
		{0.5f, -0.5f, -0.5f, // x, y, z
		1.0f, 0.0f, 0.0f, 1.0f, // r, g, b, a
		1.0f, 0.0f}, // tu, tv

		// 7 ->  front-bottom-right
		{0.5f, -0.5f, 0.5f, // x, y, z
		0.0f, 1.0f, 0.0f, 1.0f, // r, g, b, a
		1.0f, 0.0f} // tu, tv
	};
	
	static const int indices[] = 
	{
		
		// Top square
		0, 2, 1,
		0, 3, 2,

		// Bottom square
		4, 5, 6,
		4, 6, 7,
		
		// Left square
		4, 0, 1,
		4, 1, 5,

		// Right square
		6, 3, 7,
		6, 2, 3,

		// Back square
		5, 1, 2,
		5, 2, 6,
		
		// Front square
		0, 4, 7,
		0, 7, 3
	};
	*/
	/* SHOULD BE DELETED
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	// glBufferData(GL_ARRAY_BUFFER, IDNum * sizeof(Vertex), CubeID, GL_STATIC_DRAW);
	
	glGenBuffers(1, &elementbuffer);
	// Bind element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, verticesNum * sizeof(int), indices, GL_STATIC_DRAW);
	*/
	/* MODEL SECTION */

	// Pass in buffers to load a model
	// loadModelFromFile("Models/Tank1.FBX", vertexbuffer, elementbuffer, numberOfVertices, numberOfIndices);

	return 0;
}

int Game::loading()
{
	/* SHOULD BE DELETED
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,					// attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,					// size
		GL_FLOAT,			// type
		GL_FALSE,			// normalized?
		sizeof(Vertex),		// stride -> sizeof(Vertex)
		(void*)0			// array buffer offset
	);
	*/
	// Uses colours from the Vertex.h
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(3 * sizeof(float))
	);

	// Load textures
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(7 * sizeof(float))
	);
	return 0;
}

int Game::getShaders()
{
	loadMeshesFromFile("Models/Tank1.FBX", meshes);

	// Create a texture ID
	textureID = loadTextureFromFile("Textures/Tank1DF.png");

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("vertexTextured.glsl", "fragmentTextured.glsl");

	/*
	// Set up positions for position, rotation and scale
	position = glm::vec3(0.0f, 0.0f, -20.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scaling = glm::vec3(1.0f, 1.0f, 1.0f);

	// Calculate the translation, rotation and scale matrices using the above vectores
	translationMatrix = glm::translate(position);
	rotationMatrix = glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	scaleMatrix = glm::scale(scaling);

	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	// Set up vectors for our camera position
	cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// Calculate the view matrix
	viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
	// Calculate our perspective matrix
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)800 / (float)640, 0.1f, 100.0f);
	*/
	// Get the uniforms from the shader
	modelMatrixUniformLocation = glGetUniformLocation(programID, "modelMatrix");
	viewMatrixUniformLocation = glGetUniformLocation(programID, "viewMatrix");
	projectionMatrixUniformLocation = glGetUniformLocation(programID, "projectionMatrix");
	textureUniformLocation = glGetUniformLocation(programID, "textureSampler");

	return 0;
}

void Game::UpdateView()
{
	glm::mat4 matRoll = glm::mat4(1.0f);
	glm::mat4 matPitch = glm::mat4(1.0f);
	glm::mat4 matYaw = glm::mat4(1.0f);

	matRoll = glm::rotate(matRoll, roll, glm::vec3(0.0f, 0.0f, 1.0f));
	matPitch = glm::rotate(matPitch, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	matYaw = glm::rotate(matYaw, yaw, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 rotate = matRoll * matPitch * matYaw;

	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, -eyeVector);

	viewMatrix = rotate * translate;

}

void Game::KeyPressed(const char key)
{
	float dx = 0; // how much we strafe on x
	float dz = 0; // how much we strafe on z
	switch (key)
	{
	case 'w':
	{
		dz = 2;
		break;
	}
	case 's':
	{
		dz = -2;
		break;
	}
	case 'a':
	{
		dx = -2;
		break;
	}
	case 'd':
	{
		dx = 2;
		break;
	}
	default:
		break;
	}

	glm::mat4 mat = GetViewMatrix();

	glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
	glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

	const float speed = 0.12f; // how fast we move

	eyeVector += (-dz * forward + dx * strafe) * speed;

	UpdateView();
}

void Game::MoveMouse(int x, int y, int width, int height)
{
	if (isMousePressed == false)
	{
		return;
	}

	glm::vec2 mouseDelta = glm::vec2(x, y) - mousePosition;

	const float mouseXSensitivity = 0.25f;
	const float mouseYSensitivity = 0.25f;

	yaw += mouseXSensitivity * mouseDelta.x;
	pitch += mouseYSensitivity * mouseDelta.y;

	mousePosition = glm::vec2(x, y);
	UpdateView();
}

void Game::MousePressed(int button, int state, int x, int y)
{
	if (state == SDL_KEYUP)
	{
		isMousePressed = false;
	}
	if (state == SDL_KEYDOWN)
	{
		isMousePressed = true;
		mousePosition.x = x;
		mousePosition.y = y;
	}
}

void Game::render()
{
	// Update Game and Draw with OpenGL
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT

	glUseProgram(programID);

	// Activating and binding texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Binding vertex and element buffers SHOULD BE DELETED 
	// glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	glBindVertexArray(VertexArrayID);

	loading();

	// If we want another texture do the following
	// glActiveTexture(GL_TEXTURE1);
	// glBindTexture(GL_TEXTURE_2D, anotherTextureID);

	// Send the uniforms across
	glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	//glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniform1i(textureUniformLocation, 0);

	for (Mesh* currentMesh : meshes)
	{
		currentMesh->Render();
	}

	// Draw the triangle ! SHOULD BE DELETED
	// glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, (void*) 0); // draw elements instead of vertices
	glDisableVertexAttribArray(0);

	SDL_GL_SwapWindow(mainWindow);
}

void Game::clean()
{
	// Cleanup
	std::cout << "Cleaning SDL \n";
	// glDeleteBuffers(1, &vertexbuffer);
	// glDeleteBuffers(1, &elementbuffer);
	// glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteTextures(1, &textureID);
	glDeleteProgram(programID);
	auto iter = meshes.begin();
	while (iter != meshes.end())
	{
		if ((*iter))
		{
			(*iter)->Destroy();
			delete (*iter);
			iter = meshes.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	meshes.clear();
	// Delete Context
	SDL_GL_DeleteContext(gl_Context);
	SDL_DestroyWindow(mainWindow);
	IMG_Quit();
	SDL_Quit();
}
