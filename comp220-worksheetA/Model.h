#pragma once

#include "Libraries.h"
#include "Mesh.h"

bool loadModelFromFile(const std::string& filename, GLuint VBO, GLuint EBO, unsigned int& numberOfVertices, unsigned int& numberOfIndices);

bool loadMeshesFromFile(const std::string& filename, MeshCollection * meshes);