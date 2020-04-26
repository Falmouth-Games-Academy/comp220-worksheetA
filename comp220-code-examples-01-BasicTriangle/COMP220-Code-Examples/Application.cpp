#include "Application.h"

void FluidGL::Application::Init(const char* applicationName, int windowWidth, int windowHeight, bool fullscreen)
{
	renderer = new Renderer();

	renderer->Init(applicationName, windowWidth, windowHeight, fullscreen);
	renderer->LoadProgram("BasicShader");
	renderer->LoadProgram("TextureShader");
	renderer->LoadProgram("Lighting");
	renderer->LoadProgram("PostProcessing");
	renderer->InitPostProcess();

	physicsContext = new PhysicsContext();
	physicsContext->Init();
}

void FluidGL::Application::Run()
{
	GameObject* particleSpawner = new GameObject();
	GameObject* camera = new GameObject();
	GameObject* sphere = new GameObject();
	GameObject* box1 = new GameObject();
	GameObject* box2 = new GameObject();
	GameObject* box3 = new GameObject();
	GameObject* box4 = new GameObject();

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
	mesh.LoadFromFile("Resources/Models/SphereSmooth.obj", MeshFormat::MESH_FORMAT_OBJ);

	particleSpawner->transform->Move(glm::vec3(0, 5, 0));
	particleSpawner->AddComponent(ParticleSystem());
	particleSpawner->GetComponent(ParticleSystem())->Init(10000, 50, glm::vec3(0, 1, 0), 0.01f, 500.0f, &material, &mesh, 0, physicsContext);

	sphere->transform->MoveTo(glm::vec3(0, -3, 0));

	sphere->AddComponent(MeshRenderer());
	sphere->GetComponent(MeshRenderer())->mesh = &mesh;
	sphere->GetComponent(MeshRenderer())->materials.push_back(material);

	sphere->AddComponent(Rigidbody());
	sphere->GetComponent(Rigidbody())->Init(physicsContext, new btBoxShape(btVector3(2, 1, 2)), 100000);
	sphere->GetComponent(Rigidbody())->SetGravity(glm::vec3(0, 0, 0));

	box1->AddComponent(Rigidbody());
	box1->GetComponent(Rigidbody())->Init(physicsContext, new btBoxShape(btVector3(2, 3, 1)), 100000);
	box1->GetComponent(Rigidbody())->SetGravity(glm::vec3(0, 0, 0));
	box1->transform->MoveTo(glm::vec3(0, 0, 3));

	box2->AddComponent(Rigidbody());
	box2->GetComponent(Rigidbody())->Init(physicsContext, new btBoxShape(btVector3(2, 3, 1)), 100000);
	box2->GetComponent(Rigidbody())->SetGravity(glm::vec3(0, 0, 0));
	box2->transform->MoveTo(glm::vec3(0, 0, -3));

	box3->AddComponent(Rigidbody());
	box3->GetComponent(Rigidbody())->Init(physicsContext, new btBoxShape(btVector3(1, 3, 2)), 100000);
	box3->GetComponent(Rigidbody())->SetGravity(glm::vec3(0, 0, 0));
	box3->transform->MoveTo(glm::vec3(3, 0, 0));

	box4->AddComponent(Rigidbody());
	box4->GetComponent(Rigidbody())->Init(physicsContext, new btBoxShape(btVector3(1, 3, 2)), 100000);
	box4->GetComponent(Rigidbody())->SetGravity(glm::vec3(0, 0, 0));
	box4->transform->MoveTo(glm::vec3(-3, 0, 0));

	camera->AddComponent(Camera());
	camera->GetComponent(Camera())->Init(renderer->GetProgram("TextureShader"));
	camera->transform->MoveTo(glm::vec3(-10, 0, 0));

	f << "System information:\nVendor: " << glGetString(GL_VENDOR) << "\n";
	f << "Renderer: " << glGetString(GL_RENDERER) << "\n";
	f << "<=====BEGIN BENCHMARK=====>\n";

	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;

	float input = 0;
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	float runTime = 0;
	bool benchmark = false;

	renderer->usePostProcess = false;

	Time time = Time();

	sphere->GetComponent(Rigidbody())->UpdatePhysicsContext();
	box1->GetComponent(Rigidbody())->UpdatePhysicsContext();
	box2->GetComponent(Rigidbody())->UpdatePhysicsContext();
	box3->GetComponent(Rigidbody())->UpdatePhysicsContext();
	box4->GetComponent(Rigidbody())->UpdatePhysicsContext();
	particleSpawner->GetComponent(ParticleSystem())->UpdatePhysicsContext();

	bool usePhysics = true;

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
				case SDLK_p:
					usePhysics = !usePhysics;
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

		//====UPDATE PHYSICS HERE====//
		if (usePhysics)
		{
			physicsContext->UpdatePhysics();
		
			sphere->GetComponent(Rigidbody())->UpdatePhysicsComponent();
			box1->GetComponent(Rigidbody())->UpdatePhysicsComponent();
			box2->GetComponent(Rigidbody())->UpdatePhysicsComponent();
			box3->GetComponent(Rigidbody())->UpdatePhysicsComponent();
			box4->GetComponent(Rigidbody())->UpdatePhysicsComponent();

			particleSpawner->GetComponent(ParticleSystem())->UpdateParticleSystemPhysics();
		}
		//====UPDATE OBJECTS HERE====//

		particleSpawner->GetComponent(ParticleSystem())->Update();
		
		//======END UPDATE HERE======//
		//====RENDER OBJECTS HERE====//
		renderer->PreRender();

		sphere->GetComponent(MeshRenderer())->Render(camera->GetComponent(Camera())->GetViewMatrix(), camera->GetComponent(Camera())->GetProjectionMatrix(), camera->transform->Position());
		particleSpawner->GetComponent(ParticleSystem())->RenderParticles(camera->GetComponent(Camera())->GetViewMatrix(), camera->GetComponent(Camera())->GetProjectionMatrix(), camera->transform->Position());

		renderer->PostRender();
		//======END RENDER HERE======//

		// Display an FPS counter in the window title
		std::string title = renderer->GetWindowTitle();
		title = title + " @ " + std::to_string((int)(1.0 / time.deltaTime)) + " FPS & " + std::to_string(mesh.triangles.size() * particleSpawner->GetComponent(ParticleSystem())->ParticleCount() / 3) + " triangles rendered";
		SDL_SetWindowTitle(renderer->GetWindow(), title.c_str());

		if (int(runTime) % 5 == 0 && benchmark)
		{
			f << "Simulation runtime: " << std::to_string((int)runTime) <<  " s. FPS: " << std::to_string((int)(1.0 / time.deltaTime)) << " Particles " << std::to_string(particleSpawner->GetComponent(ParticleSystem())->ParticleCount()) << "\n";
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
		//runTime += time.deltaTime;

		//if ((int)(runTime) == 120)
		//	running = false;
	}

	particleSpawner->GetComponent(ParticleSystem())->DestroyRigidBodies();
	sphere->GetComponent(Rigidbody())->Destroy();
	box1->GetComponent(Rigidbody())->Destroy();
	box2->GetComponent(Rigidbody())->Destroy();
	box3->GetComponent(Rigidbody())->Destroy();
	box4->GetComponent(Rigidbody())->Destroy();
}

void FluidGL::Application::Quit()
{
	if (renderer)
	{
		delete renderer;
		renderer = nullptr;
	}

	if (physicsContext)
	{
		delete physicsContext;
		physicsContext = nullptr;
	}

	GameObject::DeleteAll();
}
