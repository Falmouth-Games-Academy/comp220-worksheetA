#include "Application.h"

ByGL::Application::Application()
{

}

ByGL::Application::~Application()
{
}

int ByGL::Application::Init()
{
#pragma region SDL Setup
	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	//https://wiki.libsdl.org/SDL_Init
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		//Display an error message box
		//https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return Quit();
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#pragma endregion
#pragma region ECS Setup

	// Initialize Coordinator
	coordinator = new Coordinator();
	coordinator->Init();
	RegisterComponents();
#pragma endregion

#pragma region
#pragma endregion

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	return 1;
	running = true;
}


int ByGL::Application::Run()
{
	// Initialize
	if (!Init())
	{
		return Quit();
	}
#pragma region Components
	// Create signatures for the systems
	std::vector<Signature> sigs;
	
	sigs = AddSignature(sigs, coordinator->GetComponentType<WindowComponent>());
	std::shared_ptr<WindowUpdateSystem> windowUpdate = RegisterSystems<WindowUpdateSystem>(sigs);
	sigs.clear();

	sigs = AddSignature(sigs, coordinator->GetComponentType<DebugComponent>());
	std::shared_ptr<DebugSystem> debugSystem = RegisterSystems<DebugSystem>(sigs);
	sigs.clear();

	sigs = AddSignature(sigs, coordinator->GetComponentType<MeshCollectionComponent>());
	sigs = AddSignature(sigs, coordinator->GetComponentType<MeshComponent>());
	sigs = AddSignature(sigs, coordinator->GetComponentType<Transform>());
	std::shared_ptr<MeshSystem> meshSystem = RegisterSystems<MeshSystem>(sigs);
	sigs.clear();
	
	sigs = AddSignature(sigs, coordinator->GetComponentType<Texture>());
	std::shared_ptr<TextureSystem> textureSystem = RegisterSystems<TextureSystem>(sigs);
	sigs.clear();

	sigs = AddSignature(sigs, coordinator->GetComponentType<CameraComponent>());
	sigs = AddSignature(sigs, coordinator->GetComponentType<Transform>());
	std::shared_ptr<CameraSystem> camSystem = RegisterSystems<CameraSystem>(sigs);
	sigs.clear();

	sigs = AddSignature(sigs, coordinator->GetComponentType<MeshCollectionComponent>());
	std::shared_ptr<ShaderSystem> shaderSystem = RegisterSystems<ShaderSystem>(sigs);
	sigs.clear();

	// Create entity
	auto ent = coordinator->CreateEntity();
	auto visualEntity = coordinator->CreateEntity();
	auto cameraEntity = coordinator->CreateEntity();
	// Initialise Components
	WindowComponent* wc = new WindowComponent();
	wc->Init("Wimdow", 300, 300, 800, 600, true);

	// Add components to Entity
	coordinator->AddComponent<WindowComponent>(ent, *wc);
	// Initialize the window and add it to component
	wc->SetWindow(windowUpdate->CreateWindow(coordinator, ent));
	// Remove the component then readd it with the window ptr
	coordinator->RemoveComponent<WindowComponent>(ent);
	coordinator->AddComponent<WindowComponent>(ent, *wc);
	coordinator->AddComponent<DebugComponent>(ent, DebugComponent{coordinator->GetComponent<WindowComponent>(ent).title, " created."});

	coordinator->AddComponent<MeshCollectionComponent>(visualEntity, MeshCollectionComponent{meshSystem->LoadMeshCollectionFromFile("2019-20-utah-teapot.fbx")});
	// x, y, z, qX, qY, qZ, qW, sX, sY, sZ
	coordinator->AddComponent<Transform>(visualEntity, Transform{0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f});
	coordinator->AddComponent<Texture>(visualEntity, Texture{textureSystem->LoadTextureFromFile("brick_D.png")});
	//coordinator->AddComponent<Vertex>(visualEntity, Vertex{});
	// x, y, z, lookX, lookY, lookZ, upX, upY, upZ, fov, aspectWidth, aspectHeight, nearClip, FarClip
	coordinator->AddComponent<CameraComponent>(cameraEntity, CameraComponent{ 0, 0, 0, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 45.0f, 1280, 720, 0.1f, 1000.0f});
	coordinator->AddComponent<Transform>(cameraEntity, Transform{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f});

	debugSystem->Update(coordinator);

	shaderSystem->Load("DefaultVert.glsl", "DefaultFrag.glsl");
	shaderSystem->SetCam(coordinator->GetComponentPtr<CameraComponent>(cameraEntity));
	//shaderSystem->
#pragma endregion
	while (running)
	{
		// Debug System

		// Physics System

		// Events System - Actually make this a System
		Events();
		// Update Components


		// Camera Update
		camSystem->UpdateCameraPosition(coordinator);

		// Start Render and Add Textures
		windowUpdate->StartRender();

		shaderSystem->Bind();
		// Mesh Update
		meshSystem->Update(coordinator);
		//shaderSystem->Update(coordinator, shaderSystem->GetUniform("view"), shaderSystem->GetUniform("projection"));
		meshSystem->Render(coordinator);
		// End Rendering
		//windowUpdate->EndRender();

		// Swap Windows
		windowUpdate->UpdateWindow(coordinator);

	}
	//for (int i = 0; i < glWindow.size(); i++)
	//	delete glWindow.at(i);
	//glWindow.clear();
	delete(wc);
	delete(coordinator);
	return Quit();
}

std::vector<Signature> ByGL::Application::AddSignature(std::vector<Signature> signatures, ComponentType newSignature)
{
	Signature sig;
	sig.set(newSignature);
	signatures.push_back(sig);
	return signatures;
}

void ByGL::Application::Events()
{
	// Resolve Events
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
			}
		}
	}
}


void ByGL::Application::RegisterComponents()
{
	coordinator->RegisterComponent<CameraComponent>();
	coordinator->RegisterComponent<DebugComponent>();
	coordinator->RegisterComponent<MeshCollectionComponent>();
	coordinator->RegisterComponent<MeshComponent>();
	coordinator->RegisterComponent<Texture>();
	coordinator->RegisterComponent<Transform>();
	coordinator->RegisterComponent<Vertex>();
	coordinator->RegisterComponent<WindowComponent>();
}


int ByGL::Application::Quit()
{
	//https://wiki.libsdl.org/SDL_Quit
	running = false;
	SDL_Quit();
	return 0;
}
