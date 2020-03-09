#include "Particle.h"

Particle::Particle(glm::vec3 position, glm::vec3 velocity, GLfloat lifespan, Mesh& mesh, Material& material)
{
	this->transform = new Transform();
	this->transform->MoveTo(position);

	this->velocity = velocity;

	this->lifespan = lifespan;

	this->meshRenderer = new MeshRenderer();
	this->meshRenderer->mesh = &mesh;
	this->meshRenderer->materials.push_back(material);

	this->meshRenderer->SetTransform(this->transform);
}

Particle::~Particle()
{
	delete meshRenderer;
	meshRenderer = NULL;

	delete transform;
	transform = NULL;
}

void Particle::Reset(glm::vec3 position, GLfloat lifespan)
{
	this->transform->MoveTo(position);
	this->lifespan = lifespan;
}

void Particle::Update()
{
	this->transform->Move(velocity);
}

void Particle::Render(Camera* camera)
{
	this->meshRenderer->Render(camera);
}
