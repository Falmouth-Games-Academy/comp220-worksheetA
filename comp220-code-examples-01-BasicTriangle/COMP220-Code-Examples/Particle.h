#pragma once

#include "Base.h"
#include "MeshRenderer.h"

class Particle
{
public:
	Particle(glm::vec3 position, glm::vec3 velocity, float lifespan, Mesh *mesh, Material *material);
	~Particle();

	void Reset(glm::vec3 position, float lifespan);

	void Update(float timeSinceLastUpdate, bool &alive);
	void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	bool active = true;
public:
	float lifespan;
	Transform* transform;
	MeshRenderer* meshRenderer;
	glm::vec3 velocity;
};