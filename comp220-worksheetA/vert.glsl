#version 330 core
// Look at the GL Attribute stuff in main.cpp /* */
layout(location = 0) in vec3 vertexPos;

void main()
{
	gl_Position = vec4(vertexPos, 1.0);
}