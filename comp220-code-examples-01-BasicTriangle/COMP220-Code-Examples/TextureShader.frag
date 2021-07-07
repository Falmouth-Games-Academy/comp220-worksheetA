#version 330 core

in vec4 vertexColourOut;
in vec2 vertexTextureCoordsOut;

out vec4 fragColor;

uniform sampler2D albedo;
uniform sampler2D normal;
uniform sampler2D specular;
uniform sampler2D gloss;

void main()
{
	vec3 color = texture(albedo, vertexTextureCoordsOut).xyz;

    fragColor = vec4(color, 1.0);
}