
//* the entry point of my application *//


#include "main.h"  //include the main header

	//initialise the SDL library
int main(int argc, char* args[]) // first parameter stands for the number of argument commands our window can open, 
{								// the second is a pointer to list of strings
														
    SDL_Window * window = nullptr;								

	//for sdl Initialisation, please see SDL_Initialiser.h
	int SDLInitialiser();

	//for the Window initialisation, please see WindowSpawner.h
	WindowInit::WindowSpawner(&window); 
	
	//for Glew Initialisation, please see Glew initialiser.h//
	GlewInit::GlewInitialiser(&window);

															//** Buffer Section **//

	//we create a vertex array object. this is an object that contains one or more Vertex Buffers and is designed to store the information for a compleate
	//rendered object.
		//we need to create this in order to create more complex objects

	GLuint VertexArrayID; //we name Our VAO
	glGenVertexArrays(1, &VertexArrayID); //this returns an n VAO names in Array, and garants that those names are not the same as the ones called before the function
	glBindVertexArray(VertexArrayID); //bind the VAO we are returning from glGenVertexArrays


	static const GLfloat g_vertex_buffer_data[] = { //this will buff the position of the vertixes on the window
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	//then we pass our triangle to be worked by open gl, we do this by creating a buffer accordingly

	GLuint triangleVerBuff;

	glGenBuffers(1, &triangleVerBuff); //we create a buffer, and we store our triangle ID

	glBindBuffer(GL_ARRAY_BUFFER, triangleVerBuff); //then we bind it as a vertex buffer

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); //now we pass the vertices of our triangle to opengl
	//for the drawing of our triangle, go look the render section

	//load our shader programs
	GLint basicProgramID = MyShaderCreator::LoadShaders( "vert.glsl" , "frag.glsl");
	if (basicProgramID < 0)
	{
		printf("Shaders %s and %s not loaded", "vert.glsl", "frag.glsl");
	}


													//**initialise Uniform Variables Section**// 
	GLuint location = glGetUniformLocation(basicProgramID, "MyVariable");
	glUniform3f(location, 1, 2, 3);


														//** Main Game Loop Section **//


	//first thing first, we create a boolean that stores our main game loop
	bool running = true;
	//SDl event structure, this is a queue that contains all the event strutctures of library, it can read the events and place them in itself
	//useful when you need to determinate a certain event.
	SDL_Event ev;
	while (running)
	{
		//pool for the events which have happend in this frame
			//remember SDL_PollEvent requires a pointer value&
		while (SDL_PollEvent(&ev))
		{
			//switch statement for any kind of message the event gives us
			switch (ev.type)
			{
				//quit message, called when the window is closed
			case SDL_QUIT:
				running = false;
				break;
				//KEYDOWN message, called when a key has been pressed down
			case SDL_KEYDOWN:
				//check if a key has been pressed trough ev
				switch (ev.key.keysym.sym)
				{
					//check if it was the escape key
				case SDLK_ESCAPE:
					running = false;
					break;
				}

			}
		}
								 									//** Render Section **//


		//Update game and Draw with OpenGL!!!

		//set the colour of the screen
		glClearColor(0.0, 0.0, 0.4, 0.0); 
		//set the bitplane area of the window using our colour buffer
		glClear(GL_COLOR_BUFFER_BIT);
		//draw using this program
		glUseProgram(basicProgramID);

		//we enable our vertex array. we do this because by default all all client-side capabilities are disabled, including all generic vertex attribute arrays.
		//if enabled we can make calls regarding rendering and allow us to draw
		glEnableVertexAttribArray(0);

		//we now get our triangle buffer and move it here for drawing //remember, once bind to a new object, this buffer previous contract is broken
		glBindBuffer(GL_ARRAY_BUFFER, triangleVerBuff);

		//now we specify the location and the type of attributes of our buffer
		glVertexAttribPointer(
			0,					//INDEX, it's used to specify the vertex attribute that needs to be modified
			3,					//SIZE, used to understeand the number of components per generic vertex attribute
			GL_FLOAT,			//TYPE, used to determine the type of our components per generic vertex attribute
			GL_FALSE,			//NORMALIZED, Specifies whether fixed-point data values should be normalized or converted directly as fixed-point values.
			0,					//STRIDE, specifies the byte offest between consecutive generic vertex attributes. If this is 0, it means that the arrays are packed thightly togherter
			(void*)0			//POINTER, this points to the first componnent of the first generic vertex attribute. The initial value is 0
		);

		//now that we have our buffer attributes settled, we can finally draw our triangle

		glDrawArrays(GL_TRIANGLES, 0, 3); //specifies what kidn of primitives to renderd. we provide a starting index, then we provide with the number of vertices
		glDisableVertexAttribArray(0); //we now disable our ability to draw, so we don't draw anything else unecessary.

		//update our window now
		//remember. all the rendering behind this.
		SDL_GL_SwapWindow(window);

	}

														//** Garbage Collection Section **//
	//Destoy the window and quit SDL2, clean all the things you have created
	glDeleteProgram(basicProgramID);
	glDeleteBuffers(1, &triangleVerBuff);
	glDeleteVertexArrays(1, &VertexArrayID); //delete the VAO

	SDL_DestroyWindow(window); 
	SDL_Quit();

	return 0;
}