#include "Particle.h"

Particle::Particle(glm::vec3 position, glm::vec3 velocity, float lifespan, Mesh* mesh, Material* material, PhysicsContext* physicsContext)
{
	this->transform = new Transform();
	this->transform->MoveTo(position);
	this->resetPosition = position;

	this->velocity = velocity;

	this->lifespan = lifespan;

	this->meshRenderer = new MeshRenderer();
	this->meshRenderer->mesh = mesh;
	this->meshRenderer->materials.push_back(*material);

	this->transform = new Transform();
	this->transform->Scale(glm::vec3(0.25, 0.25, 0.25));

	this->meshRenderer->SetTransform(this->transform);

	if (physicsContext)
	{
		this->rigidBody = new Rigidbody();
		this->rigidBody->SetTransform(this->transform);
		this->rigidBody->Init(physicsContext, new btSphereShape(0.25f), 0.01);
	}
}

Particle::~Particle()
{
	delete meshRenderer;
	meshRenderer = NULL;

	delete transform;
	transform = NULL;

	delete transform;
	transform = NULL;

	if (rigidBody != NULL)
	{
		rigidBody->Destroy();

		delete rigidBody;
		rigidBody = NULL;
	}
}

void Particle::Reset(glm::vec3 position, float lifespan)
{
	this->transform->MoveTo(resetPosition);
	this->lifespan = lifespan;
	this->active = true;

	if (rigidBody)
	{
		PhysicsContext* p = rigidBody->GetPhysicsContext();

		this->rigidBody->SetTransform(this->transform);
		this->rigidBody->Init(p, new btSphereShape(0.25), 0.01);

		p = nullptr;
	}
}

void Particle::UpdateParticlePhysicsContext()
{
	if (rigidBody)
		rigidBody->UpdatePhysicsContext();
}

void Particle::UpdateParticlePhysics()
{
	if(rigidBody)
		rigidBody->UpdatePhysicsComponent();
}

void Particle::Update(float timeSinceLastUpdate, bool& alive)
{
	if (active)
	{
		this->lifespan -= timeSinceLastUpdate;

		if (lifespan > 0)
		{
			if (!rigidBody)
				this->transform->Move(velocity);
			else
				this->rigidBody->rigidBody->applyCentralForce(Rigidbody::glmToBulletVec3(velocity));
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
