#pragma once
#include <glm\glm.hpp>
#include <SDL.h>
#include <SDL_image.h>

#include "GameObject.h"
#include "shader.h"
#include "Globals.h"

class Skybox : public GameObject {
public:
	Skybox();
	~Skybox();

	void Init();

	// Creates and fills the vertex attribute and vertex buffer objects.

	void SetupBuffers();

	// Load a cubemap from a vector of six images.
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

	// The initial skybox texture number
	int skyboxNum = globals::skyBoxNum;

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

