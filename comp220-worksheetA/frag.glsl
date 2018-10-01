#version 330 core

out vec3 colour;

uniform vec3 myColour;

void main()
{
	colour = myColour;
}