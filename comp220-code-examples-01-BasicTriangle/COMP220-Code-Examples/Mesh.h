#pragma once

#include "Base.h"
#include "GLUtils.h"

#include <fstream>
#include <sstream>

#include <glm\glm.hpp>

enum MeshFormat
{
	MESH_FORMAT_FBX,
	MESH_FORMAT_OBJ
};

class Mesh
{
public:
	Mesh() {};
	~Mesh() {
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteVertexArrays(1, &vertexArray);
	};

	// Reset all mesh properties
	void Clear()
	{
		normals.clear(); 
		tangents.clear();
		uv.clear();
		uv2.clear();
		uv3.clear();
		uv4.clear();
		vertices.clear();
		vertexColours.clear();
		triangles.clear();
		binormals.clear();
	}

	void LoadFromFile(const std::string& fileName, MeshFormat meshFormat)
	{
		FILE* f = fopen(fileName.c_str(), "r");

		if (f == nullptr)
		{
			printf("Could not open %s\n", fileName);
			return;
		}

		char line[128];
		int fReader = fscanf(f, "%s", line);

		// While we haven't reached the end of the file, read its contents
		while (fReader != EOF)
		{
			// Read normals
			if (strcmp(line, "vn") == 0)
			{
				glm::vec3 normal;
				fscanf(f, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				this->normals.push_back(normal);
			}
			// Read UVs
			else if (strcmp(line, "vt") == 0)
			{
				glm::vec2 uv;
				fscanf(f, "%f %f\n", &uv.x, &uv.y);
				this->uv.push_back(uv);
			}
			// Read vertex
			else if (strcmp(line, "v") == 0)
			{
				glm::vec3 vertex;
				fscanf(f, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				this->vertices.push_back(vertex);
			}
			// Read face
			else if (strcmp(line, "f") == 0)
			{
				unsigned int vertexIndices[3], uvIndices[3], normalIndices[3];
				GLU::vertex vertex0;
				GLU::vertex vertex1;
				GLU::vertex vertex2;

				int vertices = fscanf(f, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndices[0], &uvIndices[0], &normalIndices[0], &vertexIndices[1], &uvIndices[1], &normalIndices[1], &vertexIndices[2], &uvIndices[2], &normalIndices[2]);

				if (vertices != 9)
				{
					printf("Cannot read file format\n");
					return;
				}

				vertex0.x = this->vertices[vertexIndices[0] - 1].x;
				vertex0.y = this->vertices[vertexIndices[0] - 1].y;
				vertex0.z = this->vertices[vertexIndices[0] - 1].z;
				vertex0.tu = this->uv[uvIndices[0] - 1].x;
				vertex0.tv = this->uv[uvIndices[0] - 1].y;
				vertex0.nx = this->normals[normalIndices[0] - 1].x;
				vertex0.ny = this->normals[normalIndices[0] - 1].y;
				vertex0.nz = this->normals[normalIndices[0] - 1].z;

				vertex1.x = this->vertices[vertexIndices[1] - 1].x;
				vertex1.y = this->vertices[vertexIndices[1] - 1].y;
				vertex1.z = this->vertices[vertexIndices[1] - 1].z;
				vertex1.tu = this->uv[uvIndices[1] - 1].x;
				vertex1.tv = this->uv[uvIndices[1] - 1].y;
				vertex1.nx = this->normals[normalIndices[1] - 1].x;
				vertex1.ny = this->normals[normalIndices[1] - 1].y;
				vertex1.nz = this->normals[normalIndices[1] - 1].z;

				vertex2.x = this->vertices[vertexIndices[2] - 1].x;
				vertex2.y = this->vertices[vertexIndices[2] - 1].y;
				vertex2.z = this->vertices[vertexIndices[2] - 1].z;
				vertex2.tu = this->uv[uvIndices[2] - 1].x;
				vertex2.tv = this->uv[uvIndices[2] - 1].y;
				vertex2.nx = this->normals[normalIndices[2] - 1].x;
				vertex2.ny = this->normals[normalIndices[2] - 1].y;
				vertex2.nz = this->normals[normalIndices[2] - 1].z;


				triangles.push_back(_vertices.size());
				this->_vertices.push_back(vertex0);
				triangles.push_back(_vertices.size());
				this->_vertices.push_back(vertex1);
				triangles.push_back(_vertices.size());
				this->_vertices.push_back(vertex2);
			}

			fReader = fscanf(f, "%s", line);
		}

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(unsigned int), &triangles[0], GL_STATIC_DRAW);
	}

	void Init(std::vector<glm::vec3> vertices, std::vector<glm::vec4> vertexColours, std::vector<glm::vec2> uv, std::vector<GLuint> triangles)
	{
		this->vertices = vertices;
		this->vertexColours = vertexColours;
		this->uv = uv;
		this->triangles = triangles;

		CreateElementArrayBuffer();

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);

		int egg = this->triangles.size() * sizeof(unsigned int);

		glGenBuffers(1, &elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->triangles.size() * sizeof(unsigned int), &this->triangles[0], GL_STATIC_DRAW);
	}

	void Init(std::vector<vertex> vertices, std::vector<GLuint> indices)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			_vertices.push_back(vertices[i]);
		}

		triangles = indices;
	
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(unsigned int), &triangles[0], GL_STATIC_DRAW);
	}

	// Vertex positions
	std::vector<glm::vec3> vertices;
	// Vertex normals
	std::vector<glm::vec3> normals;
	// Vertex tangents
	std::vector<glm::vec4> tangents;
	// Triangle indices
	std::vector<GLuint> triangles;
	// Mesh texture coordinates
	std::vector<glm::vec2> uv;
	std::vector<glm::vec2> uv2;
	std::vector<glm::vec2> uv3;
	std::vector<glm::vec2> uv4;
	// Vertex colours
	std::vector<glm::vec4> vertexColours;

	// Vertex array object to deal with vertex formats
	GLuint vertexArray;

	// Vertex buffer identifier
	GLuint vertexBuffer;
	GLuint elementBuffer;

	// Name of mesh
	std::string name;

	// Vector of vertex data to be passed to renderer
	std::vector<GLU::vertex> _vertices;
	
	void CreateElementArrayBuffer()
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			GLU::vertex vert = {
				// Vertex position
				vertices[i].x,
				vertices[i].y,
				vertices[i].z,
				// Vertex colour
				vertexColours[i].r,
				vertexColours[i].g,
				vertexColours[i].b,
				vertexColours[i].a,
				// Vertex UV
				uv[i][0],
				uv[i][1]
			};

			_vertices.push_back(vert);
		}
	}

	void Use()
	{
		// Vertex position
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(vertex),     // stride
			(void*)0            // array buffer offset
		);

		// https://en.cppreference.com/w/cpp/types/offsetof

		// Vertex colours
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(vertex),
			(void*)(3 * sizeof(float))
		);

		// Vertex UV
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(vertex),
			(void*)(7 * sizeof(float))
		);

		// Vertex normals
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(
			3,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(vertex),
			(void*)(10 * sizeof(float))
		);

		glDrawElements(
			GL_TRIANGLES,
			triangles.size(),
			GL_UNSIGNED_INT,
			(void*)0
		);

		glDisableVertexAttribArray(0);
	}

private:
	// Vertex binormals
	std::vector<glm::vec3> binormals;
	
	void CalculateBinormals()
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			binormals.push_back(glm::cross(normals[i], glm::vec3(tangents[i].x, tangents[i].y, tangents[i].z)) * tangents[i].w);
		}
	}
};