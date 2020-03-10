#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem()
{
	if (mesh != NULL)
	{
		delete this->mesh;
		this->mesh = NULL;
	}

	if (material != NULL)
	{
		delete this->material;
		this->material = NULL;
	}

	this->particles.clear();
	this->pooledParticles.clear();
}

void ParticleSystem::Init(int maxParticles, float emissionRate, glm::vec3 emissionDirection, float emissionSpeed, float particleLifespan, Material* material, Mesh* mesh)
{
	this->maxParticles = maxParticles;
	this->emissionRate = 1.0 / emissionRate;
	this->emissionDirection = emissionDirection;
	this->emissionSpeed = emissionSpeed;
	this->particleLifespan = particleLifespan;
	this->material = material;
	this->mesh = mesh;
	this->lastEmission = clock();
}

void ParticleSystem::EmitParticle()
{
	Particle* p = NULL;

	// If there are pooled particles that we can use instead of spawning new ones, use those
	if (this->pooledParticles.size() > 0)
	{
		// Get the last pooled particle
		p = this->pooledParticles.back();
		// And remove it from the pooled particles vector
		this->pooledParticles.pop_back();
		Transform t = *p->transform;
		// Then reset it to the emission position
		p->Reset(transform->Position(), this->particleLifespan);
		this->particles.push_back(p);
	}
	// Otherwise, create a new particle
	else
	{
		p = new Particle(transform->Position(), this->emissionDirection * this->emissionSpeed, this->particleLifespan, this->mesh, this->material);
		this->particles.push_back(p);
	}

	lastEmission = clock();
	lastUpdate = lastEmission;
}

void ParticleSystem::EmitParticles(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		EmitParticle();
	}
}

void ParticleSystem::Reset()
{
	this->particles.clear();
	this->pooledParticles.clear();
}

void ParticleSystem::Update()
{
	// Emit new particle if needed
	if ((float)(clock() - lastEmission) / CLOCKS_PER_SEC > emissionRate && particles.size() < this->maxParticles)
	{
		EmitParticle();
	}

	bool alive = true;
	// Move existing particles
	auto i = this->particles.begin();
	while (i != this->particles.end())
	{
		// Will thow an "expression must have pointer-to-class error without the brackets due to '->' having higher precedence than '*'
		(*i)->Update((float)(clock() - lastUpdate) / CLOCKS_PER_SEC, alive);

		if (!alive)
		{
			// Add particle to pool
			this->pooledParticles.push_back(*i);
			// And remove it from list of active particles
			i = this->particles.erase(i);
		}
	}

	lastUpdate = clock();
}

void ParticleSystem::RenderParticles(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	// Render all particles
	for (auto& i : this->particles)
	{
		i->Render(viewMatrix, projectionMatrix);
	}
}
