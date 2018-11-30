#include "Game.h"

/* TODO:
	REFACTOR SKYBOX CODE AND DELETE MEMORY ON CLOSE
	Object Creation Class
	use renderDoc for debugging very important for the coursework
	work off my feedback
	joystick controls
	create light with a base attached to camera with offset
	throwable light
	shadow casting from light
	
	consider orbiting planets/ moons
	check out factory patterns for gameobject*/

Game::Game()
{
}


Game::~Game()
{
}

void Game::initialiseGame()
{
	bool inDevelopMode = false;

	// Initalise random seed
	std::srand(time(NULL));

	// Initialise times
	float lastTime = 0.0f;
	float tickTime = 0.0f;
	float deltaTime = 0.0f;

	// Initalise the SDL components
	mainWindow = init.initaliseSDLWindow();
	renderer = init.initaliseSDLRenderer();

	// Initalise OpenGL 
	init.SetOpenGLAttributes();
	gl_Context = init.initialiseContext(mainWindow);
	init.initaliseGlew(mainWindow);
}

void Game::gameLoop()
{
	initialiseGame();

	// Mouse setup
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	// create shaders
	texturedShader = new Shader();
	texturedShader->Load("blinnPhongVert.glsl", "blinnPhongFrag.glsl");

	lightOrbShader = new Shader();
	lightOrbShader->Load("vertTextured.glsl", "fragTextured.glsl");

	skyboxShader = new Shader();
	skyboxShader->Load("vertSkybox.glsl", "fragSkybox.glsl");

	/*particleShader = new Shader();
	particleShader->Load("vertParticle.glsl", "fragParticle.glsl");

	// load particle texture
	particleTextureID = loadTextureFromFile("Model/spark.png");

	Particles = new ParticleGenerator(particleShader , particleTextureID, 10);
	*/

	// Materials for lighting
	glm::vec4 ambientMaterialColour = glm::vec4(0.0f, 0.0f, 0.01f, 1.0f);
	glm::vec4 diffuseMaterialColour = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	glm::vec4 specularMaterialColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float specularMaterialPower = 50.0f;
	// camera
	glm::vec3 cameraPosition = player.camera.getCameraPos();
	// Light
	glm::vec4 ambientLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 diffuseLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 specularLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightDirection = glm::vec3(0.0f, 0.0f, -1.0f);

	// get locations for lighting
	GLint ambientMaterialColourLocation = glGetUniformLocation(texturedShader->GetShaderProgramID(), "ambientMaterialColour");
	GLint diffuseMaterialColourLocation = glGetUniformLocation(texturedShader->GetShaderProgramID(), "diffuseMaterialColour");
	GLint specularMaterialColourLocation = glGetUniformLocation(texturedShader->GetShaderProgramID(), "specularMaterialColour");

	GLint ambientLightColourLocation = glGetUniformLocation(texturedShader->GetShaderProgramID(), "ambientLightColour");
	GLint diffuseLightColourLocation = glGetUniformLocation(texturedShader->GetShaderProgramID(), "diffuseLightColour");
	GLint specularLightColourLocation = glGetUniformLocation(texturedShader->GetShaderProgramID(), "specularLightColour");

	GLint lightDirectionLocation = glGetUniformLocation(texturedShader->GetShaderProgramID(), "lightDirection");
	GLint specularMaterialPowerLocation = glGetUniformLocation(texturedShader->GetShaderProgramID(), "specularMaterialPower");

	GLint cameraPositionLocation = glGetUniformLocation(texturedShader->GetShaderProgramID(), "cameraPosition");

	// skybox vertices
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	// generate array and buffer for the skybox

	GLuint skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);


	// generate planets
	createObject("Model/egypt.fbx", "Model/colour.png", 0.0f, 40.0f, -300.0f, vec3(0.1f, 0.1f, 0.1f), vec3(0.0f, 1.0f, 0.0f), -0.1f);
	createObject("Model/forest.fbx", "Model/colour.png", 100.0f, -40.0f, -150.0f, vec3(0.1f, 0.1f, 0.1f), vec3(0.4f, 1.0f, 0.0f), 0.1f);
	createObject("Model/ice.fbx", "Model/colour.png", -300.0f, -20.0f, -450.0f, vec3(0.1f, 0.1f, 0.1f), vec3(0.0f, 0.5f, 0.5f), 0.1f);
	createObject("Model/iceGray.fbx", "Model/colour.png", 100.0f, -140.0f, -250.0f, vec3(0.1f, 0.1f, 0.1f), vec3(0.0f, 0.0f, 1.0f), -0.1f);
	createObject("Model/orange.fbx", "Model/colour.png", 600.0f, 100.0f, -650.0f, vec3(0.1f, 0.1f, 0.1f), vec3(0.0f, 1.0f, 0.0f), 0.1f);
	createObject("Model/pine.fbx", "Model/colour.png", -500.0f, -200.0f, -450.0f, vec3(0.1f, 0.1f, 0.1f), vec3(1.0f, 1.0f, 0.0f), 0.1f);

	// create light object
	createLightObject("Model/myCube.fbx", "Model/light2.png", 10.0f, 10.0f, -20.0f, vec3(3.5f, 3.5f, 3.5f), vec3(1.0f, 1.0f, 0.0f), 1.4f, 0.1f);
	createLightObject("Model/myCube.fbx", "Model/light2.png", 10.0f, 10.0f, -20.0f, vec3(5.0f, 5.0f, 5.0f), vec3(1.0f, 0.0f, 0.0f), 1.2f, 0.2f);
	createLightObject("Model/myCube.fbx", "Model/light2.png", 10.0f, 10.0f, -20.0f, vec3(2.0f, 2.0f, 2.0f), vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.1f);
	createLightObject("Model/myCube.fbx", "Model/light2.png", 10.0f, 10.0f, -20.0f, vec3(1.2f, 1.2f, 1.2f), vec3(0.0f, 0.0f, 1.0f), 0.8f, 0.05f);

	// create vector to hold skybox image locations
	std::vector<std::string> skyboxFaces
	{
		"Skybox/right.png",
		"Skybox/left.png",
		"Skybox/top.png",
		"Skybox/bottom.png",
		"Skybox/front.png",
		"Skybox/back.png"
	};

	unsigned int cubemapTexture = loadCubemap(skyboxFaces);

	// Current sdl event
	SDL_Event event;

	/*------------------------
	Main game loop
	------------------------*/
	while (gameRunning)
	{
		//Calculate deltaTime
		lastTime = tickTime;
		tickTime = SDL_GetTicks();
		deltaTime = (tickTime - lastTime);

		//Check for SDL events
		while (SDL_PollEvent(&event))
		{
			// Events found
			switch (event.type)
			{
				// Window closed
			case SDL_QUIT:
				gameRunning = false;
				break;

			case SDL_MOUSEMOTION:
				// pass event.motion.xrel and event.motion.yrel here
				player.mouseUpdate(event.motion.xrel, event.motion.yrel);
				break;

			case SDL_KEYDOWN:
				// Update key map
				player.manageKeyboardEvents(event);

				// Check individual keys by code
				switch (event.key.keysym.sym)
				{
					// Exit the game
				case SDLK_ESCAPE:
					gameRunning = false;
					break;
					
				case SDLK_F11:

					// switch between fullscreen and window
					if (window.getIsFullscreen()) {
						window.setIsFullscreen();
						SDL_SetWindowFullscreen(mainWindow, 0);
						glViewport(0, 0, window.screenWidth, window.screenHeight);
					}
					else {
						window.setIsFullscreen();
						SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
						SDL_GetWindowSize(mainWindow, &fullWidth, &fullHeight);
						glViewport(0, 0, fullWidth, fullHeight);
					}
					break;
				}
				break;

			case SDL_KEYUP:
				// Update key map
				player.manageKeyboardEvents(event);
				break;
			}
		}

		// move depending on pressed keys
		player.handleKeyboard(deltaTime);

		// update objects
		for (GameObject * obj : GameObjectList)
		{
			obj->Update(deltaTime);
		}

		// update light
		for (GameObject * obj : LightObjectList)
		{
			vec3 offset = vec3(2.0f, -1.0f, -5.0f);
			vec3 pos = player.camera.getCameraFront();
			vec3 playerPos = player.camera.getCameraPos();
			pos = pos * 100.f;
			pos = pos + playerPos;
			obj->SetPosition(pos.x, pos.y, pos.z);
			std::cout << pos.x << pos.y << pos.z << std::endl;
			obj->Update(deltaTime);
		}
		/*
		// update particles
		Particles->Update(deltaTime, *GameObjectList[0], 2, glm::vec2(0.0f,0.0f));
		*/

		// Update game and render with openGL
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Bind program
		glUseProgram(programID);

		// draw skybox
		glDepthMask(GL_FALSE);
		skyboxShader->Use();
		view = glm::mat4(glm::mat3(player.camera.getViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader->GetShaderProgramID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader->GetShaderProgramID(), "proj"), 1, GL_FALSE, glm::value_ptr(proj));

		glBindVertexArray(skyboxVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthMask(GL_TRUE);

		// note that we're translating the scene in the reverse direction of where we want to move
		view = player.camera.getViewMatrix();
		proj = perspective(radians(45.0f), (float)window.screenWidth / (float)window.screenHeight, 0.1f, 6000.0f);
		
		/*
		// Draw particles	
		Particles->Draw(proj);
		*/

		// draw objects
		for (GameObject * obj : GameObjectList) {

			Shader * currentShader = obj->GetShader();
			currentShader->Use();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, obj->GetDiffuseTexture());

			glUniformMatrix4fv(currentShader->GetUniform("modelMatrix"), 1, GL_FALSE, glm::value_ptr(obj->GetModelTransformation()));
			glUniformMatrix4fv(currentShader->GetUniform("view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(currentShader->GetUniform("proj"), 1, GL_FALSE, glm::value_ptr(proj));
			glUniform1i(currentShader->GetUniform("diffuseTexture"), 0);
			// refactor the below it for lighting
			glUniform4fv(ambientMaterialColourLocation, 1, glm::value_ptr(ambientMaterialColour));
			glUniform4fv(diffuseMaterialColourLocation, 1, glm::value_ptr(diffuseMaterialColour));
			glUniform4fv(specularMaterialColourLocation, 1, glm::value_ptr(specularMaterialColour));

			glUniform4fv(ambientLightColourLocation, 1, glm::value_ptr(ambientLightColour));
			glUniform4fv(diffuseLightColourLocation, 1, glm::value_ptr(diffuseLightColour));
			glUniform4fv(specularLightColourLocation, 1, glm::value_ptr(specularLightColour));

			glUniform3fv(lightDirectionLocation, 1, glm::value_ptr(lightDirection));
			glUniform1f(specularMaterialPowerLocation, specularMaterialPower);
			
			glUniform3fv(cameraPositionLocation, 1, glm::value_ptr(cameraPosition));
			
			obj->Render();
		}

		// draw lights
		for (GameObject * obj : LightObjectList) {

			Shader * currentShader = obj->GetShader();
			currentShader->Use();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, obj->GetDiffuseTexture());

			glUniformMatrix4fv(currentShader->GetUniform("modelMatrix"), 1, GL_FALSE, glm::value_ptr(obj->GetModelTransformation()));
			glUniformMatrix4fv(currentShader->GetUniform("view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(currentShader->GetUniform("proj"), 1, GL_FALSE, glm::value_ptr(proj));
			glUniform1i(currentShader->GetUniform("diffuseTexture"), 0);
			// refactor the below it for lighting
			glUniform4fv(ambientMaterialColourLocation, 1, glm::value_ptr(ambientMaterialColour));
			glUniform4fv(diffuseMaterialColourLocation, 1, glm::value_ptr(diffuseMaterialColour));
			glUniform4fv(specularMaterialColourLocation, 1, glm::value_ptr(specularMaterialColour));

			glUniform4fv(ambientLightColourLocation, 1, glm::value_ptr(ambientLightColour));
			glUniform4fv(diffuseLightColourLocation, 1, glm::value_ptr(diffuseLightColour));
			glUniform4fv(specularLightColourLocation, 1, glm::value_ptr(specularLightColour));

			glUniform3fv(lightDirectionLocation, 1, glm::value_ptr(lightDirection));
			glUniform1f(specularMaterialPowerLocation, specularMaterialPower);

			glUniform3fv(cameraPositionLocation, 1, glm::value_ptr(cameraPosition));

			obj->Render();
		}

		SDL_GL_SwapWindow(mainWindow);
	}
	// Call all quit functions
	gameQuit();
}


/* Creates a new game object and stores it in the objectList
takes file and texture locations, x,y,z positions, vec3 for scale, and vec3 for the axis to rotate around, and a rotation speed, set speed to 0 for no rotation*/
void Game::createObject(const std::string & fileLocation, const std::string & textureLocation, float posX, float posY, float posZ, glm::vec3 scale, glm::vec3 rotationAxis, float speed)
{
	MeshCollection * Meshes = new MeshCollection();
	loadMeshesFromFile(fileLocation, Meshes);

	textureID = loadTextureFromFile(textureLocation);

	GameObject * GO = new GameObject();
	GO->SetPosition(posX, posY, posZ);
	GO->SetMesh(Meshes);
	GO->setScale(scale);
	GO->setRotationAxis(rotationAxis);
	GO->setRotationSpeed(speed);
	GO->SetShader(texturedShader);
	GO->SetDiffuseTexture(textureID);
	GameObjectList.push_back(GO);
}

/* Creates a new game object and stores it in the objectList
takes file and texture locations, x,y,z positions, vec3 for scale, and vec3 for the axis to rotate around, and a rotation speed, set speed to 0 for no rotation*/
void Game::createLightObject(const std::string & fileLocation, const std::string & textureLocation, float posX, float posY, float posZ, glm::vec3 scale, glm::vec3 rotationAxis, float speed, float scaleFactor)
{
	MeshCollection * Meshes = new MeshCollection();
	loadMeshesFromFile(fileLocation, Meshes);

	textureID = loadTextureFromFile(textureLocation);

	GameObject * GO = new GameObject();
	GO->SetPosition(posX, posY, posZ);
	GO->SetMesh(Meshes);
	GO->setScale(scale);
	GO->setRotationAxis(rotationAxis);
	GO->setRotationSpeed(speed);
	GO->setScaleFactor(scaleFactor);
	GO->SetShader(texturedShader);
	GO->SetDiffuseTexture(textureID);
	LightObjectList.push_back(GO);
}

unsigned int Game::loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		SDL_Surface * surface = IMG_Load(faces[i].c_str());
		if (surface == nullptr)
		{
			printf("Could not load file %s", IMG_GetError());
			return 0;
		}
		else
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
			SDL_FreeSurface(surface);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

// Clean up resources when the game is exited
void Game::gameQuit()
{
	delete Particles;
	// clear key events
	player.clearEvents();
	// delete textures
	glDeleteTextures(1, &textureID);
	// delete Program
	glDeleteProgram(programID);
	// delete context
	SDL_GL_DeleteContext(gl_Context);
	// close window
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
}
/* https://learnopengl.com/Advanced-OpenGL/Cubemaps */

