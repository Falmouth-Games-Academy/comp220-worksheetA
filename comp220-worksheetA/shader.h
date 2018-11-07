#pragma once

#include <map>
#include <string>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class ShaderManager {
public:
	ShaderManager();
	~ShaderManager();

	GLuint LoadShaders(std::string ShaderName, const char * vertex_file_path, const char * fragment_file_path);

	GLuint GetShader(std::string name);

private:
	std::map<std::string, GLuint> ShaderDict;

};

