#include "Mesh.h"



Mesh::Mesh()
{
	m_VBO = 0;
	m_EBO = 0;
	m_VAO = 0;
	m_NumberOfVertices = 0;
	m_NumberOfIndices = 0;
}


Mesh::~Mesh()
{
	Destroy();
}

void Mesh::CopyBufferData(Vertex * pVerts, unsigned int numberOfVerts, unsigned int * pIndices, unsigned int numberOfIndices)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, numberOfVerts * sizeof(Vertex), pVerts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(unsigned int), pIndices, GL_STATIC_DRAW);
	
	m_NumberOfIndices = numberOfIndices;
	m_NumberOfVertices = numberOfVerts;

	glBindVertexArray(m_VAO);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,					// attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,					// size
		GL_FLOAT,			// type
		GL_FALSE,			// normalized?
		sizeof(Vertex),		// stride -> sizeof(Vertex)
		(void*)0			// array buffer offset
	);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1, 
		4, 
		GL_FLOAT, 
		GL_FALSE, 
		sizeof(Vertex), 
		(void*)(3 * sizeof(float))
	);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2, 
		2, 
		GL_FLOAT,
		GL_FALSE, 
		sizeof(Vertex), 
		(void*)(7 * sizeof(float))
	);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
		3,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(9 * sizeof(float))
	);
}

void Mesh::Init()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

void Mesh::Render()
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glDrawElements(GL_TRIANGLES, m_NumberOfIndices, GL_UNSIGNED_INT, (void*)0);
}

void Mesh::Destroy()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}


MeshCollection::MeshCollection()
{
}

MeshCollection::~MeshCollection()
{
	destroy();
}

// add new mesh to the collection
void MeshCollection::addMesh(Mesh *pMesh)
{
	m_Meshes.push_back(pMesh);
}

// loop through all meshes in the collection and call render on them
void MeshCollection::render()
{
	for (Mesh *pMesh : m_Meshes)
	{
		pMesh->Render();
	}
}

void MeshCollection::destroy()
{
	// Delete the data in meshes - can't use the standard for loop as you can't modifiy anything instide the loop
	auto iter = m_Meshes.begin();
	// while iter isn't the end of meshes
	while (iter != m_Meshes.end())
	{
		// check iter has memory
		if ((*iter))
		{
			// destroy the mesh
			(*iter)->Destroy();
			// delete the memory
			delete (*iter);
			(*iter) = nullptr;
			// erase the slot in the vector and return new iter
			iter = m_Meshes.erase(iter);
		}
		else
		{
			// if no memory move on
			iter++;
		}
	}
	// final flush of vector
	m_Meshes.clear();
}
