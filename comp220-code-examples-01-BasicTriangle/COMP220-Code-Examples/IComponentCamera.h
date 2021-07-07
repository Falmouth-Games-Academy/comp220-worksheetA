#pragma once

#include "Base.h"
#include "IComponent.h"

using namespace GLU;

// GameObject component system
// problem with enums is they are compile time
// Runtime

// Consider having a separate material system
// And a separate shader -> enumerate all shaders

///<summary>
/// Interface for implementing the component-based system
///</summary>
class IComponentCamera : public IComponent
{
public:
	IComponentCamera() {};
	virtual ~IComponentCamera() override {};

	// Runs every loop
	virtual void Update() override {};
	// Also runs every loop for rendering purposes
	virtual void RenderCamera() {};
protected:
	const char* componentType = "camera";
};