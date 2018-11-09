
#version 330 core

// Look at GL Attribute Pointer in main.cpp

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec4 vertexColour;
lauout(location =2)  in vec2 vertexTextureCoord;

uniform float = 0.0f;



uniform mat4 ModelMatrix = mat4(1.0f);
uniform mat4 veiwMatrix = mat4(1.0f;
uniform mat4 projectionMatrix(1.0f);

out vec4 vertexColourOut;
out vec2 vertexTextureCoordOut;

void main()
{
	mat MVPMatrix = projectionMatrix*VeiwMatrix*ModelMatrix;

	gl_Position = MVPMatrix * vec4(vertexPos, 1.0f);

	vertexColourOut = vertexColour;

	vertexTextureCoordOut = vertexTextureCoord;
}