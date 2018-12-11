#version 330 core

out vec4 colour;
in vec3 textureCoords;

uniform samplerCube skybox;

void main()
{
	gl_FragDepth = 0.9999f;
	colour = texture(skybox, textureCoords);
	
}