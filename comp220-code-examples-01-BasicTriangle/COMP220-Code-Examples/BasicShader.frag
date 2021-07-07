#version 330 core

in vec4 vertexColourOut;
out vec4 color;

void main()
{
	color = vertexColourOut;
}