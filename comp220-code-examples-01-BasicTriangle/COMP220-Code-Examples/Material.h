#pragma once

#include "Base.h"
#include "GLUtils.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

///<summary>
/// Container for shader programs and textures
/// Has functionality to send data to shader programs
///</summary>
class Material
{
public:
	Material() {};
	~Material();

	void Init(GLuint shaderProgram, GLuint albedo = NOTEXTURE, GLuint normal = NOTEXTURE, GLuint specular = NOTEXTURE, GLuint gloss = NOTEXTURE);
	void Use(glm::mat4 translationMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	GLuint shaderProgram;
	
	// Used to check whether a texture was assigned
	static const GLuint NOTEXTURE = 99999;

//=========TEXTURES=========//
	// Albedo texture id
	GLuint albedoId;
	// Albedo texture location
	GLuint albedoLocation;
	// Normal texture id
	GLuint normalId;
	// Normal texture location
	GLuint normalLocation;
	// Specular texture id
	GLuint specularId;
	// Specular texture location
	GLuint specularLocation;
	// Gloss texture id
	GLuint glossId;
	// GLoss texture location
	GLuint glossLocation;
	//
	GLuint ambientLightColorLocation;
	GLuint ambientMaterialColorLocation;
//======MATRIX LOCATIONS====//
	GLuint modelMatrixLocation;
	GLuint viewMatrixLocation;
	GLuint projectionMatrixLocation;
};