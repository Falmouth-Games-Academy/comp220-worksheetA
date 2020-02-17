#include "Model.h"

void Model::Init(const std::vector<GLfloat>& inVertices, const GLuint& inProgram)
{
	shaderProgram = inProgram;
	vertices = inVertices;

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
}

void Model::Render()
{
	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,
		3,	// Number of components that make up a vertex
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
	glDisableVertexAttribArray(0);
}
