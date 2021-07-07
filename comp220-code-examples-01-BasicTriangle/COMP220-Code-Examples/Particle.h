#pragma once

#include "Base.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"

class Particle
{
public:
	Particle(glm::vec3 position, glm::vec3 velocity, float lifespan, Mesh *mesh, Material *material, PhysicsContext* physicsContext);
	~Particle();

	void Reset(glm::vec3 position, float lifespan);
	
	void UpdateParticlePhysicsContext();
	void UpdateParticlePhysics();
	void Update(float timeSinceLastUpdate, bool &alive);
	void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition=glm::vec3(0));

	bool active = true;
public:
	float lifespan;
	glm::vec3 resetPosition;
	Transform* transform;
	MeshRenderer* meshRenderer;
	Rigidbody* rigidBody;
	glm::vec3 velocity;
};