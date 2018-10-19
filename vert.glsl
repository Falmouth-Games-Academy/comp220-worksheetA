#version 330 core

// look at main. cpp for the vertex attribute pointer

layout(location = 0) in vec3 vertexPos;

uniform vec3 changeLocation;
uniform mat4 modelMatrix=mat4(1.0f);
uniform mat4 ViewMatrix=mat4(1.0f);
uniform mat4 ProjectionMatrix=mat4(1.0f);




void main()
{

mat4 MVPMatrix = ProjectionMatrix* ViewMatrix* modelMatrix; 



gl_Position= MVPMatrix*vec4(vertexPos, 1.0f); 

}


//gl_Position = vec4(vertexPos, 1.0f);
//mat4 mvpPosition = MVPMatrix*vec4(vertexPos, 1.0f);