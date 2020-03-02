#include "Application.h"

void FluidGL::Application::Init(const char* applicationName, int windowWidth, int windowHeight, bool fullscreen)
{
	renderer = new Renderer();

	renderer->Init(applicationName, windowWidth, windowHeight, fullscreen);
	renderer->LoadProgram("BasicShader");
	renderer->LoadProgram("TextureShader");

}

void FluidGL::Application::Run()
{
	std::vector<vertex> vertices =
	{
		{-1, -1, 0, 1, 0, 0, 1, 0, 0}, // vertex 1
		{1, -1, 0, 0, 1, 0, 1, 1, 0}, // vertex 2
		{1, 1, 0, 0, 0, 1, 1, 1, 1}, // vertex 3
		{-1, 1, 0, 1, 1, 0, 1, 0, 1}, // vertex 4
		{-1, -1, -2, 1, 0, 0, 1, 1, 0}, // vertex 5
		{1, -1, -2, 0, 1, 0, 1, 0, 0}, // vertex 6
		{1, 1, -2, 0, 0, 1, 1, 0, 1}, // vertex 7
		{-1, 1, -2, 1, 1, 0, 1, 1, 1} // vertex 8
	};

	std::vector<GLuint> indices = { 0, 2, 3,
	0, 1, 2,
	1, 6, 2,
	1, 5, 6,
	5, 4, 7,
	5, 7, 6,
	4, 3, 7,
	4, 0, 3,
	2, 7, 3,
	2, 6, 7,
	1, 4, 5,
	1, 0, 4
	};

	GameObject* gameObject = new GameObject();
	GameObject* camera = new GameObject();

	GLuint albedoId = loadTextureFromFile("Resources/Textures/GreatGrateCrate.png");
	Material material = Material();
	material.Init(renderer->GetProgram("TextureShader"), albedoId);

	Mesh mesh = Mesh();
	mesh.Init(vertices, indices);

	gameObject->transform->MoveTo(glm::vec3(0, 0, 0));
	gameObject->AddComponent(MeshRenderer());
	gameObject->GetComponent(MeshRenderer())->materials.push_back(material);
	gameObject->GetComponent(MeshRenderer())->mesh = &mesh;

	camera->AddComponent(Camera());
	camera->GetComponent(Camera())->Init(renderer->GetProgram("TextureShader"));
	camera->transform->MoveTo(glm::vec3(0, 0, 10));

	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;

	float i = 0;

 	while (running)
	{
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
				case SDLK_LEFT:
					gameObject->transform->Move(glm::vec3(1, 0, 0));
					break;
				case SDLK_RIGHT:
					gameObject->transform->Move(glm::vec3(-1, 0, 0));
					break;
				case SDLK_UP:
					gameObject->transform->Move(glm::vec3(0, 1, 0));
					break;
				case SDLK_DOWN:
					gameObject->transform->Move(glm::vec3(0, -1, 0));
					break;
				}
			}
		}

		// Clear screen
		renderer->ClearScreen(0, 0, 0, 1);

		//====RENDER OBJECTS HERE====//
		//camera->transform->RotateAngles(glm::vec3(0, 1, 0), (int)i % 360);
		gameObject->GetComponent(MeshRenderer())->Render(camera->GetComponent(Camera()));

		// Swap buffers
		renderer->SwapBuffers();
	}
}

void FluidGL::Application::Quit()
{
	delete renderer;
	GameObject::DeleteAll();
}
