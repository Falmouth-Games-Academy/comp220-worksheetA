#include <iostream>
#include <vector>
#include <array>

#include <sstream>
#include <fstream>

#include "Application.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

int main(int argc, char ** argsv)
{
	////Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	////https://wiki.libsdl.org/SDL_Init
	//if (SDL_Init(SDL_INIT_VIDEO) < 0)
	//{
	//	//Display an error message box
	//	//https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
	//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
	//	return 1;
	//}

	////Create a window, note we have to free the pointer returned using the DestroyWindow Function
	////https://wiki.libsdl.org/SDL_CreateWindow
	//SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);
	////Checks to see if the window has been created, the pointer will have a value of some kind
	//if (window == nullptr)
	//{
	//	//Show error
	//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);
	//	//Close the SDL Library
	//	//https://wiki.libsdl.org/SDL_Quit
	//	SDL_Quit();
	//	return 1;
	//}

	//SDL_GLContext glContext = SDL_GL_CreateContext(window);

	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	////Initialize GLEW
	//glewExperimental = GL_TRUE;
	//GLenum glewError = glewInit();
	//if (glewError != GLEW_OK)
	//{
	//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unable to initialise GLEW", (char*)glewGetErrorString(glewError), NULL);
	//}

	////Create a Vertex Array object to deal with vertex formats
	//GLuint vertexArray;
	//glGenVertexArrays(1, &vertexArray);
	//glBindVertexArray(vertexArray);


	//// An array of 3 vectors which represents 3 vertices
	//static const GLfloat vertices[] = {
	//   -1.0f, -1.0f, 0.0f,
	//   1.0f, -1.0f, 0.0f,
	//   0.0f,  1.0f, 0.0f,
	//};


	//// This will identify our vertex buffer
	//GLuint vertexBuffer;
	//// Generate 1 buffer, put the resulting identifier in vertexbuffer
	//glGenBuffers(1, &vertexBuffer);
	//// The following commands will talk about our 'vertexbuffer' buffer
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//// Give our vertices to OpenGL.
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//// Create and compile our GLSL program from the shaders
	//GLuint programID = LoadShaders("BasicShader.vert",
	//	"BasicShader.frag");

	//GLuint modelMatrixLocation = glGetUniformLocation(programID, "model");
	//GLuint viewMatrixLocation = glGetUniformLocation(programID, "viewMatrix");
	//GLuint projectionMatrixLocation = glGetUniformLocation(programID, "projectionMatrix");

	//glm::vec3 position = glm::vec3(0.5, 0.0, 0.0);
	//glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	//glm::mat4 translationMatrix = glm::mat4(1.0f);
	//glm::mat4 rotationMatrix = glm::mat4(1.0f);
	//glm::mat4 scaleMatrix = glm::mat4(1.0f);
	//translationMatrix = glm::translate(translationMatrix, position);

	//// Set up camera view matrix
	//glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -10.0f);
	//glm::vec3 cameraTarget = glm::vec3(position);
	//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	//glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

	//// Set up perspective matrix
	//glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.01f, 100.0f);

	////Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	//bool running = true;
	////SDL Event structure, this will be checked in the while loop
	//SDL_Event ev;

	//int l = 0;
	//while (running)
	//{
	//	//Poll for the events which have happened in this frame
	//	//https://wiki.libsdl.org/SDL_PollEvent
	//	while (SDL_PollEvent(&ev))
	//	{
	//		//Switch case for every message we are intereted in
	//		switch (ev.type)
	//		{
	//			//QUIT Message, usually called when the window has been closed
	//		case SDL_QUIT:
	//			running = false;
	//			break;
	//			//KEYDOWN Message, called when a key has been pressed down
	//		case SDL_KEYDOWN:
	//			//Check the actual key code of the key that has been pressed
	//			switch (ev.key.keysym.sym)
	//			{
	//				//Escape key
	//			case SDLK_ESCAPE:
	//				running = false;
	//				break;
	//			case SDLK_LEFT:
	//				translationMatrix = glm::translate(translationMatrix, glm::vec3(1, 0, 0));
	//				break;
	//			case SDLK_RIGHT:
	//				translationMatrix = glm::translate(translationMatrix, glm::vec3(-1, 0, 0));
	//				break;
	//			case SDLK_UP:
	//				translationMatrix = glm::translate(translationMatrix, glm::vec3(0, 1, 0));
	//				break;
	//			case SDLK_DOWN:
	//				translationMatrix = glm::translate(translationMatrix, glm::vec3(0, -1, 0));
	//				break;
	//			}
	//		}
	//	}

	//	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	glUseProgram(programID);

	//	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(translationMatrix));
	//	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));
	//	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection));

	//	glEnableVertexAttribArray(0);
	//	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//	glVertexAttribPointer(
	//		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	//		3,                  // size
	//		GL_FLOAT,           // type
	//		GL_FALSE,           // normalized?
	//		0,                  // stride
	//		(void*)0            // array buffer offset
	//	);
	//	// Draw the triangle !
	//	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	//	glDisableVertexAttribArray(0);

	//	SDL_GL_SwapWindow(window);
	//}


	//glDeleteProgram(programID);
	//glDeleteBuffers(1, &vertexBuffer);
	//glDeleteVertexArrays(1, &vertexArray);
	//SDL_GL_DeleteContext(glContext);
	////Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	////https://wiki.libsdl.org/SDL_DestroyWindow
	//SDL_DestroyWindow(window);
	////https://wiki.libsdl.org/SDL_Quit
	//SDL_Quit();

	//====================MODULARISATION======================
	
	FluidGL::Application* application = new FluidGL::Application();
	application->Init("FluidGL", 1280, 720, false);
	application->Run();

	return 0;
}