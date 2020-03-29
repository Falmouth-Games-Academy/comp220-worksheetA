#include "Application.h"

void FluidGL::Application::Init(const char* applicationName, int windowWidth, int windowHeight, bool fullscreen)
{
	renderer = new Renderer();

	renderer->Init(applicationName, windowWidth, windowHeight, fullscreen);
	renderer->LoadProgram("BasicShader");
	renderer->LoadProgram("TextureShader");
	renderer->LoadProgram("Lighting");
	renderer->LoadProgram("PostProcessing");
}

void FluidGL::Application::Run()
{
	GameObject* gameObject = new GameObject();
	GameObject* terrain = new GameObject();
	GameObject* camera = new GameObject();

	fs::create_directory("Benchmarks");

	std::string fName = "Benchmarks/Benchmark0.txt";
	int i = 0;

	while (fs::exists(fName))
	{
		fName = "Benchmarks/Benchmark" + std::to_string(++i) + ".txt";
	}

	std::ofstream f(fName);
	
	//GLuint albedoId = loadTextureFromFile("Resources/Textures/TEX_Car_UV.png");
	GLuint albedoId = loadTextureFromFile("Resources/Textures/TEX_Panel_Albedo.png");
	GLuint normalId = loadTextureFromFile("Resources/Textures/TEX_Panel_Normal.png");
	Material material = Material();
	material.Init(renderer->GetProgram("Lighting"), albedoId, normalId);

	Mesh mesh = Mesh();
	//mesh.Init(vertices, indices);
	//mesh.LoadFromFile("Resources/Models/Cube.obj", MeshFormat::MESH_FORMAT_OBJ);
	mesh.LoadFromFile("Resources/Models/SphereSmooth.obj", MeshFormat::MESH_FORMAT_OBJ);
	//mesh.LoadFromFile("Resources/Models/Monkey.obj", MeshFormat::MESH_FORMAT_OBJ);
	//mesh.LoadFromFile("Resources/Models/MonkeySmooth.obj", MeshFormat::MESH_FORMAT_OBJ);
	//mesh.LoadFromFile("Resources/Models/Car.obj", MeshFormat::MESH_FORMAT_OBJ);

	Mesh terrainMesh = Mesh();
	//terrainMesh.LoadFromFile("Resources/Models/Terrain.obj", MeshFormat::MESH_FORMAT_OBJ);

	gameObject->transform->MoveTo(glm::vec3(0, 0, 0));
	terrain->transform->Scale(glm::vec3(10, 10, 10));

	gameObject->AddComponent(ParticleSystem());
	gameObject->GetComponent(ParticleSystem())->Init(10000, 200.0f, glm::vec3(0, 1, 0), 0.05f, 1000.0f, &material, &mesh);

	//terrain->AddComponent(MeshRenderer());
	//terrain->GetComponent(MeshRenderer())->materials.push_back(material);
	//terrain->GetComponent(MeshRenderer())->mesh = &terrainMesh;

	camera->AddComponent(Camera());
	camera->GetComponent(Camera())->Init(renderer->GetProgram("TextureShader"));
	camera->transform->MoveTo(gameObject->transform->Position() - glm::vec3(10, 0, 0));

	f << "System information:\nVendor: " << glGetString(GL_VENDOR) << "\n";
	f << "Renderer: " << glGetString(GL_RENDERER) << "\n";
	f << "<=====BEGIN BENCHMARK=====>\n";
	
	//// Create texture to render to
	//GLuint postTextureID = CreateTexture(1280, 720);

	//// Create depth buffer
	//GLuint depthBufferID;
	//glGenRenderbuffers(1, &depthBufferID);
	//// Bind depth buffer
	//glBindRenderbuffer(GL_RENDERBUFFER, depthBufferID);
	//// The higher the buffer the more precise it is but the more expensive it is. GL_DEPTH_COMPONENT is 8 bits and should be enough
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1280, 720);

	//// Create frame buffer
	//GLuint frameBufferID;
	//glGenFramebuffers(1, &frameBufferID);
	//glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

	//// Bind texture - depends on how many attachments your drivers support
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, postTextureID, 0);

	//// Bind the depth buffer
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferID);

	//// Check the framebuffer works well
	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	//{
	//	printf("Incomplete framebuffer!\n");
	//	Quit();
	//}

	//// Vertices for Post processing quad
	//float vertices[] =
	//{
	//	-1, -1,
	//	1, -1,
	//	-1, 1,
	//	1, 1
	//};

	//GLuint screenVBO;
	//glGenBuffers(1, &screenVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
	//glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);
	//
	//GLuint screenVAO;
	//glGenVertexArrays(1, &screenVAO);
	//glBindVertexArray(screenVAO);
	//glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
	//
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//GLuint postProcessingProgramID = renderer->GetProgram("PostProcessing");

	//GLuint texture0ID = glGetUniformLocation(postProcessingProgramID, "texture0");

	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;

	float input = 0;
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	float runTime = 0;
	bool benchmark = false;

	Time time = Time();

 	while (running)
	{
		time.StartTimer();
		input = 0;
		keys = SDL_GetKeyboardState(NULL);
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
				case SDLK_SPACE:
					renderer->SetFullscreen(!renderer->IsFullscreen());
					break;
				}
			}
		}

		if (keys[SDL_SCANCODE_UP])
			input = -0.1;
		if (keys[SDL_SCANCODE_DOWN])
			input += 0.1;
		if (keys[SDL_SCANCODE_LEFT])
			camera->transform->RotateAngles(glm::vec3(1, 0, 0), -2);
		if(keys[SDL_SCANCODE_RIGHT])
			camera->transform->RotateAngles(glm::vec3(1, 0, 0), 2);

		camera->transform->Move(-camera->transform->Forward() * input);
		
		// Bind the frame buffer
		//glBindFramebuffer(GL_FRAMEBUFFER, depthBufferID);
		
		// Clear screen
		renderer->ClearScreen(0, 0, 0, 1);

		//====UPDATE OBJECTS HERE====//

		gameObject->GetComponent(ParticleSystem())->Update();

		glm::quat q = Transform::RandomRotation();
		
		//======END UPDATE HERE======//
		//====RENDER OBJECTS HERE====//
		

		gameObject->GetComponent(ParticleSystem())->RenderParticles(camera->GetComponent(Camera())->GetViewMatrix(), camera->GetComponent(Camera())->GetProjectionMatrix(), camera->transform->Position());
		//printf("Particles rendered : %d\nCurrent FPS: %d\n", gameObject->GetComponent(ParticleSystem())->ParticleCount(), (int)(1.0 / time.deltaTime));

		//terrain->GetComponent(MeshRenderer())->Render(camera->GetComponent(Camera())->GetViewMatrix(), camera->GetComponent(Camera())->GetProjectionMatrix());

		//======END RENDER HERE======//

		//// Start post processing
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//renderer->ClearScreen(0, 0, 0, 1, GL_COLOR_BUFFER_BIT);

		//glUseProgram(postProcessingProgramID);

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, postTextureID);
		//glUniform1d(texture0ID, 0);
		//
		//// Draw post processing quad
		//glDisable(GL_DEPTH_TEST);
		//glBindVertexArray(screenVAO);
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		// Display an FPS counter in the window title
		std::string title = renderer->GetWindowTitle();
		title = title + " @ " + std::to_string((int)(1.0 / time.deltaTime)) + " FPS & " + std::to_string(mesh.triangles.size() * gameObject->GetComponent(ParticleSystem())->ParticleCount() / 3) + " triangles rendered";
		SDL_SetWindowTitle(renderer->GetWindow(), title.c_str());

		if (int(runTime) % 5 == 0 && benchmark)
		{
			f << "Simulation runtime: " << std::to_string((int)runTime) <<  " s. FPS: " << std::to_string((int)(1.0 / time.deltaTime)) << " Particles " << std::to_string(gameObject->GetComponent(ParticleSystem())->ParticleCount()) << "\n";
			benchmark = false;
		}
		else if (int(runTime) % 5 == 1)
		{
			benchmark = true;
		}

		// Swap buffers
		renderer->SwapBuffers();
		// End frame timer
		time.EndTimer();
		runTime += time.deltaTime;

		if ((int)(runTime) == 120)
			running = false;
	}

	//glDeleteBuffers(1, &screenVBO);
	//glDeleteVertexArrays(1, &screenVAO);

	//glDeleteRenderbuffers(1, &depthBufferID);
	//glDeleteTextures(1, &postTextureID);
	//glDeleteBuffers(1, &screenVBO);
	//glDeleteFramebuffers(1, &frameBufferID);
}

void FluidGL::Application::Quit()
{
	delete renderer;
	GameObject::DeleteAll();
}
