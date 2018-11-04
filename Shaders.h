#pragma once

#include <SDL.h> //load the sdl Library
#include<glew.h> // load the openGl exentsion Wrangler
#include <SDL_opengl.h>//load open Gl
using namespace std;

#include <string>
#include <vector>
#include <fstream>

class MyShaderCreator
{
public:
	static GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	static void CompileVertexShaders(const char *path, std::string code, GLuint id, GLint result, int logLength);
	static void CompileFragmentShaders(const char *path, std::string code, GLuint id, GLint result, int logLength);
	static void ShaderProgramLinker(GLuint programID, GLuint vertID, GLuint fragID, GLint result, int logLength);
};



