#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColour; // IS vertexColour in some other vert files here

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform float currentTime;

out vec4 vertexColourOut;

void main(){

	vec3 animatedPosition = vertexPosition;

	animatedPosition.y += (sin(currentTime + animatedPosition.x) * 0.6f);
	animatedPosition.z += (cos(currentTime + animatedPosition.x) * 0.6f);

	// Animate normals next
	// Animate texture coords inside frag texture more realistic
	// 0.6f into paramas
	
	mat4 mvpMatrix=projectionMatrix*viewMatrix*modelMatrix;

	vec4 mvpPosition=mvpMatrix*vec4(animatedPosition,1.0f);
	
	vertexColourOut=vertexColour;

	gl_Position=mvpPosition;
}