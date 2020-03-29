#version 330 core
out vec4 color;
in vec2 textureCoords;
uniform sampler2D texture0;
void main()
{
	vec4 textureColour = texture(texture0, textureCoords);

	float luminance = (textureColour.r + textureColour.g + textureColour.b) / 3.0;

	if(luminance < 0.2f)
		color = vec4(0 ,0, 0, 1);
	else
		color = vec4(1, 1, 1, 1);
}