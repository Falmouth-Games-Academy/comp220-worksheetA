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

#include "Texture.h"
#include "Model.h"

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

	// Initalise SDL IMAGE! -- add error checking
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

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
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

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
	/*
	static const Vertex v[] = {

		{ -0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f },
		{ 0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f },
		{ 0.5f,0.5f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f },
		{ -0.5f,0.5f,0.0f,0.0f,0.0f,1.0f,1.0f ,0.0f,1.0f }

	};

	// Describes the square (two triangles) anti-clockwise for front facing
	static const unsigned int indices[] =
	{
		0,1,2,
		2,0,3
	};
	*/
	//glEnable(GL_DEPTH_TEST);

	//This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Gives our vertices to OpenGL
	//glBufferData(GL_ARRAY_BUFFER, 8*sizeof(Vertex), v, GL_STATIC_DRAW);

	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer); // Binding an element buffer
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // GL_STATIC_DRAW as doesn't need to be updated every frame

	// Cube.nff test
	unsigned int numberOfVerts = 0;
	unsigned int numberofInfices = 0;
	loadModelFromFile("Tank1.FBX", vertexbuffer, elementbuffer, numberOfVerts, numberofInfices);

	// Load in a texture from a file
	GLuint textureID = loadTextureFromFile("Crate.jpg");

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

	GLuint programID = LoadShaders("textureVert.glsl", "textureFrag.glsl"); // Normally would name the var what it does

	//glm::vec3 position = glm::vec3(0.0f, 0.5f, 0.0f);

	//glm::mat4 modelMatrix = glm::translate(position);

	// Get location from .glsl
	static const GLfloat fragColour[] = { 0.0f,1.0f,0.0f,1.0f };

	GLuint fragColourLocation = glGetUniformLocation(programID, "fragColour");
	GLuint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix"); // Same name as in vert.glsl
	GLuint viewMatrixLocation = glGetUniformLocation(programID, "viewMatrix");
	GLuint projectionMatrixLocation = glGetUniformLocation(programID, "projectionMatrix");
	GLuint textureLocation = glGetUniformLocation(programID, "baseTexture");

	// Inspired by http://gameprogrammingpatterns.com/game-loop.html
	Time::time_point previous = Time::now();
	double lag = 0.0;
	bool fullScreen = false;
	
	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;
	while (running)
	{
		// Clear depth buffer
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

		// Update game and draw with OpenGL
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Active, bind, send (glUniform1i)
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		glUseProgram(programID); // for shaders
		glUniform4fv(fragColourLocation, 1, fragColour);

		// Send matrix to vert.glsl
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		glUniform1i(textureLocation, 0);

		// Change colour
		//GLuint location
		//	= glGetUniformLocation(programID, "myColour");
		//glUniform3f(location, 0, 1, 0);

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
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
		//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, (void*)0);
		//glDisableVertexAttribArray(0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));


		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));

		// Draw the triangle !
		glDrawElements(GL_TRIANGLES, numberofInfices, GL_UNSIGNED_INT, (void*)0);
		SDL_GL_SwapWindow(window);

		/*
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
		*/
	}

	// Delete program
	glDeleteProgram(programID);

	// Delete buffers
	glDeleteBuffers(1, &vertexbuffer);
	
	// Delete vertex arrays
	glDeleteVertexArrays(1, &VertexArrayID);

	// Delete textures
	glDeleteTextures(1, &textureID);

	// Delete Context
	SDL_GL_DeleteContext(gl_Context);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);

	// Close SDL IMAGE
	IMG_Quit();

	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();

	return 0;
}
