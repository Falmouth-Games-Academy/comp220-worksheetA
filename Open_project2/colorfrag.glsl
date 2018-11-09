#version 330 core


in vec4 vertexColorOut;  
in vec2 vertexTextureCoord;

out vec4 color;
out vec2 vertexTextureCoordOut;

uniform vec4 fragColorVertex4(1.0,1.0,1.0,1.0);
unifoirm sampler2D baseTexture;

void main(){

color = texture2D(baseTexture,vertexTextureCoordOut);

}
