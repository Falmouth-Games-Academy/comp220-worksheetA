#pragma once
#include "Physics.h"
#include "IComponent.h"
#include "Base.h"

#include <btBulletDynamicsCommon.h>

///<summary>
/// Base class for all physics-related components, namely RigidBodies
///</summary>
class IComponentPhysics : public IComponent
{
public:
	IComponentPhysics() {};
	~IComponentPhysics()
	{
		if (collisionShape)
		{
			delete collisionShape;
			collisionShape = nullptr;
		}

		if (colliderTransform)
		{
			delete colliderTransform;
			colliderTransform = nullptr;
		}
	}

	virtual void Init(PhysicsContext* physicsContext, btCollisionShape* collider, btScalar mass=1)
	{
		this->physicsContext = physicsContext;
	}

	static btVector3 glmToBulletVec3(glm::vec3 vec3)
	{
		return btVector3(vec3.x, vec3.y, vec3.z);
	}

	static glm::vec3 BulletToGlmVec3(btVector3 vec3)
	{
		return glm::vec3(vec3.x(), vec3.y(), vec3.z());
	}

	virtual void UpdatePhysicsComponent() {};
protected:
	btCollisionShape* collisionShape = nullptr;
	btTransform* colliderTransform = nullptr;
	btTransform currentTransform;
	PhysicsContext* physicsContext = nullptr;
};