#include "Application.h"

void FluidGL::Application::Init(const char* applicationName, int windowWidth, int windowHeight, bool fullscreen)
{
	renderer = new Renderer();

	renderer->Init(applicationName, windowWidth, windowHeight, fullscreen);
	renderer->LoadProgram("BasicShader");

}

void FluidGL::Application::Run()
{
	GameObject* gameObject = new GameObject();
	GameObject* camera = new GameObject();

	std::vector<GLfloat> vertices = {
	   -1, -1, 0,
	   0, -1, 0,
	   -1, 2, 0
	};

	GLuint modelMatrixLocation = glGetUniformLocation(renderer->GetProgram("BasicShader"), "model");
	GLuint viewMatrixLocation = glGetUniformLocation(renderer->GetProgram("BasicShader"), "viewMatrix");
	GLuint projectionMatrixLocation = glGetUniformLocation(renderer->GetProgram("BasicShader"), "projectionMatrix");

	gameObject->Init(renderer->GetProgram("BasicShader"));
	gameObject->AddComponent(Model());
	gameObject->GetComponent(Model())->Init(vertices, renderer->GetProgram("BasicShader"));

	camera->Init(renderer->GetProgram("BasicShader"));
	camera->AddComponent(Camera());
	camera->transform->MoveTo(glm::vec3(0, 0, -1));

	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;

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
				}
			}
		}

		renderer->ClearScreen(1, 0, 0, 1);
		gameObject->Render();

		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(gameObject->GetComponent(Transform())->GetTransformation()));
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(
			camera->GetComponent(
				Camera())->GetViewMatrix(camera->GetComponent(Transform())->Position(),
					camera->GetComponent(Transform())->Position() + glm::vec3(0, 0, 1),
					glm::vec3(0, 1, 0)
			)));
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->GetComponent(Camera())->GetProjectionMatrix(true, 45, 16.0 / 9.0, 0.01, 100.0)));

		renderer->SwapBuffers();
	}
}

void FluidGL::Application::Quit()
{
	delete renderer;
	GameObject::DeleteAll();
}
