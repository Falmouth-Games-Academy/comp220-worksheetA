#pragma once
#include <SDL_opengl.h>
#include <vector>

#include "Transform.h"
#include "Vertex.h"

struct MeshComponent
{
	float translationMatrix[16], rotationMatrix[16], scaleMatrix[16];
	float modelMatrix[16];
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;
	unsigned int m_numberOfVerts;
	unsigned int m_numberOfIndices;
	std::vector<Vertex> m_verts;
	std::vector<unsigned int> m_indices;


	void Init(GLuint _VBO, GLuint _EBO, GLuint _VAO, unsigned int _verts, unsigned int _indices)
	{
		m_VBO = _VBO;
		m_EBO = _EBO;
		m_VAO = _VAO;
		m_numberOfVerts = _verts;
		m_numberOfIndices = _indices;
	}
	void Init(MeshComponent mc)
	{
		m_VBO = mc.m_VBO;
		m_VAO = mc.m_VAO;
		m_EBO = mc.m_EBO;
		m_numberOfVerts = mc.m_numberOfVerts;
		m_numberOfIndices = mc.m_numberOfIndices;
	}
};