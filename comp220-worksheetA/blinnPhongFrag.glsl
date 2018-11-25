#version 330 core

in vec4 vertexColourOut;
in vec2 vertexTextureCoordOut;

out vec4 color;

uniform sampler2D textureSampler;

uniform vec4 ambientLightColor;
uniform vec4 ambientMaterialColor;

void main()
{
	// Texture
	// color = texture2D(textureSampler, vertexTextureCoordOut);

	// White color (for debugging)
	// color = vec4(1.0f);

	// Color sent in attribute pointers 
	// color = vertexColourOut;

	// Blinn Phong lighting
	color = (ambientLightColor * ambientMaterialColor);
}