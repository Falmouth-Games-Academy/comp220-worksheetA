#pragma once

#include <sstream>
#include <fstream>
#include <iostream>

#include <array>
#include <vector>
#include <map>

#include "IComponent.h"
#include "GLUtils.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

///<summary>
/// Holds mesh functionality
///</summary>
class Model : public IComponent
{
public:
	Model() { componentFlags = GLU::operator|(ComponentFlags::MESH, ComponentFlags::RENDERER); };
	~Model() {};

	void Init(const std::vector<GLfloat>& inVertices, const GLuint& inProgram);
	void Render();
	
protected:
	GLuint vertexArray = -1;
	GLuint vertexBuffer = -1;
	std::vector<GLfloat> vertices;
	GLuint shaderProgram = -1;
private:
};