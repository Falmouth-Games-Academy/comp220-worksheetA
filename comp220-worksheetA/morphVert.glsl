#version 330 core
// Look at the GL Attribute stuff in main.cpp /* */
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexFinalPosition;

uniform mat4 modelMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projectionMatrix = mat4(1.0f);

out vec4 vertexColourOut;

uniform float morphBlendFactor = 0.0f;

void main()
{
	vec3 morphPosition = mix(vertexPosition, vertexFinalPosition.xyz, clamp(morphBlendFactor, 0.0f, 1.0f));

	mat4 MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;

	vertexColourOut = vec4(1.0f,1.0f,1.0f,1.0f);

	gl_Position = MVPMatrix * vec4(morphPosition.xyz, 1.0f);
}