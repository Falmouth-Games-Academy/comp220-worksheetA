#pragma once

#include <GL\glew.h>
#include <SDL_opengl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
using namespace glm;

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
