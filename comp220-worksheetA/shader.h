#pragma once

#include <map>
#include <string>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class Shader {
public:
	Shader();
	~Shader();

	void setProgramID(GLuint id)
	{
		programID = id;
	};

	GLuint getProgramID()
	{
		return programID;
	};

	void discoverUniforms();

	GLint getUniformLocation(std::string name)
	{
		// Find function in map
		GLint location = UniformLocationDict[name];
		return location;
	};

private:
	GLuint programID;
	std::map<std::string, GLint> UniformLocationDict;

};

class ShaderManager {
public:
	ShaderManager();
	~ShaderManager();

	//GLuint LoadShaders(std::string ShaderName, const char * vertex_file_path, const char * fragment_file_path);
	void LoadShaders(std::string ShaderName, const char * vertex_file_path, const char * fragment_file_path);

	//GLuint GetShader(std::string name);
	Shader * GetShader(std::string name);

	void destroy()
	{
		auto shaderiter = ShaderDict.begin();
		while (shaderiter != ShaderDict.end())
		{
			glDeleteProgram((*shaderiter).second.getProgramID());
			shaderiter++;
		};
	};

private:
	//std::map<std::string, GLuint> ShaderDict;
	std::map<std::string, Shader> ShaderDict;

};

