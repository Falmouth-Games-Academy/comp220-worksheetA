#pragma once

#include "IComponentPhysics.h"

///<summary>
/// Component used for handling object-side physics
///</summary>
class Rigidbody : public IComponentPhysics
{
public:
	Rigidbody();
	~Rigidbody();

	void Destroy(){ physicsContext->RemoveRigidBodyFromWorld(rigidBody); }
	void Init(PhysicsContext* physicsContext, btCollisionShape* collider, btScalar mass=1) override;
	void UpdatePhysicsComponent() override;
	// Tell the physics context about any new position changes
	void UpdatePhysicsContext();
	void SetGravity(glm::vec3 value) { rigidBody->setGravity(glmToBulletVec3(value)); }

	PhysicsContext* GetPhysicsContext() { return physicsContext; }

	btMotionState* rigidBodyMotionState = nullptr;
	btRigidBody::btRigidBodyConstructionInfo* rigidBodyInfo = nullptr;
	btRigidBody* rigidBody = nullptr;
	
	btScalar mass = 0.3;
	btVector3 localInertia = btVector3(0, 0, 0);
};