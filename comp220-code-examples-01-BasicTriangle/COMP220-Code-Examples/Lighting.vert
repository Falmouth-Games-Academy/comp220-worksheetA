#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec4 vertexCol;
layout(location = 3) in vec3 vertexNormal;

uniform mat4 model;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition = vec3(0.0f, 0.0f, 0.0f);

out vec4 vertexColourOut;
out vec3 vertexNormalOut;
out vec3 cameraDirection;

void main()
{
	mat4 mvp = projectionMatrix * viewMatrix * model;

	vertexColourOut = vertexCol;

	vec3 vertexModelPos = (model * vec4(vertexPos, 1.0f)).xyz;

	cameraDirection = normalize(cameraPosition - vertexModelPos);

	gl_Position.xyzw = mvp * vec4(vertexPos, 1.0);

	vertexNormalOut = normalize((model * vec4(vertexNormal, 0.0f)).xyz);
}