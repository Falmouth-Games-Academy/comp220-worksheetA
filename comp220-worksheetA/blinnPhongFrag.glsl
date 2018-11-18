#version 330 core

in vec4 vertexColourOut;
in vec2 vertextTextureCoordOut;

out vec4 colour;

uniform vec4 fragColour=vec4(1.0,1.0,1.0,1.0);

uniform sampler2D baseTexture;

uniform vec4 ambientLightColour;
uniform vec4 ambientMaterialColour;

void main()
{
	colour = (ambientLightColour * ambientMaterialColour);
}
