#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec4 vertexColour;
layout(location = 2) in vec2 vertexTextureCoord;
layout(location = 3) in vec3 vertexNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 vertexColourOut;
out vec2 vertexTextureCoordOut;
out vec3 vertexNormalOut;
out vec4 worldSpaceVertexOut;

void main()
{
	mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

	vec4 mvpPosition = mvpMatrix * vec4(vertexPos, 1.0f);

	vertexColourOut = vertexColour;
	vertexTextureCoordOut = vertexTextureCoord;
	vertexNormalOut = vertexNormal;
	worldSpaceVertexOut = modelMatrix * vec4(vertexPos, 1.0f);

	gl_Position = mvpPosition;
}