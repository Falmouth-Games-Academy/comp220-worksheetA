#pragma once

#include "Base.h"
#include "GLUtils.h"

using namespace GLU;

// GameObject component system
// problem with enums is they are compile time
// Runtime

// Consider having a separate material system
// And a separate shader -> enumerate all shaders

///<summary>
/// Interface for implementing the component-based system
///</summary>
class IComponent
{
public:
	IComponent() {};
	virtual ~IComponent() {};

	// Returns the type of component
	const char* GetComponentType() { return componentType; };

	// Runs every update loop
	virtual void Update() {};
protected:
	const char* componentType = "";
};

// Base components should be described here i.e. transforms, etc
// These components are fundamental to the usage of the component system as other components will rely on them

class Transform : public IComponent
{
public:
	Transform() {};
	virtual ~Transform() {};
};