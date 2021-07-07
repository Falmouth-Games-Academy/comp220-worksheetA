#include "Rigidbody.h"

Rigidbody::Rigidbody()
{
}

Rigidbody::~Rigidbody()
{
	if (rigidBodyMotionState)
	{
		delete rigidBodyMotionState;
		rigidBodyMotionState = nullptr;
	}

	if (rigidBodyInfo)
	{
		delete rigidBodyInfo;
		rigidBodyInfo = nullptr;
	}

	if (rigidBody)
	{
		delete rigidBody;
		rigidBody = nullptr;
	}
}

void Rigidbody::Init(PhysicsContext* physicsContext, btCollisionShape* collider, btScalar mass)
{
	this->physicsContext = physicsContext;

	// Create collision shape
	collisionShape = collider;

	this->mass = mass;

	colliderTransform = new btTransform();
	colliderTransform->setIdentity();
	colliderTransform->setOrigin(glmToBulletVec3(transform->Position()));

	collisionShape->calculateLocalInertia(this->mass, localInertia);

	// Actual rigidbody
	rigidBodyMotionState = new btDefaultMotionState(colliderTransform->getIdentity());
	rigidBodyInfo = new btRigidBody::btRigidBodyConstructionInfo(this->mass, rigidBodyMotionState, collisionShape, localInertia);
	rigidBody = new btRigidBody(*rigidBodyInfo);

	// Add rigidBody to dynamic world
	physicsContext->AddRigidBodyToWorld(rigidBody);

	UpdatePhysicsContext();
}

void Rigidbody::UpdatePhysicsComponent()
{
	rigidBodyMotionState = rigidBody->getMotionState();
	rigidBodyMotionState->getWorldTransform(currentTransform);

	transform->MoveTo(BulletToGlmVec3(currentTransform.getOrigin()));
}

void Rigidbody::UpdatePhysicsContext()
{
	rigidBodyMotionState = rigidBody->getMotionState();
	rigidBodyMotionState->getWorldTransform(currentTransform);

	currentTransform.setOrigin(glmToBulletVec3(transform->Position()));
	rigidBodyMotionState->setWorldTransform(currentTransform);
	rigidBody->setMotionState(rigidBodyMotionState);
}
