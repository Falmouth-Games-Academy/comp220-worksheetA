#include "Shaders.h"

//this program will load on compilation the shaders used by our application.



GLuint MyShaderCreator::LoadShaders(const char * vertex_file_path, const char * fragment_file_path)
{

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	string VertexShaderCode;

	ifstream VertexShaderStream(vertex_file_path, ios::in); //ifstream is goiing to manipulate the program file
	if (VertexShaderStream.is_open()) {
		string Line = "";
		while (getline(VertexShaderStream, Line))
			//get data from file
			VertexShaderCode += "\n" + Line;
		//once done, close stream
		VertexShaderStream.close();

	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	string FragmentShaderCode;
	ifstream FragmentShaderStream(fragment_file_path, ios::in);
	if (FragmentShaderStream.is_open()) {
		string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();

	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	//compile the shaders 
	GLint Result = GL_FALSE;
	int InfoLogLength = NULL;

	MyShaderCreator::CompileVertexShaders(vertex_file_path, VertexShaderCode, VertexShaderID, Result, InfoLogLength);
	MyShaderCreator::CompileFragmentShaders(fragment_file_path, FragmentShaderCode, FragmentShaderID, Result, InfoLogLength);
	
	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	MyShaderCreator::ShaderProgramLinker(ProgramID, VertexShaderID, FragmentShaderID, Result, InfoLogLength);


	//Delete the shader compilation at the end 
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void MyShaderCreator::CompileVertexShaders(const char *path, string code, GLuint id, GLint result, int logLength)
{
	// Compile Vertex Shader
	printf("Compiling shader : %s\n", path);
	char const * VertexSourcePointer = code.c_str(); //we create a pointer passing a string of VertexShader
	glShaderSource(id, 1, &VertexSourcePointer, NULL);
	glCompileShader(id);

	// Check Vertex Shader
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		vector<char> VertexShaderErrorMessage(logLength + 1);
		glGetShaderInfoLog(id, logLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}
}

void MyShaderCreator::CompileFragmentShaders(const char *path, string code, GLuint id, GLint result, int logLength)
{
	// Compile Fragment Shader
	printf("Compiling shader : %s\n", path);
	char const * FragmentSourcePointer = code.c_str();
	glShaderSource(id, 1, &FragmentSourcePointer, NULL);
	glCompileShader(id);

	// Check Fragment Shader
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		vector<char> FragmentShaderErrorMessage(logLength + 1);
		glGetShaderInfoLog(id, logLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}
}

void MyShaderCreator::ShaderProgramLinker(GLuint programID, GLuint vertID, GLuint fragID, GLint result, int logLength)
{
	
	glAttachShader(programID, vertID);
	glAttachShader(programID, fragID);
	glLinkProgram(programID);

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		vector<char> ProgramErrorMessage(logLength + 1);
		glGetProgramInfoLog(programID, logLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
}