#include "Particle.h"

Particle::Particle(glm::vec3 position, glm::vec3 velocity, float lifespan, Mesh* mesh, Material* material)
{
	this->transform = new Transform();
	this->transform->MoveTo(position);

	this->velocity = velocity;

	this->lifespan = lifespan;

	this->meshRenderer = new MeshRenderer();
	this->meshRenderer->mesh = mesh;
	this->meshRenderer->materials.push_back(*material);

	this->transform = new Transform();
	this->transform->Scale(glm::vec3(0.2, 0.2, 0.2));

	this->meshRenderer->SetTransform(this->transform);
}

Particle::~Particle()
{
	delete meshRenderer;
	meshRenderer = NULL;

	delete transform;
	transform = NULL;

	delete transform;
	transform = NULL;
}

void Particle::Reset(glm::vec3 position, float lifespan)
{
	this->transform->Move(glm::vec3(0, -this->transform->Position().y, 0));
	this->lifespan = lifespan;
	this->active = true;
}

void Particle::Update(float timeSinceLastUpdate, bool& alive)
{
	if (active)
	{
		this->lifespan -= timeSinceLastUpdate;

		if (lifespan > 0)
		{
			this->transform->Move(velocity);
			alive = true;
		}
		else
		{
			alive = false;
			active = false;
		}
	}
}

void Particle::Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition)
{
	if(active)
		this->meshRenderer->Render(viewMatrix, projectionMatrix, cameraPosition);
}
