#include "Renderer.h"

Renderer::~Renderer()
{
	glDeleteBuffers(1, &screenVBO);
	glDeleteVertexArrays(1, &screenVAO);

	glDeleteRenderbuffers(1, &depthBufferID);
	glDeleteTextures(1, &postTextureID);
	glDeleteBuffers(1, &screenVBO);
	glDeleteFramebuffers(1, &frameBufferID);

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int Renderer::Init(const char* windowName, int resX, int resY, bool fullscreen, int glMajorVersion, int glMinorVersion, bool depthTesting, bool cullFaces)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Display an error message box
		//https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return 1;
	}

	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX, resY, SDL_WINDOW_OPENGL);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);
		//Close the SDL Library
		//https://wiki.libsdl.org/SDL_Quit
		SDL_Quit();
		return 1;
	}

	glContext = SDL_GL_CreateContext(window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glMajorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glMinorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unable to initialise GLEW", (char*)glewGetErrorString(glewError), NULL);
	}

	SetFullscreen(fullscreen);

	if(depthTesting)
		glEnable(GL_DEPTH_TEST);
	
	if(cullFaces)
		glEnable(GL_CULL_FACE);

	this->windowTitle = windowName;

	return 0;
}

void Renderer::ClearScreen(float r, float g, float b, float a, GLbitfield mask)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SwapBuffers()
{
	if (window != nullptr)
		SDL_GL_SwapWindow(window);
	else
		std::cout << "No SDL_Window available, cannot swap buffer";
}

void Renderer::SetFullscreen(bool fullscreen)
{
	if (window)
	{
		SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_BORDERLESS);
	}
}

bool Renderer::IsFullscreen()
{
	return SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN == SDL_WINDOW_FULLSCREEN;
}

void Renderer::LoadProgram(const char* shaderName, const char* directory)
{
	std::vector<GLuint> loadedShaders = std::vector<GLuint>();

	// Load fragment shader
	char shaderPath[20];
	//std::strcat(shaderPath, directory);
	std::strcpy(shaderPath, shaderName);
	std::strcat(shaderPath, ".frag");
	loadedShaders.push_back(LoadSingleShader(shaderPath, GL_FRAGMENT_SHADER));

	// Load vertex shader
	std::strcpy(shaderPath, "");
	//std::strcat(shaderPath, directory);
	std::strcpy(shaderPath, shaderName);
	std::strcat(shaderPath, ".vert");
	loadedShaders.push_back(LoadSingleShader(shaderPath, GL_VERTEX_SHADER));

	// Load shader program
	loadedPrograms.try_emplace(shaderName, LinkShaders(loadedShaders));
}

void Renderer::LoadAllPrograms(const char* directory)
{
	// TODO: implement looping through all shader files with a known extension and adding them to the corresponding shader progrm
}

void Renderer::UnloadProgramByName(std::string programName)
{
	glDeleteProgram(loadedPrograms.at(programName));
	loadedPrograms.erase(programName);
}

void Renderer::UnloadProgramById(GLuint id)
{
	for (auto& item : loadedPrograms)
		if (item.second == id)
		{
			glDeleteProgram(id);
			loadedPrograms.erase(item.first);
			return;
		}
}

void Renderer::UnloadAllPrograms()
{
	for (auto& item : loadedPrograms)
		UnloadProgramByName(item.first);
}

void Renderer::InitPostProcess()
{
	int resX, resY;
	SDL_GetWindowSize(window, &resX, &resY);
	postTextureID = CreateTexture(resX, resY);

	// Create depth buffer
	depthBufferID = 0;
	glGenRenderbuffers(1, &depthBufferID);
	// Bind depth buffer
	glBindRenderbuffer(GL_RENDERBUFFER, depthBufferID);
	// The higher the buffer the more precise it is but the more expensive it is. GL_DEPTH_COMPONENT is 8 bits and should be enough
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 1280, 720);

	// Create frame buffer
	frameBufferID = 0;
	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

	// Bind the depth buffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferID);

	// Bind texture - depends on how many attachments your drivers support
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, postTextureID, 0);
	
	// Check the framebuffer works well
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("Incomplete framebuffer!\n");
		return;
	}

	glGenBuffers(1, &screenVBO);
	glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), pVertices, GL_STATIC_DRAW);
	
	glGenVertexArrays(1, &screenVAO);
	glBindVertexArray(screenVAO);
	glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	postProcessingProgramID = this->GetProgram("PostProcessing");

	texture0ID = glGetUniformLocation(postProcessingProgramID, "texture0");

	glBindBuffer(GL_FRAMEBUFFER, 0);

	postProcessInit = true;
}

void Renderer::PreRender()
{
	// Bind the frame buffer
	if (usePostProcess)
	{
		glEnable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	// Clear screen
	ClearScreen(0, 0, 0, 1);
}

void Renderer::PostRender()
{
	if (usePostProcess)
		PostProcess();
}

void Renderer::PostProcess()
{
	// Start post processing
	glDisable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	ClearScreen(0, 0, 0, 1, GL_COLOR_BUFFER_BIT);

	glUseProgram(postProcessingProgramID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, postTextureID);
	glUniform1d(texture0ID, 0);
		
	// Draw post processing quad
	glBindVertexArray(screenVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

GLuint Renderer::LoadSingleShader(const char* file_path, GLenum shaderType)
{
	// Create shader
	GLuint shaderID = glCreateShader(shaderType);

	// Read shader code from file
	std::string shaderCode;
	std::ifstream shaderStream(file_path, std::ios::in);
	if (shaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}
	else
	{
		printf("Impossible to open %s. Are you in the right directory ?\n", file_path);
		getchar();
		return 0;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile shader
	printf("Compiling shader : %s\n", file_path);
	char const* sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		std::vector<char> shaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(infoLogLength, infoLogLength, NULL, &shaderErrorMessage[0]);
		printf("%s\n", &shaderErrorMessage[0]);
	}

	return shaderID;
}

GLuint Renderer::LinkShaders(std::vector<GLuint> shaderID)
{
	GLint result = GL_FALSE;
	int infoLogLength;

	// Link the program
	printf("Linking program\n");
	GLuint programID = glCreateProgram();
	for (auto& id : shaderID)
		glAttachShader(programID, id);
	glLinkProgram(programID);

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	for (auto& id : shaderID)
	{
		glDetachShader(programID, id);
		glDeleteShader(id);
	}

	return programID;
}