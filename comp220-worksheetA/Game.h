#pragma once
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Globals.h"
#include "Graphics.h"
#include "GameObject.h"
#include "shader.h"
#include "camera.h"
#include "Vertex.h"
#include "Input.h"
#include "Controls.h"

class Game
{
public:

	Game();
	virtual ~Game();

	// main functions to get the game running
	virtual void init();
	void gameLoop();
	void gameCleanUp();
	
	SDL_Window* window;

	Input input;

	SDL_GLContext gl_Context;
	
	GLuint location;

	std::vector<GameObject *> objs;
	GameObject gameObject;

	ShaderManager shaderManager;

	// This will Identify out vertex buffer
	GLuint vertexbuffer;
	GLuint VertexArrayID;

	// element buffer
	GLuint elementbuffer;

	Controls controls;

	// Camera to view the screen
	Camera camera;

	// mouse x and y vars
	int mouseX = 0;
	int mouseY = 0;
	
	// model and texture vars
	MeshCollection * dinoModel;
	MeshCollection * teaPotModel;
	GLuint TextureID;

private:

	SDL_DisplayMode DM;

	// the different initialises
	void initSDL();
	void initWindow();
	void initOpenGL();
	void initGlew();
	void initScene();

	void CheckEvents();
	void update();
	void render();

	// time vars
	float lastTime;
	float tickTime;
	float deltaTime;
	float fps;

	// fullscreen toggle boolean and function
	bool fullScreenToggle = false;
	void fullScreen();

	// Gameloop running boolean
	bool running = true;

	// secene matrix locations
	GLuint modelMatrixUniformLocation;
	GLuint viewMatrixUniformLocation;
	GLuint projectionMatrixUniformLocation;
	GLint baseTextureLocation;

	glm::mat4 sceneMatrix;


	//Light properties
	glm::vec4 ambientLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 diffuseLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 specularLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightDirection = glm::vec3(0.0f, 0.0f, 1.0f);


	//Material Properties
	glm::vec4 ambientMaterialColour = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f);
	glm::vec4 diffuseMaterialColour = glm::vec4(0.0f, 0.4f, 0.0f, 1.0f);
	glm::vec4 specularMaterialColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float specularMaterialPower = 50.0f;

	// stuff
	GLint ambientLightColourLocation;
	GLint diffuseLightColourLocation;
	GLint specularLightColourLocation;

	GLint ambientMaterialColourLocation;
	GLint diffuseMaterialColourLocation;
	GLint specularMaterialColourLocation;
	GLint specularMaterialPowerLocation;

	GLint lightDirectionLocation;
	GLint cameraPositionLocation;


protected:

};