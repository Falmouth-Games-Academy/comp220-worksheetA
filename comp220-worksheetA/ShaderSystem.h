#pragma once
#include<GL\glew.h>
#include<SDL_opengl.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>

#include "System.h"
#include "Texture.h"
#include "Coordinator.h"
#include "MeshCollectionComponent.h"

class ShaderSystem : public System
{
public:
	void Init();
	void Delete();
	void Bind();
	bool Load(const std::string& s_vertFileName, const std::string& s_fragShaderName);
	GLuint LoadShaders(const char* c_vertexFilePath, const char* c_fragmentFilePath);
	GLint GetUniform(const std::string& s_uniformName);
	void Update(std::unique_ptr<Coordinator> &coord, float view[16], float projection[16], GLuint v, GLuint p);

private:
	bool CheckShader(GLuint shaderID, GLint results, int logLength);
	bool CheckShader(GLuint shaderID, GLenum info, GLint results, int logLength);
	
	void RetrieveUniforms();
	void CompileShader(GLuint shaderID, std::string shaderCode);
	void DetachShaders(GLuint programID, std::vector<GLuint> shaderIDs);
	void DeleteShaders(std::vector<GLuint> shaderIDs);
	
	GLuint CreateProgram(std::vector<GLuint> shaderIDs);
	std::string ReadStream(const char* _c_filePath);

	GLuint shaderProgramID;
	std::map<std::string, GLint> Uniforms;
protected:

};