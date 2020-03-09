#include "Application.h"

void FluidGL::Application::Init(const char* applicationName, int windowWidth, int windowHeight, bool fullscreen)
{
	renderer = new Renderer();

	renderer->Init(applicationName, windowWidth, windowHeight, fullscreen);
	renderer->LoadProgram("BasicShader");
	renderer->LoadProgram("TextureShader");
	renderer->LoadProgram("LightShader");
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

	//GLuint albedoId = loadTextureFromFile("Resources/Textures/TEX_Car_UV.png");
	GLuint albedoId = loadTextureFromFile("Resources/Textures/TEX_Panel_Albedo.png");
	GLuint normalId = loadTextureFromFile("Resources/Textures/TEX_Panel_Normal.png");
	Material material = Material();
	material.Init(renderer->GetProgram("TextureShader"), albedoId, normalId);

	Mesh mesh = Mesh();
	//mesh.Init(vertices, indices);
	//mesh.LoadFromFile("Resources/Models/Cube.obj", MeshFormat::MESH_FORMAT_OBJ);
	mesh.LoadFromFile("Resources/Models/Car.obj", MeshFormat::MESH_FORMAT_OBJ);

	gameObject->transform->MoveTo(glm::vec3(0, .5, 0));
	gameObject->transform->Scale(glm::vec3(7, 7, 7));
	gameObject->AddComponent(MeshRenderer());
	gameObject->GetComponent(MeshRenderer())->materials.push_back(material);
	gameObject->GetComponent(MeshRenderer())->mesh = &mesh;

	camera->AddComponent(Camera());
	camera->GetComponent(Camera())->Init(renderer->GetProgram("TextureShader"));
	camera->transform->MoveTo(gameObject->transform->Position() - glm::vec3(10, 0, 0));

	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;

	float input = 0;
	const Uint8* keys = SDL_GetKeyboardState(NULL);

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

		// Clear screen
		renderer->ClearScreen(0, 0, 0, 1);

		//====RENDER OBJECTS HERE====//
		//camera->transform->RotateAngles(glm::vec3(0, 1, 0), (int)i % 360);
		gameObject->GetComponent(MeshRenderer())->Render(camera->GetComponent(Camera()));

		glm::vec3 forward = camera->transform->Forward();
		// Swap buffers
		renderer->SwapBuffers();
		time.EndTimer();
	}
}

void FluidGL::Application::Quit()
{
	delete renderer;
	GameObject::DeleteAll();
}
