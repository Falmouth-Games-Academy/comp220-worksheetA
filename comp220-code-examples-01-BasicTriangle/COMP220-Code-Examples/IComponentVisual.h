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
class IComponentVisual : public IComponent
{
public:
	IComponentVisual() {};
	virtual ~IComponentVisual() override {};

	// Runs every loop
	virtual void Update() override {};
	// Also runs every loop for render purposes
	virtual void Render() {};
protected:
	const char* componentType = "visual";
};