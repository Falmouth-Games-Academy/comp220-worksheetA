#version 330 core

in vec4 vertexColourOut;
in vec2 vertexTextureCoordOut;

out vec4 colour;

uniform sampler2D baseTexture;

void main()
{
 vec4 texel = texture(baseTexture, vertexTextureCoordOut);
  if(texel.a < 0.5)
    discard;
  colour = texel;
}