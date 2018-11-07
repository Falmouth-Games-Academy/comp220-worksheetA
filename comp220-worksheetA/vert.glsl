#version 330 core

// Look at GL Attribute Pointer in main.cpp
layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec4 vertexColour;
layout(location = 2) in vec2 vertexTextureCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

out vec4 vertexColourFinal;
out vec2 vertexTextureCoordOut;

void main()
{
	gl_Position = projMatrix * viewMatrix * modelMatrix* vec4(vertexPos, 1.0f);

	vertexTextureCoordOut = vertexTextureCoord;

	vertexColourFinal = vertexColour;
}