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

int main(int argc, char ** argsv)
{
	OpenGLWindow *openGLWindow = new OpenGLWindow();
	bool success = openGLWindow->createWindow(800, 600);
	SDL_Window *window = openGLWindow->getWindow();

	if (!success)
	{
		return -1;
	}

	// Mesh collection(vector)
	//std::vector<Mesh*> meshes;
	// Teapot
	//loadMeshesFromFile("utah-teapot.fbx", meshes);
	std::vector<GameObject*> GameObjectList;

	Vertex verts[] =
	{

		{ -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f, 0.5f,-0.5f, -0.5f, 0.5f, 1.0f },
		{ 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f },

		{ -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 1.0f },
		{ -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 1.0f }
	};

	//Define triangles in the cube
	unsigned int indices[] =
	{
		1, 0 , 4,
		4, 0, 5,

		7, 2, 1,
		7, 1, 4,

		1, 2, 3,
		1, 3, 0,

		5, 0, 3,
		5, 3, 6,

		6, 3, 7,
		7, 3, 2,

		7, 4, 5,
		7, 5, 6
	};

	Mesh * morphMesh = new Mesh();
	morphMesh->init();
	morphMesh->copyBufferData(verts, 8, indices, 36);
	MeshCollection* morphMeshes = new MeshCollection();
	morphMeshes->addMesh(morphMesh);

	// Create and compile our GLSL program from the shader
	Shader * morphShader = new Shader();
	morphShader->Load("vert.glsl", "frag.glsl");

	GameObject * cubeGO = new GameObject();
	cubeGO->SetPosition(0.0f, 0.0f, 1.0f);
	cubeGO->SetMesh(morphMeshes);
	cubeGO->SetShader(morphShader);

	GameObjectList.push_back(cubeGO);


	// Triangle
	glm::vec3 trianglePosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 triangleScale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 trinagleRotation = glm::uvec3(0.0f, 0.0f, 0.0f);

	// View
	glm::mat4 translationMatrix = glm::translate(trianglePosition);
	glm::mat4 scaleMatrix = glm::scale(triangleScale);
	glm::mat4 rotationMatrix = glm::rotate(trinagleRotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(trinagleRotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(trinagleRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	// Model
	glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	// Camera
	glm::vec3 cameraPosition = glm::vec3(2.0f, 25.0f, -30.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

	glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), ((float)800 / 600), 0.1f, 100.0f);

	bool fullScreen = false;

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe


	Timer timer;
	timer.Start();
	
	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;
	while (running)
	{
		timer.Update();

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
					if (fullScreen)
					{
						SDL_SetWindowFullscreen(window, 0);
						fullScreen = false;
					}
					else
					{
						SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
						fullScreen = true;
					}
					break;
				}
			}
		}

		//update
		for (GameObject * obj : GameObjectList)
		{
			obj->Update(timer.GetDeltaTime());
		}

		// Update game and draw with OpenGL
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (GameObject * obj : GameObjectList) {

			Shader * currentShader = obj->GetShader();
			currentShader->Use();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, obj->GetDiffuseTexture());

			glUniformMatrix4fv(currentShader->GetUniform("modelMatrix"), 1, GL_FALSE, glm::value_ptr(obj->GetModelTransformation()));
			glUniformMatrix4fv(currentShader->GetUniform("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(currentShader->GetUniform("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
			glUniform1f(currentShader->GetUniform("morphBlendAlpha"), 0.0f);
			glUniform1i(currentShader->GetUniform("diffuseTexture"), 0);


			obj->Render();
		}


		SDL_GL_SwapWindow(window);

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

	// Flushes the vector
	GameObjectList.clear();

	// Delete Context
	//SDL_GL_DeleteContext(gl_Context);

	// Close SDL IMAGE
	IMG_Quit();

	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();

	return 0;
}
