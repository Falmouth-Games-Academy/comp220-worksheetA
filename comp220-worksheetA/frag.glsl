#version 330 core

out vec4 colour;

uniform vec3 myColour;

in vec4 vertexColourOut;

void main()
{
	colour = vertexColourOut;
}