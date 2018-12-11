#version 330 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

out vec3 textureCoords;

void main()
{
	mat4 mvpMatrix=projMatrix*viewMatrix*modelMatrix;

	vec4 mvpPosition=mvpMatrix*vec4(vertexPosition,1.0f);
	mvpPosition = modelMatrix * vec4(vertexPosition, 1.0f);
	mvpPosition = viewMatrix * vec4(mvpPosition.xyz, 0.0f);
	mvpPosition = projMatrix * vec4(mvpPosition.xyz, 1.0f);
	textureCoords = vertexPosition;
    gl_Position = mvpPosition;
}