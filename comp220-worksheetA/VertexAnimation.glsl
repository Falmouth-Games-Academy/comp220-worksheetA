#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColours;
layout(location=2) in vec2 vertexTextureCoord;
layout(location=3) in vec3 vertexNormals;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform vec3 cameraPosition;

uniform float currentTime;
uniform float deltaTime;

out vec4 vertexColoursOut;
out vec2 vertexTextureCoordOut;
out vec3 vertexNormalsOut;
out vec3 viewDirection;
out vec3 worldVertexPosition;

void main(){
	
	mat4 mvpMatrix=projMatrix*viewMatrix*modelMatrix;

	vec3 adjustedVertexPosition=vertexPosition;
	adjustedVertexPosition.x+=(sin(currentTime+adjustedVertexPosition.y)*vertexPosition.y)*0.1;
	adjustedVertexPosition.z+=(sin(currentTime+adjustedVertexPosition.y)*vertexPosition.y)*0.1;
	
	float X = adjustedVertexPosition.x;
	float Z = adjustedVertexPosition.z;

	//adjustedVertexPosition.x += step(0,vertexPosition.y - 0.5f) * X * 0.5f;
	//adjustedVertexPosition.z += step(0,vertexPosition.y - 0.5f) * Z * 0.5f;

	vec4 worldPosition=modelMatrix*vec4(adjustedVertexPosition,1.0f);
	vec4 mvpPosition=mvpMatrix*vec4(adjustedVertexPosition,1.0f);
	
	vertexColoursOut=vertexColours;
	vertexTextureCoordOut=vertexTextureCoord;
	vertexNormalsOut=normalize(modelMatrix*vec4(vertexNormals,0.0f)).xyz;
	viewDirection=normalize(cameraPosition-worldPosition.xyz);
	worldVertexPosition=worldPosition.xyz;

	gl_Position=mvpPosition;
}