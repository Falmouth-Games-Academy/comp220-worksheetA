#pragma once

#include <sstream>
#include <fstream>
#include <iostream>

#include <vector>
#include <map>
#include "Components.h"
#include "Texture.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

#define RENDERER_GL_MAJOR_VERSION 3
#define RENDERER_GL_MINOR_VERSION 1
#define RENDERER_DEFAULT_RESOLUTION_X 1280
#define RENDERER_DEFAULT_RESOLUTION_Y 720
#define RENDERER_MAX_SHADER_PROGRAMS 8

#define SHADER_FILES_DIRECTORY "..\\Shader Files\\"

class Renderer
{
public:
	Renderer() {};
	~Renderer();

	int Init(
		const char* windowName,
		int resX = RENDERER_DEFAULT_RESOLUTION_X,
		int resY = RENDERER_DEFAULT_RESOLUTION_Y,
		bool fullscreen = false,
		int glMajorVersion = RENDERER_GL_MAJOR_VERSION,
		int glMinorVersion = RENDERER_GL_MINOR_VERSION,
		bool depthTesting = true,
		bool cullFaces = true
	);	// Initialise an SDL window and Gl context
	
	void ClearScreen(float r, float g, float b, float a, GLbitfield mask = GL_COLOR_BUFFER_BIT);	// Clear screen
	void SwapBuffers();		// Swap buffers

	// Setters for private variables

	// Getters for private variabes
	SDL_Window* GetWindow() { return window; }
	SDL_GLContext* GetGLContext() { return &glContext; }

	// Switch fullscreen mode
	void SetFullscreen(bool fullscreen);
	bool IsFullscreen();

	// Load a shader program ID: search by name for any potential shader files (*.frag, *.vert etc.) and link them
	void LoadProgram(const char* shaderName, const char* directory = SHADER_FILES_DIRECTORY);
	// Load all shaders found within the shader directory
	void LoadAllPrograms(const char* directory = SHADER_FILES_DIRECTORY);
	// Unload shader program by name
	void UnloadProgramByName(std::string programName);
	// Unload shader program by name
	void UnloadProgramById(GLuint id);
	// Unload all programs
	void UnloadAllPrograms();
	// Get program based on name
	GLuint GetProgram(const char* programName) { return loadedPrograms.at(programName); }
	// Render all cameras 


private : 
	SDL_Window* window = nullptr;
	SDL_GLContext glContext = NULL;

	// Returns a shader ID
	GLuint LoadSingleShader(const char* file_path, GLenum shaderType);
	// Returns  shader program ID, takes in all required shaders
	GLuint LinkShaders(std::vector<GLuint> shaderID);

	std::map <std::string, GLuint> loadedPrograms;	// Dictionary of all shader programs loaded
};