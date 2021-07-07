#include "Material.h"

Material::~Material()
{
	glDeleteTextures(1, &albedoId);
	glDeleteTextures(1, &normalId);
	glDeleteTextures(1, &specularId);
	glDeleteTextures(1, &glossId);

	glDeleteProgram(this->shaderProgram);
}

void Material::Init(GLuint shaderProgram, GLuint albedo, GLuint normal, GLuint specular, GLuint gloss)
{
	this->shaderProgram = shaderProgram;
	this->albedoId = albedo;
	this->normalId = normal;
	this->specularId = specular;
	this->glossId = gloss;

	modelMatrixLocation = glGetUniformLocation(shaderProgram, "model");
	viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
	projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");

	if (albedo != NOTEXTURE)
		albedoLocation = glGetUniformLocation(shaderProgram, "albedo");
	if (normal != NOTEXTURE)
		normalLocation = glGetUniformLocation(shaderProgram, "normal");
	if (specular != NOTEXTURE)
		specularLocation = glGetUniformLocation(shaderProgram, "specular");
	if (gloss != NOTEXTURE)
		glossLocation = glGetUniformLocation(shaderProgram, "gloss");

	ambientLightColorLocation = glGetUniformLocation(shaderProgram, "ambientLightColor");
	ambientMaterialColorLocation = glGetUniformLocation(shaderProgram, "ambientMaterialColor");
	cameraPositionLocation = glGetUniformLocation(shaderProgram, "cameraPosition");
}

// TODO: add camera location for updating specular lighting
void Material::Use(glm::mat4 translationMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition)
{
	// Use albedo texture
	if (albedoId != NOTEXTURE)
	{
		glActiveTexture(GL_TEXTURE0); // This zero...
		glBindTexture(GL_TEXTURE_2D, albedoId);
		glUniform1i(albedoLocation, 0); // Should match this zero
	}
	// Use rest of textures
	if (normalId != NOTEXTURE)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalId);
		glUniform1i(normalLocation, 1);
	}

	// Use shader
	glUseProgram(shaderProgram);

	glm::vec4 ambientLightColor = glm::vec4(1, 1, 1, 1);
	glm::vec4 ambientMaterialColor = glm::vec4(0.2f, 0.2f, 0.2f, 1);

	glUniform4fv(ambientLightColorLocation, 1, glm::value_ptr(ambientLightColor));
	glUniform4fv(ambientMaterialColorLocation, 1, glm::value_ptr(ambientMaterialColor));
	glUniform3fv(cameraPositionLocation, 1, glm::value_ptr(cameraPosition));

	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}
