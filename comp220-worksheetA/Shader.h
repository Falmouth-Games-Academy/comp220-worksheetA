#pragma once

// glsl visual studio 2017 to highlight .glsl file

#include <GL\glew.h>
#include <SDL_opengl.h> // Needs to go after glew include

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

std::string ReadShaderFile(std::string path);
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
