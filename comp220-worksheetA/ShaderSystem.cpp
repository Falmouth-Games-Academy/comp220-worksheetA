#include "ShaderSystem.h"

#pragma region Init/Delete

void ShaderSystem::Init()
{
	shaderProgramID = 0;
}

void ShaderSystem::Delete()
{
	glDeleteProgram(shaderProgramID);
}

#pragma endregion

#pragma region Load Shader Functions

GLuint ShaderSystem::LoadShaders(const char* c_vertexFilePath, const char* c_fragmentFilePath)
{
	// Create The Shader
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	// Read the vertex shader code from the file
	std::string vertexShaderCode = ReadStream(c_vertexFilePath);
	if(vertexShaderCode == "")
	{
		printf("Couldn't open %s. Check the directory name again.", c_vertexFilePath);
		getchar();
		return 0;
	}
	std::string fragmentShaderCode = ReadStream(c_fragmentFilePath);
	if (fragmentShaderCode == "")
	{
		printf("Couldn't open %s. Check the directory name again.", c_fragmentFilePath);
		getchar();
		return 0;
	}

	GLint result = GL_FALSE;

	int InfoLogLength = 0;

	// Compile & Check Shaders
	CompileShader(vertexShaderID, vertexShaderCode);
	CheckShader(vertexShaderID, result, InfoLogLength);
	CompileShader(fragmentShaderID, fragmentShaderCode);
	CheckShader(fragmentShaderID, result, InfoLogLength);
	std::vector<GLuint> shaderIDs;
	shaderIDs.push_back(vertexShaderID);
	shaderIDs.push_back(fragmentShaderID);

	GLuint programID = CreateProgram(shaderIDs);
	CheckShader(programID, GL_LINK_STATUS, result, InfoLogLength);
	DetachShaders(programID, shaderIDs);
	DeleteShaders(shaderIDs);

	return programID;
}

GLuint ShaderSystem::CreateProgram(std::vector<GLuint> shaderIDs)
{
	GLuint programID = glCreateProgram();
	for (GLuint shader : shaderIDs)
	{
		glAttachShader(programID, shader);
	}
	glLinkProgram(programID);
	return programID;
}

std::string ShaderSystem::ReadStream(const char* _c_filePath)
{
	std::string newString;
	std::ifstream newStream(_c_filePath, std::ios::in);
	if (newStream.is_open())
	{
		std::stringstream sstr;
		sstr << newStream.rdbuf();
		newString = sstr.str();
		newStream.close();
	}
	else return "";
	return newString;
}

void ShaderSystem::DetachShaders(GLuint programID, std::vector<GLuint> shaderIDs)
{
	for (GLuint shaders : shaderIDs)
	{
		glDetachShader(programID, shaders);
	}
}

void ShaderSystem::DeleteShaders(std::vector<GLuint> shaderIDs)
{
	for (GLuint shaders : shaderIDs)
	{
		glDeleteShader(shaders);
	}
}

void ShaderSystem::CompileShader(GLuint shaderID, std::string shaderCode)
{
	char const* sourcePtr = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePtr, NULL);
	glCompileShader(shaderID);
}

bool ShaderSystem::CheckShader(GLuint shaderID, GLint result, int logLength)
{
	// Check shader compilation status
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
	// If there's an error, log the error
	if (logLength > 0)
	{
		std::vector<char> shaderErrorMessage(logLength + 1);
		glGetShaderInfoLog(shaderID, logLength, NULL, &shaderErrorMessage[0]);
		printf("%s\n", &shaderErrorMessage[0]);
		return false;
	}
	return true;
}

bool ShaderSystem::CheckShader(GLuint shaderID, GLenum info, GLint result, int logLength)
{
	// Check shader compilation status
	glGetShaderiv(shaderID, info, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
	// If there's an error, log the error
	if (logLength > 0)
	{
		std::vector<char> shaderErrorMessage(logLength + 1);
		glGetShaderInfoLog(shaderID, logLength, NULL, &shaderErrorMessage[0]);
		printf("%s\n", &shaderErrorMessage[0]);
		return false;
	}
	return true;
}
#pragma endregion

bool ShaderSystem::Load(const std::string& vertShaderFilename, const std::string& fragShaderFilename)
{
	shaderProgramID = LoadShaders(vertShaderFilename.c_str(), fragShaderFilename.c_str());

	if (shaderProgramID == false)
		return false;

	RetrieveUniforms();
	return true;
}

void ShaderSystem::RetrieveUniforms()
{
	GLint numberOfUniforms;
	GLint sizeOfUniformName;
	GLenum uniformType;

	GLchar nameBuffer[128];
	GLsizei nameLength;
	glGetProgramiv(shaderProgramID, GL_ACTIVE_UNIFORMS, &numberOfUniforms);
	for (int i = 0; i < numberOfUniforms; i++)
	{
		glGetActiveUniform(shaderProgramID, i, 128, &nameLength, &sizeOfUniformName, &uniformType, nameBuffer);
		std::cout << "Uniform " << i << " " << nameBuffer << std::endl;

		Uniforms.insert(std::pair<std::string, GLint>(nameBuffer, i));
	}

}

void ShaderSystem::SetCam(CameraComponent* _cam)
{
	mainCam = _cam;
}

void ShaderSystem::Bind()
{
	glUseProgram(shaderProgramID);
}



void ShaderSystem::Update(Coordinator* coord, GLuint v, GLuint p)
{
	for (auto const& ent : sy_Entities)
	{
		MeshCollectionComponent mcc = coord->GetComponent<MeshCollectionComponent>(ent);
		Texture tec = coord->GetComponent<Texture>(ent);
		for (MeshComponent mesh : mcc.mcc_meshCollection)
		{
			glm::mat4 modelMatrix = glm::make_mat4(mesh.modelMatrix);
			glUniformMatrix4fv(GetUniform("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glm::mat4 view = glm::make_mat4(mainCam->view);
			glUniformMatrix4fv(v, 1, GL_FALSE, glm::value_ptr(view));
			glm::mat4 projection = glm::make_mat4(mainCam->projection);
			glUniformMatrix4fv(p, 1, GL_FALSE, glm::value_ptr(projection));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tec.i_albedoTextureID);
			glUniform1i(GetUniform("albedoTexture"), 0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tec.i_specTextureID);
			glUniform1i(GetUniform("specularTexture"), 1);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, tec.i_normalTextureID);
			glUniform1i(GetUniform("normalTexture"), 2);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, tec.i_heightTextureID);
			glUniform1i(GetUniform("heightTexture"), 3);
		}
	}
}

GLint ShaderSystem::GetUniform(const std::string& uniformName)
{
	return Uniforms[uniformName];
}