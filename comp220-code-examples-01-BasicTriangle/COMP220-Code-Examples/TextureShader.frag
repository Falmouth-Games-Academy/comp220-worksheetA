#version 330 core

in vec4 vertexColourOut;
in vec2 vertexTextureCoordsOut;

out vec4 color;

uniform sampler2D baseTexture;

void main()
{
	color = texture(baseTexture, vertexTextureCoordsOut);
}