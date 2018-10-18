#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec4 vertexColor;

uniform float time = 0.0f;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 vertexColorOut;

void main()
{
	mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

	gl_Position = MVP * vec4(vertexPos, 1.0);
	vertexColorOut = vertexColor;

}