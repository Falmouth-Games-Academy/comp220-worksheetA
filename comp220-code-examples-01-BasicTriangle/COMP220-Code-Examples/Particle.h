#pragma once

#include "Base.h"
#include "Components.h"

class Particle
{
public:
	Particle(glm::vec3 position, glm::vec3 velocity, GLfloat lifespan, Mesh &mesh, Material &material);
	~Particle();

	void Reset(glm::vec3 position, GLfloat lifespan);

	void Update();
	void Render(Camera* camera);
private:
	GLfloat lifespan;
	Transform* transform;
	MeshRenderer* meshRenderer;
	glm::vec3 velocity;
};