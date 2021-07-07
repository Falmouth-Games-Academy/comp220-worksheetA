#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec4 vertexCol;
layout(location = 2) in vec2 vertexTextureCoords;

uniform mat4 model;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 vertexColourOut;
out vec2 vertexTextureCoordsOut;

void main()
{
	mat4 mvp = projectionMatrix * viewMatrix * model;

	vertexColourOut = vertexCol;
	vertexTextureCoordsOut = vertexTextureCoords;

	gl_Position.xyzw = mvp * vec4(vertexPos, 1.0);
}