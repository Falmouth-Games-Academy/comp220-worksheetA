#pragma once


#include<assimp\Importer.hpp>
#include<assimp\scene.h>
#include<assimp\postprocess.h>


#include<string>
#include "GL/glew.h"
#include<SDL_opengl.h>

#include<vector>
#include"vertex.h"






bool loadModelFromFile(const std::string& filename, GLuint VBO, GLuint EBOP, unsigned int& numberOfVerts, unsigned int& numberOfIndices);


