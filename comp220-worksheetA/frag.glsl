#version 330 core


in vec4 vertexColourFinal;
in vec2 vertexTextureCoordOut;

out vec4 colour;

uniform sampler2D baseTexture;


uniform vec4 triangleColour; 

void main()
{
  //colour = vertexColourFinal;

  colour=texture2D(baseTexture,vertexTextureCoordOut);

}