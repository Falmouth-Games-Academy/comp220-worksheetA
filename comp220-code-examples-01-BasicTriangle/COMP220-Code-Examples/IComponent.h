#pragma once

#include "Base.h"
#include "GLUtils.h"
#include "Transform.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace GLU;

class GameObject;
typedef std::string component_type;
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

	void SetOwner(GameObject* gameObject) { owner = gameObject; }
	GameObject* GetOwner() { return owner; }

	// Runs every update loop
	virtual void Update() {};
protected:
	const char* componentType = "";
	GameObject* owner;
};

// Base components should be described here i.e. transforms, etc
// These components are fundamental to the usage of the component system as other components will rely on them

