#pragma once

#include "Libraries.h"
#include "Shader.h"

class Skybox
{
public:
	Skybox();
	~Skybox();

	GLuint GetSkyboxVAO()
	{
		return skyboxVAO;
	};

	Shader* GetShader()
	{
		return skyboxShader;
	};

	unsigned int GetCubemapTexture()
	{
		return cubemapTexture;
	};

	void RenderSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void InitialiseSkybox();

private:
	glm::mat4 view;

	GLuint skyboxVAO;
	GLuint skyboxVBO;

	Shader* skyboxShader;
		
	unsigned int cubemapTexture;
	unsigned int LoadCubemap(std::vector<std::string> faces);
};

