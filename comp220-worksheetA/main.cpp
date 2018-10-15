#include <iostream>
#include <chrono> // Get time
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h> // Needs to go after glew include
#include <glm/glm.hpp> // Old header file standard (.hpp)

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Vertex.h"

typedef std::chrono::high_resolution_clock Time;

int main(int argc, char ** argsv)
{
	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	//https://wiki.libsdl.org/SDL_Init
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Display an error message box
		//https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return 1;
	}

	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);
		//Close the SDL Library
		//https://wiki.libsdl.org/SDL_Quit
		SDL_Quit();
		return 1;
	}

	// Request 3.2 Core OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GLContext gl_Context = SDL_GL_CreateContext(window);
	if (gl_Context == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreatedContext Failed", SDL_GetError(), NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	// Init GLEW
	glewExperimental = GL_TRUE;
	// Make sure GLEW is being initalised correctly
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		// Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", (char*)glewGetErrorString(err), NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An array of 3 vectors which represents 3 verticies
	// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
	// {x,y,z,r,g,b,a}
	static const Vertex v[] = {
		/*
		// Front
		{ -0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,1.0f },
		{ 0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,1.0f },
		{ 0.5f,0.5f,0.0f,0.0f,0.0f,1.0f,1.0f },
		{ -0.5f,0.5f,0.0f,0.0f,0.0f,1.0f,1.0f },

		// Top
		{ 0.5f,0.5f,-0.5f,0.0f,0.0f,1.0f,1.0f },
		{ -0.5f,0.5f,-0.5f,0.0f,0.0f,1.0f,1.0f },
		*/

		// 0, 1, 1 (Top Front left)
		{ 0.0f,1.0f,1.0f,	1.0f,0.0f,1.0f,1.0f }, // 0
		// 0, 1, 0 (Top Back left)
		{ 0.0f,1.0f,0.0f,	0.0f,0.0f,1.0f,1.0f }, // 1

		// 1, 1, 1 (Top Front right)
		{ 1.0f,1.0f,1.0f,	1.0f,0.0f,1.0f,1.0f }, // 2
		// 1, 1, 0 (Top Back right)
		{ 1.0f,1.0f,0.0f,	0.0f,0.0f,1.0f,1.0f }, // 3

		// 0, 0, 1 (Bottom Front left)
		{ 0.0f,0.0f,1.0f,	1.0f,0.0f,1.0f,1.0f }, // 4
		// 0, 0, 0 (Bottom Back left)
		{ 0.0f,0.0f,0.0f,	0.0f,0.0f,1.0f,1.0f }, // 5

		// 1, 0, 1 (Bottom Front right)
		{ 1.0f,0.0f,1.0f,	1.0f,0.0f,1.0f,1.0f }, // 6
		// 1, 0, 0 (Bottom Back right)
		{ 1.0f,0.0f,0.0f,	0.0f,0.0f,1.0f,1.0f }, // 7

	};

	// Describes the square (two triangles) anti-clockwise for front facing
	static const unsigned int indices[] =
	{
		// Front
		//0,1,2,
		//2,0,3,

		// Top
		2, 3, 1,
		2, 1, 0,

		// Front
		0, 4, 6

	};

	//This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Gives our vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(Vertex), v, GL_STATIC_DRAW);

	GLuint elementBuffer;
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer); // Binding an element buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 9 * sizeof(int), indices, GL_STATIC_DRAW); // GL_STATIC_DRAW as doesn't need to be updated every frame

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
	glm::vec3 cameraPosition = glm::vec3(2.0f, 2.0f, -2.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

	glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), ((float)800 / 600), 0.1f, 100.0f);

	GLuint programID = LoadShaders("vert.glsl", "frag.glsl"); // Normally would name the var what it does

	//glm::vec3 position = glm::vec3(0.0f, 0.5f, 0.0f);

	//glm::mat4 modelMatrix = glm::translate(position);

	// Get location from .glsl
	GLuint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix"); // Same name as in vert.glsl

	GLuint viewMatrixLocation = glGetUniformLocation(programID, "viewMatrix");

	GLuint projectionMatrixLocation = glGetUniformLocation(programID, "projectionMatrix");

	// Inspired by http://gameprogrammingpatterns.com/game-loop.html
	Time::time_point previous = Time::now();
	double lag = 0.0;
	
	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;
	while (running)
	{
		// Keep track of processing time
		Time::time_point current = Time::now();
		double elapsed = std::chrono::duration<double, std::nano>(current - previous).count();
		Time::time_point previous = current;
		lag += elapsed;

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

		// Update game and draw with OpenGL
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID); // for shaders

		// Send matrix to vert.glsl
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		// Change colour
		GLuint location
			= glGetUniformLocation(programID, "myColour");
		glUniform3f(location, 0, 1, 0);

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glVertexAttribPointer(
			0,			// Attribute 0. No particular reason for 0, but must match the Layout in the shader
			3,			// Size
			GL_FLOAT,	// Type
			GL_FALSE,	// Normalised?
			sizeof(Vertex),			// Stride
			(void*)0	// Array buffer offset
		);
		// Draw the triangle
		//glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
		glDisableVertexAttribArray(0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)(3 * sizeof(float))
		);

		SDL_GL_SwapWindow(window);
	}

	// Delete program
	glDeleteProgram(programID);

	// Delete buffers
	glDeleteBuffers(1, &vertexbuffer);
	
	// Delete vertex arrays
	glDeleteVertexArrays(1, &VertexArrayID);

	// Delete Context
	SDL_GL_DeleteContext(gl_Context);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();

	return 0;
}
