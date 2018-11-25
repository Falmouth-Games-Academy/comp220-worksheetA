#version 330 core

in vec4 vertexColourOut;
in vec2 vertexTextureCoordOut;
in vec3 vertexNormalOut;

out vec4 colour;

uniform vec4 fragColour=vec4(1.0,1.0,1.0,1.0);

uniform sampler2D baseTexture;

uniform vec4 ambientLightColour;
uniform vec4 diffuseLightColour;

uniform vec4 ambientMaterialColour;
uniform vec4 diffuseMaterialColour;

uniform vec3 lightDirection;

void main()
{
	float diffuseReflectance = dot(vertexNormalOut, -lightDirection);

	colour = (ambientLightColour * ambientMaterialColour) + (diffuseLightColour * diffuseReflectance * diffuseMaterialColour);
}
