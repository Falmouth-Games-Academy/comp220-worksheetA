#include "Renderer.h"

Renderer::~Renderer()
{
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