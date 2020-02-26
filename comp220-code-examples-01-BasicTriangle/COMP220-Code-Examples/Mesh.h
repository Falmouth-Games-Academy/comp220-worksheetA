#pragma once

#include "Base.h"

#include <glm\glm.hpp>

class Mesh
{
public:
	Mesh() {};
	~Mesh() {};

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

	// Vertex normals
	std::vector<glm::vec3> normals;
	// Vertex tangents
	std::vector<glm::vec4> tangents;
	// Mesh texture coordinates
	std::vector<glm::vec2> uv;
	std::vector<glm::vec2> uv2;
	std::vector<glm::vec2> uv3;
	std::vector<glm::vec2> uv4;
	// Vertex positions
	std::vector<glm::vec3> vertices;
	// Vertex colours
	std::vector<glm::vec4> vertexColours;
	// Triangle indices
	std::vector<glm::uvec3> triangles;

private:
	// Vertex binormals
	std::vector<glm::vec3> binormals;
	
	void CalculateBinormals()
	{
		for (int i = 0; i < vertices.size; i++)
		{
			binormals.push_back(glm::cross(normals[i], glm::vec3(tangents[i].x, tangents[i].y, tangents[i].z)) * tangents[i].w);
		}
	}
};