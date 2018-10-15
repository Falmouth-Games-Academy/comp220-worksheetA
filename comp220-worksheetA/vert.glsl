#version 330 core
// Look at the GL Attribute stuff in main.cpp /* */
layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec4 vertexColour;

uniform mat4 modelMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projectionMatrix = mat4(1.0f);

out vec4 vertexColourOut;

void main()
{
	mat4 MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;

	vertexColourOut = vertexColour;

	gl_Position = MVPMatrix * vec4(vertexPos, 1.0f);
}