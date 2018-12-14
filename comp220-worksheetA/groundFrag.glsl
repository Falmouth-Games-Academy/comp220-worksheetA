#version 330 core

in vec4 vertexColourOut;
in vec2 vertexTextureCoordOut;
in vec3 vertexNormalsOut;
in vec3 viewDirection;

out vec4 colour;

uniform sampler2D baseTexture;

uniform vec4 ambientLightColour = vec4 (1.0f);
uniform vec4 diffuseLightColour = vec4 (1.0f);
uniform vec4 specularLightColour = vec4 (1.0f);

uniform vec3 lightDirection = vec3 (0.0f, 0.0f, 1.0f);

vec4 ambientMaterialColour = vec4 (0.02f, 0.02f, 0.02f, 1.0f);
uniform vec4 diffuseMaterialColour = vec4 (0.0f, 0.0f, 0.0f, 1.0f);
uniform vec4 specularMaterialColour = vec4 (1.0f);
uniform float specularMaterialPower = 25.0f;

void main()
{
	//Diffuse
	float nDotl=dot(vertexNormalsOut,normalize(-lightDirection));

	//Specular
	vec3 halfWay=normalize(lightDirection+viewDirection);
	float nDoth=pow(dot(vertexNormalsOut,halfWay),specularMaterialPower);

	colour = texture(baseTexture, vertexTextureCoordOut / 6) + (ambientLightColour*ambientMaterialColour)+(diffuseLightColour*nDotl*diffuseMaterialColour);
}