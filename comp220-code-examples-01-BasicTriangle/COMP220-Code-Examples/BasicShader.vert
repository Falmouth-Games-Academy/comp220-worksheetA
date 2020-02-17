#version 330 core

layout(location = 0) in vec3 vertexPos;

uniform mat4 model;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	mat4 mvp = projectionMatrix * viewMatrix * model;

	// gl_Position.xyzw = mvp * vec4(vertexPos, 1.0);
	gl_Position.xyzw = vec4(vertexPos, 1.0);
}