/**
Skybox

Handles the setup and loading of skybox textures into a cubemap that can be drawn around the gameworld.
*/

#pragma once
#include <glm\glm.hpp>
#include <SDL.h>
#include <SDL_image.h>

#include "GameObject.h"
#include "shader.h"

class Skybox : public GameObject {
public:
	Skybox();
	~Skybox();

	/**
	Initalise the skybox and create a cubemap.

	@param vertexShader : The filepath to the vertex shader to use.
	@param fragmentShader : The filepath to the fragment shader to use.
	*/
	void Init();

	/**
	Creates and fills the vertex attribute and vertex buffer objects.
	*/
	void SetupBuffers();

	/**
	Load a cubemap from a vector of six images.

	@returns textureID : The ID of the created cubemap texture.
	*/
	unsigned int LoadCubemap(std::vector<std::string> faces);


	unsigned int GetCubemapTexture()
	{
		return cubemapTexture;
	}

	GLuint GetProgramID()
	{
		return programID;
	}

	GLuint GetSkyboxVAO()
	{
		return skyboxVAO;
	}

	void changeSkyboxTexture(int skyboxNum);


	int skyboxNum;

	//File paths for each skybox face
	//The filepaths should be able to be specified in a function to allow different skyboxes to be loaded.
	std::vector<std::string> skyboxFaces;

private:

	ShaderManager shaderManager;

	//ID of the shader to use for this skybox
	GLuint programID;

	unsigned int cubemapTexture;

	GLuint skyboxVAO, skyboxVBO;
};

