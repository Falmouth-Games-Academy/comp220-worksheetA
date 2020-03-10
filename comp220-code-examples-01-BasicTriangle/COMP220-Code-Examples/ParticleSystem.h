#pragma once

#include "Base.h"
#include "IComponentParticle.h"
#include "Particle.h"
#include <ctime>

///<summary>
///Component used for controlling emission and behaviour of particles (2D or 3D)
///</summary>
class ParticleSystem : public IComponentParticle
{
public:
	ParticleSystem() {};
	~ParticleSystem();

	///<param name="maxParticles">Maximum number of particles that can be on the screen at the same time</param>
	///<param name="emissionRate">Number of particles emitted per second</param>
	///<param name="emissionDirection">Direction particles are emitted in</param>
	///<param name="emissionSpeed">Speed of emitted particles</param>
	///<param name="particleLifespan">Lifespan of individual particles</param>
	///<param name="material">Material assigned to particles</param>
	///<param name="mesh">Mesh assigned to particles. If none is assigned, particles are considered 2D</param>
	void Init(int maxParticles,
		float emissionRate,
		glm::vec3 emissionDirection,
		float emissionSpeed,
		float particleLifespan,
		Material* material,
		Mesh* mesh
	);

	void EmitParticle();
	void EmitParticles(int amount);

	void Reset();
	void Update() override;
	void RenderParticles(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) override;
private:
	std::vector<Particle*> particles;
	std::vector<Particle*> pooledParticles;
	int maxParticles;
	float emissionRate;
	float particleLifespan;
	clock_t lastEmission;
	clock_t lastUpdate;
	glm::vec3 emissionDirection;
	float emissionSpeed;
	Material* material = NULL;
	Mesh* mesh = NULL;
};