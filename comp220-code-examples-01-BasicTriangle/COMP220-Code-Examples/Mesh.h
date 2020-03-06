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
		std::ifstream f(fileName);
		std::string line = "";

		while (std::getline(f, line))
		{
			// If the line describes the object name
			if (line[0] == 'o')
			{
				name = line;
			}
			// Else if line describes a UV coordinate
			else if (line[0] == 'v' && line[1] == 't')
			{
				char* _line = new char[128];
				strcpy(_line, line.c_str() + 3);

				glm::vec2 uv = glm::vec2(0);

				char* p = strtok(_line, " ");

				uv.x = std::atof(p);
				p = strtok(NULL, " ");
				uv.y = std::atof(p);

				// AddUnique(this->uv, uv);
				this->uv.push_back(uv);
			}
			// Else if line describes a vertex
			else if (line[0] == 'v')
			{
				char* _line = new char[128];
				strcpy(_line, line.c_str() + 2);

				char* p = strtok(_line, " ");

				glm::vec3 vert = glm::vec3(0);

				vert.x = std::atof(p);
				p = strtok(NULL, " ");
				vert.y = std::atof(p);
				p = strtok(NULL, " ");
				vert.z = std::atof(p);

				vertices.push_back(vert);

				delete _line;
				_line = nullptr;
			}
			// Else if line describes a triangle
			else if (line[0] == 'f')
			{
				char* _line = new char[128];
				strcpy(_line, line.c_str() + 2);

				char* p = strtok(_line, " ");

				triangles.push_back(std::atoi(p) - 1);
				p = strtok(NULL, " ");
				triangles.push_back(std::atoi(p) - 1);
				p = strtok(NULL, " ");
				triangles.push_back(std::atoi(p) - 1);

				delete _line;
				_line = nullptr;
			}
		}

		for (int i = 0; i < vertices.size(); i++)
		{
			GLU::vertex vert = {
				// Vertex position
				vertices[i].x,
				vertices[i].y,
				vertices[i].z,
				// Vertex colour
				((float)i) / vertices.size(),
				((float)i) / vertices.size(),
				((float)i) / vertices.size(),
				1,
				// Vertex UV
				(i % 4 + 1) / 4.0,
				(i % 4 + 1) / 4.0
			};

			_vertices.push_back(vert);
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

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(vertex),
			(void*)(3 * sizeof(float))
		);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(vertex),
			(void*)(7 * sizeof(float))
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