#include "Actor.h"



Actor::Actor()
{
	programID = LoadShaders("blinnPhongVert.glsl", "blinnPhongFrag.glsl");
	loadMeshFromFile("utah-teapot.fbx", teapotMesh);


	//Get the uniforms from the shader
	modelMatrixUniformLocation = glGetUniformLocation(programID, "modelMatrix");
	viewMatrixUniformLocation = glGetUniformLocation(programID, "viewMatrix");
	projectionMatrixUniformLocation = glGetUniformLocation(programID, "projectionMatrix");
	baseTextureLocation = glGetUniformLocation(programID, "baseTexture");

	ambientLightColourLocation = glGetUniformLocation(programID, "ambientLightColour");
	diffuseLightColourLocation = glGetUniformLocation(programID, "diffuseLightColour");
	specularLightColourLocation = glGetUniformLocation(programID, "specularLightColour");

	lightDirectionLocation = glGetUniformLocation(programID, "lightDirection");
	cameraPositionLocation = glGetUniformLocation(programID, "cameraPosition");


	ambientMaterialColourLocation = glGetUniformLocation(programID, "ambientMaterialColour");
	diffuseMaterialColourLocation = glGetUniformLocation(programID, "diffuseMaterialColour");
	specularMaterialColourLocation = glGetUniformLocation(programID, "specularMaterialColour");
	specularMaterialPowerLocation = glGetUniformLocation(programID, "specularMaterialPower");
}


Actor::~Actor()
{
	glDeleteTextures(1, &textureID);
	glDeleteProgram(programID);
}

void Actor::render(Camera* cam)
{
	glUseProgram(programID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//send the uniforms across
	glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix()));
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(cam->viewMatrix()));
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(cam->projectionMatrix));
	glUniform1i(baseTextureLocation, 0);

	glUniform4fv(ambientMaterialColourLocation, 1, glm::value_ptr(ambientMaterialColour));
	glUniform4fv(diffuseMaterialColourLocation, 1, glm::value_ptr(diffuseMaterialColour));
	glUniform4fv(specularMaterialColourLocation, 1, glm::value_ptr(specularMaterialColour));

	glUniform4fv(ambientLightColourLocation, 1, glm::value_ptr(ambientLightColour));
	glUniform4fv(diffuseLightColourLocation, 1, glm::value_ptr(diffuseLightColour));
	glUniform4fv(specularLightColourLocation, 1, glm::value_ptr(specularLightColour));
	glUniform1f(specularMaterialPowerLocation, specularMaterialPower);

	glUniform3fv(lightDirectionLocation, 1, glm::value_ptr(lightDirection));
	glUniform3fv(cameraPositionLocation, 1, glm::value_ptr(cam->position));

	teapotMesh->render();
}
