#version 330 core

out vec4 color;

in vec4 vertexColourOut;
in vec2 vertexTextureCoordsOut;

uniform sampler2D textureSampler;

void main()
{
	// Texture
	// color = texture(textureSampler, vertexTextureCoordsOut);

	// White color (for debugging)
	// color = vec4(1.0f);

	// Color sent in attribute pointers 
	color = vertexColourOut;
}