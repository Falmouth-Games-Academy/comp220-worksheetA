#version 330 core

in vec4 vertexColourOut;
in vec3 vertexNormalOut;
in vec3 cameraDirection;

out vec4 color;

uniform vec3 lightDirection = vec3(0f, 0f, -1f);

uniform vec4 diffuseLightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 diffuseMaterialColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

uniform vec4 ambientLightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 ambientMaterialColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

uniform vec4 specularLightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 specularMaterialColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

uniform float specularRoughness = 20.0f;

void main()
{
	// Dot product of normal and the reversed light direction
	float diffuseLightIntensity = clamp(dot(vertexNormalOut, -lightDirection), 0.0f, 1.0f);
	
	// Calculate halfway vector
	vec3 halfway = normalize(lightDirection + cameraDirection);

	// Calculate specular intensity
	float specularLightIntensity = pow(clamp(dot(vertexNormalOut, halfway), 0.0f, 1.0f), specularRoughness);

	//color = ambientLightColor * ambientMaterialColor;
	color = (ambientLightColor * ambientMaterialColor) + (diffuseLightColor * diffuseMaterialColor * diffuseLightIntensity) + (specularLightColor * specularMaterialColor * specularLightIntensity);
}