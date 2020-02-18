#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec4 vertexCol;

uniform mat4 model;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 vertexColourOut;

void main()
{
	mat4 mvp = projectionMatrix * viewMatrix * model;

	vertexColourOut = vertexCol;

	gl_Position.xyzw = mvp * vec4(vertexPos, 1.0);
}