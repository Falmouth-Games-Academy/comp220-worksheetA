#pragma once
#include "Game.h"
#include "Skybox.h"

class GraphicsApplication : public Game {
public:
	GraphicsApplication();
	~GraphicsApplication();

	void init() override;
	void update() override;
	void render() override;

private:

	Skybox* skybox = new Skybox;

	// model vars
	MeshCollection * skyboxModel;

	MeshCollection * dinoModel;
	MeshCollection * teaPotModel;
	MeshCollection * BunnyModel;
	MeshCollection * GroundModel;
	MeshCollection * TreeModel;
	MeshCollection * GrassModel;
	MeshCollection * FlowersModel;
	MeshCollection * FlowersModel2;
	MeshCollection * MushroomModel;

	// SHADER VARS //

	// uses and send the shader uniform variables across for the chosen object
	void useShader(Shader * currentShader, GameObject * obj);

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
	glm::vec4 Colour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	glm::vec4 ambientMaterialColour = Colour;
	glm::vec4 diffuseMaterialColour = (Colour - 0.2f);
	glm::vec4 specularMaterialColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float specularMaterialPower = 50.0f;

	// Time Properties
	float alphaTime = 0;
	GLint deltaTimeLocation = time.GetDeltaTime();

	// WindShader Properties
	GLfloat windForce = 0.09;
	GLfloat treeWindForce = 0.03;

	float RandomFloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}

};