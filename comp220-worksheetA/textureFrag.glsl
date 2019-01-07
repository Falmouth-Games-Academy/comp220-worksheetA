#version 330 core

in vec4 vertexColourOut;
in vec2 vertextTextureCoordOut;

out vec4 colour;

uniform vec4 fragColour=vec4(1.0,1.0,1.0,1.0);

uniform sampler2D diffuseTexture;

void main()
{
	colour = texture2D(diffuseTexture, vertextTextureCoordOut);
}