#pragma once

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <string>
#include <vector>

#include <GL\glew.h>
#include <SDL_opengl.h>

#include "Vertex.h"
#include "Mesh.h"

bool loadModelFromFile(const std::string&, GLuint V30, GLuint B30, unsigned int& numberofVerts, unsigned int& numberIndices);

bool loadMeshFromFile(const std::string & filename, MeshCollection * pMeshCollection);
