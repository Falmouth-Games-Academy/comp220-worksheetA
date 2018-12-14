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
uniform float windForce;

out vec4 vertexColoursOut;
out vec2 vertexTextureCoordOut;
out vec3 vertexNormalsOut;
out vec3 viewDirection;
out vec3 worldVertexPosition;

void main(){
	
	mat4 mvpMatrix=projMatrix*viewMatrix*modelMatrix;

	vec3 adjustedVertexPosition=vertexPosition;
	vec4 orginalWorldSpace = modelMatrix*vec4(vertexPosition,1.0f);

	adjustedVertexPosition.x+=(sin(currentTime+adjustedVertexPosition.y)*(orginalWorldSpace.y - 8))*windForce * 2;
	adjustedVertexPosition.z+=(sin(currentTime+adjustedVertexPosition.y)*(orginalWorldSpace.y - 8))*windForce * 2;

	vec4 worldPosition=modelMatrix*vec4(adjustedVertexPosition,1.0f);
	vec4 mvpPosition=mvpMatrix*vec4(adjustedVertexPosition,1.0f);
	
	vertexColoursOut=vertexColours;
	vertexTextureCoordOut=vertexTextureCoord;
	vertexNormalsOut=normalize(modelMatrix*vec4(vertexNormals,0.0f)).xyz;
	viewDirection=normalize(cameraPosition-worldPosition.xyz);
	worldVertexPosition=worldPosition.xyz;

	gl_Position=mvpPosition;
}