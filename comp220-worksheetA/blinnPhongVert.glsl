#version 330 core
// Look at the GL Attribute stuff in main.cpp /* */
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColour;
layout(location = 2) in vec2 vertexTextureCoord;
layout(location = 3) in vec3 vertexNormal;

uniform mat4 modelMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projectionMatrix = mat4(1.0f);
uniform vec3 cameraPosition;

out vec4 vertexColourOut;
out vec2 vertexTextureCoordOut;
out vec3 vertexNormalOut;
out vec3 viewDirection;

void main()
{
	mat4 MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;

	vec4 vertexWorldPosition = modelMatrix * vec4(vertexPosition, 1.0f);

	vertexColourOut = vertexColour;
	vertexTextureCoordOut = vertexTextureCoord;
	vertexNormalOut = vertexNormal;
	viewDirection = normalize(cameraPosition - vertexWorldPosition.xyz); // normalize = simplified

	gl_Position = MVPMatrix * vec4(vertexPosition, 1.0f);
}
