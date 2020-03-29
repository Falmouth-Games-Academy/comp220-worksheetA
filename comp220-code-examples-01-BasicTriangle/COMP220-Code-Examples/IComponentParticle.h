#pragma once

#include "Base.h"
#include "GLUtils.h"
#include "Transform.h"
#include "IComponent.h"

using namespace GLU;

// GameObject component system
// problem with enums is they are compile time
// Runtime

// Consider having a separate material system
// And a separate shader -> enumerate all shaders

///<summary>
/// Interface for implementing particle related components
///</summary>
class IComponentParticle : public IComponent
{
public:
	IComponentParticle() {};
	virtual ~IComponentParticle() override {};

	// Runs every loop
	virtual void Update() override {};

	virtual void RenderParticles(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition=glm::vec3(0)) {};
protected:
	const char* componentType = "particle";
};