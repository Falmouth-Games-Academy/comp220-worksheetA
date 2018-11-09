#version 330 core

//gl_Position = vec4(vertexPos, 1.0f);
//mat4 mvpPosition = MVPMatrix*vec4(vertexPos, 1.0f);

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec4 vertexColour;
layout(location = 2)  in vec2 vertexTextureCoord;



uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 vertexColourOut;
out vec2 vertexTextureCoordOut;

void main()
{
	mat4 MVPMatrix = projectionMatrix*viewMatrix*modelMatrix;

	gl_Position = MVPMatrix * vec4(vertexPos, 1.0f);

	vertexColourOut = vertexColour;

	vertexTextureCoordOut = vertexTextureCoord;
}