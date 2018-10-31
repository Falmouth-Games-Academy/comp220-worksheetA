#version 330 core

// Look at GL Attribute Pointer in main.cpp
layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec4 vertexColour;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform mat4 MVPMatrix;

out vec4 vertexColourFinal;

void main()
{
	//mat4 MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;

	gl_Position = projMatrix * viewMatrix * modelMatrix* vec4(vertexPos, 1.0f);

	//gl_Position = modelMatrix * vec4(vertexPos, 1.0f);
	//vertColour = vertexPos;
	vertexColourFinal = vertexColour;
}