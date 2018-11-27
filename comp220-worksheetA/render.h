#pragma once

#include <iostream>
#include <chrono> // Get time
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h> // Needs to go after glew include
#include <glm/glm.hpp> // Old header file standard (.hpp)

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.h"
#include "Vertex.h"

class Render {

	public:
		void TestObj(double posX, double posY, double size);
		void Draw();

	private:
		// An array of 3 vectors which represents 3 verticies
		// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
		// {x,y,z,r,g,b,a}
		const Vertex cubeVerticies[8] = {

			// 0, 1, 1 (Top Front left)
			{ 0.0f,1.0f,1.0f,	1.0f,0.0f,1.0f,1.0f }, // 0
			// 0, 1, 0 (Top Back left)
			{ 0.0f,1.0f,0.0f,	0.0f,0.0f,1.0f,1.0f }, // 1

			// 1, 1, 1 (Top Front right)
			{ 1.0f,1.0f,1.0f,	1.0f,0.0f,1.0f,1.0f }, // 2
			// 1, 1, 0 (Top Back right)
			{ 1.0f,1.0f,0.0f,	0.0f,0.0f,1.0f,1.0f }, // 3

			// 0, 0, 1 (Bottom Front left)
			{ 0.0f,0.0f,1.0f,	1.0f,0.0f,1.0f,1.0f }, // 4
			// 0, 0, 0 (Bottom Back left)
			{ 0.0f,0.0f,0.0f,	0.0f,0.0f,1.0f,1.0f }, // 5

			// 1, 0, 1 (Bottom Front right)
			{ 1.0f,0.0f,1.0f,	1.0f,0.0f,1.0f,1.0f }, // 6
			// 1, 0, 0 (Bottom Back right)
			{ 1.0f,0.0f,0.0f,	0.0f,0.0f,1.0f,1.0f } // 7

		};

		// Describes the square (two triangles) anti-clockwise for front facing
		const unsigned int cubeIndices[36] = {
			// Front
			0, 4, 6,
			0, 6, 2,

			// Back
			1, 5, 7,
			7, 3, 1,

			// Top
			2, 3, 1,
			2, 1, 0,

			// Bottom
			5, 4, 6,
			6, 7, 5,

			// Left
			1, 5, 4,
			4, 0, 1,

			// Right
			3, 7, 6,
			6, 2, 3
		};


};
