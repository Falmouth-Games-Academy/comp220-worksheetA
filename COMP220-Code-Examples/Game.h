#pragma once

#include <iostream>
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <math.h>

#include "Shaders.h"
#include "Vertex.h"
#include "Texture.h"
#include "Model.h"
#include "Mesh.h"
#include "ActorBase.h"
#include "Actor.h"
#include "Camera.h"


class Game
{
public:
	Game();
	~Game();
	int init(int WindowWidth, int WindowHeight);
	void update(double deltaTime);
	void render();
	void exit();

	bool running = true;

private:

	//Game
	SDL_Event ev;
	SDL_Window* window = nullptr;
	SDL_GLContext gl_Context;
	Camera* gameCamera = new Camera();

	//Mouse and Joystick
	bool JOYSTICK = false;
	SDL_Joystick* gGameController;
	const float JOYSTICK_DEAD_ZONE = 0.1f;

	const float MouseSpeed = 4.0f;
	glm::vec2 MouseControls = { 0,0 };



	Actor* tea = nullptr;

	



};

