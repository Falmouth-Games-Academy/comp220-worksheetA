#version 330 core

in vec4 vertexColourOut;
in vec2 vertexTextureCoordsOut;

out vec4 color;

uniform sampler2D albedo;
uniform sampler2D normal;

void main()
{
	vec4 objColor = texture(albedo, vertexTextureCoordsOut);

	float ambientStrength = 0.8;
    vec3 ambient = ambientStrength * vec3(0.2, 0.6, 0.6);

    vec3 result = ambient * objColor.rgb;
    color = vec4(result, 1.0);
}