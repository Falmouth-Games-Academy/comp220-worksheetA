#include<iostream>
#include<SDL.h>
#include "GL/glew.h"
#include<SDL_opengl.h>
#include <glm\glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\transform.hpp>
#include<glm\gtc\type_PTR.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"Shader.h"
#include "SDL_image.h"
#include "Texture.h"
#include "Vertex.h"
#include "model.h"




using namespace std; 

float TpositionX=0.0;
float TpositionY;
float TpostionZ = 0.0;

int main(int argc, char * argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL error", SDL_GetError(), NULL);
		SDL_Quit();
		return 1;

	}

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	SDL_Window* window = SDL_CreateWindow("SDL window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800, 600,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (window == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"SDL_Create window failed",
			SDL_GetError(),
			NULL);
		SDL_Quit();
		return 1;
	}

	// request core OpenGL(creating a context)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GLContext gl_Context = SDL_GL_CreateContext(window);
	if (gl_Context == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateContext failed ", SDL_GetError(), NULL);

		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}




	//init glew

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
		std::cout << glewGetErrorString(error) << std::endl;
	}








	// creating a vertex Array object

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//This is the vertices, rgba, and texture data added 
	// {x,y,z,r,g,b,a,tu,tv}
	/*
	static const Vertex cubeIndiciesArray[]     //g_vertex_buffer_data[] =   redundent code
	{
		{ -0.5f, -0.5f, 0.0f,  1.0f,0.0f,1.0f,1.0f, 0.0f,0.0f },
		{ 0.5f, -0.5f, 0.0f,  0.0f,1.0f,1.0f,1.0f,  1.0f,0.0f},
		{ 0.5f, 0.5f, 0.0f,  1.0f,1.0f,0.0f,1.0f,  1.0f,1.0f},
		{ -0.5f, 0.5f, 0.0f,  1.0f,1.0f,1.0f,1.0f,  0.0f,1.0},

		{ -0.5f,-0.5f, -1.0f,  1.0f,0.0f,0.0f,1.0f, 0.0f,0.0f },
		{ 0.5f,-0.5f, -1.0f,  1.0f,1.0f,0.0f,1.0f,  1.0f,0.0f},
		{ 0.5f,0.5f, -1.0f,  0.0f,0.0f,1.0f,1.0f,  1.0f,1.0f},
		{ -0.5f,0.5f, -1.0f,  0.0f,1.0f,0.0f,1.0f,  0.0f,1.0}

	};
	*/
	static const Vertex cubeVerticesArray[]     //g_vertex_buffer_data[] =   redundent code
	{
		{ -0.5f, -0.5f, 0.0f,  1.0f,0.0f,1.0f,1.0f,0.0f,0.0f },
		{ 0.5f, -0.5f, 0.0f,  0.0f,1.0f,1.0f,1.0f,1.0f,0.0f},
		{ 0.5f, 0.5f, 0.0f,  1.0f,1.0f,0.0f,1.0f,1.0f,1.0f},
		{ -0.5f, 0.5f, 0.0f,  1.0f,1.0f,1.0f,1.0f,0.0f,1.0f},

		{ -0.5f,-0.5f, -1.0f,  1.0f,0.0f,0.0f,1.0f,0.0f,0.0f},
		{ 0.5f,-0.5f, -1.0f,  1.0f,1.0f,0.0f,1.0f,1.0f,0.0f},
		{ 0.5f,0.5f, -1.0f,  0.0f,0.0f,1.0f,1.0f,1.0f,1.0f},
		{ -0.5f,0.5f, -1.0f,  0.0f,1.0f,0.0f,1.0f,0.0f,1.0f}

	};


	// Indicies must be set in anti-clockwise if on the outside of the cube order due to back-face culling
	static const int cubeIndicesArray[] =
	{
		0,1,2, //one triangle of the square
		2,3,0,

		6,5,4,
		4,7,6,

		7,3,2,
		2,6,7,

		6,2,1,
		1,5,6,

		3,7,4,
		4,0,3,

		1,0,5,
		5,0,4
	};

	/*static const GLfloat g_vertex_buffer_data[] = {
	 -1.0f,-1.0f,-1.0f, 
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 
	1.0f, 1.0f,-1.0f, 
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, 
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
	};
	*/
	

	//create vertex buffer

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(Vertex), cubeVerticesArray, GL_STATIC_DRAW);
	// Attribute pointer for vertices

	GLuint elementBuffer;
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36*sizeof(int), cubeIndicesArray, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // change to 2
		3,                  // change to 
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(Vertex),                  // stride
		(void*)0            // this becomes 7 later on (need to shift throught the x,y,z,r,g,b,alpha++textures)
	);

	// Attribute pointer for RGBA


	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),                  // stride
		(void*)(3 * sizeof(float))
	);


	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(7 * sizeof(float))
	);


	/*issues here --massive renaming of variables and shaders happening (too many cooks! took too much advice 
	from fellow student less attention to video tutorials---now paying the price--cod is getting super confusing*/

	GLuint programID = LoadShaders("textureVert.glsl", "texturefrag.glsl");

	glUseProgram(programID);

	if (programID<0) {
		//error check
		printf("Shaders %s and %s are not working", "vert.glsl", "frag.glsl");
	}


	// MODEL in this section 

	unsigned int numberOfVertices=0;
	unsigned int numberOfIndices=0; 

	loadModelFromFile("Tank1.Fbx",vertexbuffer,elementBuffer, numberOfVertices, numberOfIndices);







	//Add texture 
	GLuint textureID = loadTextureFromFile("Crate.jpg");


	//error catching
	if (error != GLEW_OK)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Glew failed to initialise",
			(char*)glewGetErrorString(error),
			NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}






	//matrix stuff___________position/scale/rotation
	glm::vec3 position = glm::vec3(0.0f, 0.5f, 0.0f);
	glm::vec3 Tri_scale = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 Tri_rotation = glm::vec3(0.0f, 10.0f, 10.0f);
	//scaling matrix
	glm::mat4 translationMatrix = glm::translate(position);
	glm::mat4 scaleMatrix = glm::scale(Tri_scale);
	//rotation matrix
	glm::mat4 rotationMatrix = glm::rotate(Tri_rotation.x, glm::vec3(1.0f,0.0f,0.0f))
		*glm::rotate(Tri_rotation.y, glm::vec3(0.0f,1.0f,0.0f))
		*glm::rotate(Tri_rotation.z, glm::vec3(0.0f, 0.0f, 1.f));
	//final matrix
	glm::mat4 modelMatrix = translationMatrix* rotationMatrix * scaleMatrix;
	
	//Add the camera (view matrix)

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -5.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraup = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 cameraMatrix = glm::lookAt(cameraPos, cameraTarget, cameraup);


	//projection matrixs

	glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(45.0f), float(800 / 600), 0.1f, 100.0f);
	

	//Keep all uniforms here!!!!______________________________

	GLint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");
	GLint ViewMatrixLocation = glGetUniformLocation(programID, "viewMatrix");
	GLint ProjectionMatrixLocation = glGetUniformLocation(programID, "projectionMatrix");
	GLint textureLocation = glGetUniformLocation(programID, "baseTexture");


	glEnable(GL_CULL_FACE);

	


	
	//Game loop
	bool isrunning = true;


		SDL_Event event;

		while (isrunning)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					isrunning = false;
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						isrunning = false;
						break;
					case SDLK_w:
						cameraPos.z += 1.0f;
						cameraTarget.z += 1.0f;
						break;
					case SDLK_s:
						cameraPos.z -= 1.0f;
						cameraTarget.z -= 1.0f;
						break;
					case SDLK_a:
						cameraPos.x -= 1.0f;
						cameraTarget.x -= 1.0f;
						break;
					case SDLK_d:
						cameraPos.x += 1.0f;
						cameraTarget.x += 1.0f;
						break;
						//arrow keys---suggestion to self : use the arrow keys to control the rotation of the object
					case SDLK_UP:
						position.y += 1.0f;
						break;
					case SDLK_DOWN:
						position.y -= 1.0f;
						break;
					case SDLK_RIGHT:
						position.x += 1.0f;
						break;
					case SDLK_LEFT: 
						position.x -= 1.0f;
						break;
					}

				}
			}


			//Render and updating with open gl HERE!!!!!
			glClearColor(0.0, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(programID);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureID);

			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

			//glUniformMatrix4fv(modelMatrixlocation, 1, GL_false, glm::value_ptr(modelMatrix));

			//Recalculations for the camera to cope with move/camera movement. This means that the matrix(s) needs to be fed back

			cameraMatrix = glm::lookAt(cameraPos, cameraTarget, cameraup);

			
			//translationMatrix = glm::translate(position);
			//scaleMatrix = glm::scale(Tri_scale);//new addition
			rotationMatrix = glm::rotate(Tri_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))
				*glm::rotate(Tri_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f))
				*glm::rotate(Tri_rotation.z, glm::vec3(0.0f, 0.0f, 1.f));//new addition

			modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(ViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
			glUniformMatrix4fv(ProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
			glUniform1i(textureLocation, 0);
		

			
			glDrawElements(GL_TRIANGLES,numberOfIndices, GL_UNSIGNED_INT, (void*)0);
			

		
			//glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
			//glDisableVertexAttribArray(0);

			SDL_GL_SwapWindow(window);

		}

		//Delete vertexArray
		glDeleteVertexArrays(1, &VertexArrayID);

		glDeleteBuffers(1, &vertexbuffer);
		//DeleteTexture
		glDeleteTextures(1, &textureID);
		//Delete Context
		SDL_GL_DeleteContext(gl_Context);

		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
	
	return 0;
}