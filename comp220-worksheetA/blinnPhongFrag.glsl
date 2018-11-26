#version 330 core

in vec4 vertexColourOut;
in vec2 vertexTextureCoordOut;
in vec3 vertexNormalOut;
in vec4 worldSpaceVertexOut;

out vec4 color;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

uniform vec4 ambientMaterialColor;
uniform vec4 ambientLightColor;

uniform vec4 diffuseMaterialColor;
uniform vec4 diffuseLightColor;

uniform vec4 specularLightColor = vec4(1.0f);
uniform vec4 specularMaterialColor = vec4(0.8f, 0.8f, 0.8f, 1.0f);

uniform vec3 cameraPosition;
uniform vec3 lightDirection;

uniform float specularPower = 25.0f;

void main()
{
	// Texture
	// color = texture2D(diffuseTexture, vertexTextureCoordOut);

	// White color (for debugging)
	// color = vec4(1.0f);

	// Color sent in attribute pointers 
	// color = vertexColourOut;

	// Blinn Phong lighting
	float nDotl = dot(vertexNormalOut, -lightDirection);


	vec3 viewDirection = normalize(cameraPosition - worldSpaceVertexOut.xyz);
	vec3 halfWay = normalize(-lightDirection + viewDirection);
	float nDoth = pow(clamp(dot(vertexNormalOut, halfWay), 0, 1), specularPower);

	vec4 diffuseTextureColor = texture(diffuseTexture, vertexTextureCoordOut);
	vec4 specularTextureColor = texture(specularTexture, vertexTextureCoordOut);

	color = (ambientLightColor * ambientMaterialColor) + 
			(diffuseLightColor * nDotl * diffuseMaterialColor * diffuseTextureColor) + 
			(specularLightColor * nDoth * specularMaterialColor * specularTextureColor);
}