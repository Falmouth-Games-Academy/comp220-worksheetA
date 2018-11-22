#pragma once

#include <GL\glew.h>
#include <SDL_opengl.h>
#include <vector>
#include "Vertex.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void copyBufferData(Vertex *pVerts, unsigned int numberOfVerts, unsigned int *pIndices, unsigned int numberOfIndices);

	void init();
	void destroy();

	void render();

private:
	GLuint m_VBO;
	GLuint m_EBO;

	unsigned int m_NumberOfVertices;
	unsigned int m_NumberOfIndices;

	GLuint m_VAO; // Vertex array object
};

