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
	~Material() 
	{
		glDeleteTextures(1, &albedoId);
		glDeleteTextures(1, &normalId);
		glDeleteTextures(1, &specularId);
		glDeleteTextures(1, &glossId);

		glDeleteProgram(this->shaderProgram);
	};

	void Init(GLuint shaderProgram, GLuint albedo = NOTEXTURE, GLuint normal = NOTEXTURE, GLuint specular = NOTEXTURE, GLuint gloss = NOTEXTURE)
	{
		this->shaderProgram = shaderProgram;
		this->albedoId = albedo;
		this->normalId = normal;
		this->specularId = specular;
		this->glossId = gloss;

		modelMatrixLocation = glGetUniformLocation(shaderProgram, "model");
		viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
		projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
		
		if(albedo != NOTEXTURE)
			albedoLocation = glGetUniformLocation(shaderProgram, "albedo");
		if (normal != NOTEXTURE)
			normalLocation = glGetUniformLocation(shaderProgram, "normal");
		if (specular != NOTEXTURE)
			specularLocation = glGetUniformLocation(shaderProgram, "specular");
		if (gloss != NOTEXTURE)
			glossLocation = glGetUniformLocation(shaderProgram, "gloss");
	}

	void Use(glm::mat4 translationMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
	{
		// Use albedo texture
		if (albedoId != NOTEXTURE)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, albedoId);
			glUniform1i(albedoLocation, 0);
		}
		// Use rest of textures

		// Use shader
		glUseProgram(shaderProgram);

		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(translationMatrix));
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	}

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
//======MATRIX LOCATIONS====//
	GLuint modelMatrixLocation;
	GLuint viewMatrixLocation;
	GLuint projectionMatrixLocation;
};