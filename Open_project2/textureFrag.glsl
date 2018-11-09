#version 330 core


in vec4 vertexColorOut;  
in vec2 vertexTextureCoordOut;

out vec4 color;

uniform sampler2D baseTexture;

void main(){

color = texture2D(baseTexture,vertexTextureCoordOut);

}
