#pragma once

#include "Libraries.h"
#include "Vertex.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void CopyMeshData(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

	void Init();
	void Render();
	void Destroy();

private:
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;

	unsigned int m_NumberOfVertices;
	unsigned int m_NumberOfIndices;
};

class MeshCollection
{
public:
	MeshCollection();
	~MeshCollection();

	void addMesh(Mesh *pMesh);

	void render();
	void destroy();
private:
	std::vector<Mesh*> m_Meshes;
};

