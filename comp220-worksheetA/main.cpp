#include <iostream>
#include <chrono> // Get time
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h> // Needs to go after glew include
#include <glm/glm.hpp> // Old header file standard (.hpp)

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.h"
#include "Vertex.h"

#include "OpenGLWindow.h"
#include "Texture.h"
#include "Model.h"
#include "Timer.h"
#include "GameObject.h"
#include "Camera.h"

int main(int argc, char ** argsv)
{
	unsigned int windowWidth = 800;
	unsigned int windowHeight = 600;

	OpenGLWindow *openGLWindow = new OpenGLWindow();
	bool success = openGLWindow->CreateWindow(windowWidth, windowHeight);

	if (!success)
	{
		openGLWindow->RemoveWindow();
		if (openGLWindow)
		{
			delete openGLWindow;
			openGLWindow = nullptr;
		}
		return -1;
	}

	// Hide and lock cursor to screen
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	std::vector<GameObject*> GameObjectList;

	MeshCollection * teapotMeshes = new MeshCollection();
	loadMeshFromFile("utah-teapot.fbx", teapotMeshes);

	Shader * texturedShader = new Shader();
	texturedShader->Load("textureVert.glsl", "textureFrag.glsl");

	GLuint textureID = loadTextureFromFile("brick_D.png");

	GameObject * teapotGO = new GameObject();
	teapotGO->SetPosition(0.0f, 0.0f, -100.0f);
	teapotGO->SetMesh(teapotMeshes);
	teapotGO->SetShader(texturedShader);
	teapotGO->SetDiffuseTexture(textureID);

	//GameObjectList.push_back(cubeGO);
	GameObjectList.push_back(teapotGO);


	// Water mesh needs to later be moved out of GameObjectList
	// so that it can be rendered after all other objects
	// or add some sort of layer/priority system
	MeshCollection * waterMesh = new MeshCollection();
	loadMeshFromFile("water.fbx", waterMesh);

	texturedShader = new Shader();
	texturedShader->Load("waterVert.glsl", "waterFrag.glsl");

	textureID = loadTextureFromFile("waterTexture.png");

	GameObject * waterGO = new GameObject();
	waterGO->SetPosition(0.0f, -20.0f, -50.0f);
	waterGO->SetMesh(waterMesh);
	waterGO->SetShader(texturedShader);
	waterGO->SetDiffuseTexture(textureID);

	//GameObjectList.push_back(waterGO);

	Camera * camera = new Camera();

	bool fullScreen = false;

	float morphBlendFactor = 0.0f;

	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe


	Timer timer;
	timer.Start();

	// Capture mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;
	while (running)
	{
		timer.Update();

		int lastX = 0;
		int lastY = 0;

		bool paused = false;

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
				case SDLK_F11:
					openGLWindow->FullScreen(!fullScreen);
					fullScreen = !fullScreen;
					break;
				case SDLK_UP:
					morphBlendFactor += 0.1f;
					break;
				case SDLK_DOWN:
					morphBlendFactor -= 0.1f;
					break;

				case SDLK_SPACE:
					paused = !paused;
					break;

				// Refactor later -- BUG jumps around
				case SDLK_w:
					if (!paused)
						camera->ProcessKeyboard(FORWARD, timer.GetDeltaTime());
					break;
				case SDLK_s:
					if (!paused)
						camera->ProcessKeyboard(BACKWARD, timer.GetDeltaTime());
					break;
				case SDLK_a:
					if (!paused)
						camera->ProcessKeyboard(LEFT, timer.GetDeltaTime());
					break;
				case SDLK_d:
					if (!paused)
						camera->ProcessKeyboard(RIGHT, timer.GetDeltaTime());
					break;
				}
			// If the mouse is being moved
			case SDL_MOUSEMOTION:
				//std::cout << ev.motion.xrel << " | " << ev.motion.yrel << std::endl;
				if (!paused)
					camera->ProcessMouseMovement(ev.motion.xrel - lastX, lastY - ev.motion.yrel, timer.GetDeltaTime());

				lastX = ev.motion.xrel;
				lastY = ev.motion.yrel;
				break;
			}
		}

		morphBlendFactor += timer.GetDeltaTime();
		morphBlendFactor = glm::clamp(morphBlendFactor, 0.0f, 1.0f);

		//update
		if (!paused) {
			for (GameObject * obj : GameObjectList)
			{
				obj->Update(timer.GetDeltaTime());
			}
			waterGO->Update(timer.GetDeltaTime());
		}

		// Update game and draw with OpenGL
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render game objects
		for (GameObject * obj : GameObjectList) {

			// Centralise information passing
			Shader * currentShader = obj->GetShader();
			currentShader->Use();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, obj->GetDiffuseTexture());

			glUniformMatrix4fv(currentShader->GetUniform("modelMatrix"), 1, GL_FALSE, glm::value_ptr(obj->GetModelTransformation()));
			glUniformMatrix4fv(currentShader->GetUniform("viewMatrix"), 1, GL_FALSE, glm::value_ptr(camera->ViewMatrix()));
			glUniformMatrix4fv(currentShader->GetUniform("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(camera->ProjectionMatrix(openGLWindow)));
			//glUniform1f(currentShader->GetUniform("morphBlendAlpha"), 0.0f);
			//glUniform1i(currentShader->GetUniform("diffuseTexture"), 0);
			glUniform1f(currentShader->GetUniform("currentTime"), timer.GetUpdatedTime());
			//glUniform1f(currentShader->GetUniform("morphBlendFactor"), morphBlendFactor);


			obj->Render();
		}

		// Render water
		Shader * currentShader = waterGO->GetShader();
		currentShader->Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, waterGO->GetDiffuseTexture());

		glUniformMatrix4fv(currentShader->GetUniform("modelMatrix"), 1, GL_FALSE, glm::value_ptr(waterGO->GetModelTransformation()));
		glUniformMatrix4fv(currentShader->GetUniform("viewMatrix"), 1, GL_FALSE, glm::value_ptr(camera->ViewMatrix()));
		glUniformMatrix4fv(currentShader->GetUniform("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(camera->ProjectionMatrix(openGLWindow)));
		glUniform1f(currentShader->GetUniform("currentTime"), timer.GetUpdatedTime());

		waterGO->Render();

		SDL_GL_SwapWindow(openGLWindow->GetWindow());

	}

	// Iterator to the beginning of the vector
	auto iter = GameObjectList.begin();

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
	}

	// Remove water
	if (waterGO)
	{
		delete waterGO;
		waterGO = nullptr;
	}

	// Flushes the vector
	GameObjectList.clear();

	// Remove camera
	if (camera)
	{
		delete camera;
		camera = nullptr;
	}

	// Delete Context
	//SDL_GL_DeleteContext(gl_Context);

	// Close SDL IMAGE
	IMG_Quit();

	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();

	return 0;
}
