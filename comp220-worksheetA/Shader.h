#pragma once

#include "Libraries.h"

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

class Shader
{
public:
	Shader();
	~Shader();

	GLint GetUniform(std::string name);

	void Use();

	bool Load(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);

private:
	void InitialiseUniforms();
	GLuint ShaderProgramID;
	std::map<std::string, GLint> UniformMap;

};