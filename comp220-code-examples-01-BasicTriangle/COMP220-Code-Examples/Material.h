#pragma once

#include "Base.h"
#include "GLUtils.h"

///<summary>
/// Container for shader programs and textures
/// Has functionality to send data to shader programs
///</summary>
class Material
{
public:
	Material() {};
	~Material() {};

	GLuint shaderProgram;
	
//=========TEXTURES=========//
	// Albedo texture
	GLuint albedo;
	// Normal texture
	GLuint normal;
	// Specular texture
	GLuint specular;
	// Gloss texture
	GLuint gloss;
};