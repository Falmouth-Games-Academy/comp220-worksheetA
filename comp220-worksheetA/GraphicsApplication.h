#pragma once
#include "Game.h"

class GraphicsApplication : public Game {
public:
	GraphicsApplication();
	~GraphicsApplication();

	void init() override;
	void update() override;
	void render() override;

private:

	// model vars
	MeshCollection * dinoModel;
	MeshCollection * teaPotModel;
	MeshCollection * BunnyModel;
	MeshCollection * GroundModel;
	MeshCollection * TankModel;
	MeshCollection * GrassModel;

	// SHADER VARS //

	// secene matrix locations
	GLuint modelMatrixUniformLocation;
	GLuint viewMatrixUniformLocation;
	GLuint projectionMatrixUniformLocation;
	glm::mat4 sceneMatrix;

	// Light properties
	glm::vec4 ambientLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 diffuseLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 specularLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightDirection = glm::vec3(0.0f, 0.0f, 1.0f);

	// Material Properties
	glm::vec4 Colour = glm::vec4(1.0f, 0.5f, 0.6f, 1.0f);
	glm::vec4 ambientMaterialColour = Colour;
	glm::vec4 diffuseMaterialColour = (Colour - 0.2f);
	glm::vec4 specularMaterialColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float specularMaterialPower = 50.0f;

	// Time Properties
	float alphaTime = 0;
	GLint deltaTimeLocation = time.GetDeltaTime();

};