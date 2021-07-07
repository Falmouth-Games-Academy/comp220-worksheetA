#include "Physics.h"

PhysicsContext::PhysicsContext()
{
}

PhysicsContext::~PhysicsContext()
{
	if (dynamicWorld)
	{
		delete dynamicWorld;
		dynamicWorld = nullptr;
	}
	if (collisionSolver)
	{
		delete collisionSolver;
		collisionSolver = nullptr;
	}
	if (collisionBroadphase)
	{
		delete collisionBroadphase;
		collisionBroadphase = nullptr;
	}
	if (collisionDispatcher)
	{
		delete collisionDispatcher;
		collisionDispatcher = nullptr;
	}
	if (collisionConfig)
	{
		delete collisionConfig;
		collisionConfig = nullptr;
	}
}

void PhysicsContext::Init()
{
	collisionConfig = new btDefaultCollisionConfiguration();
	collisionDispatcher = new btCollisionDispatcher(collisionConfig);
	collisionBroadphase = new btDbvtBroadphase();
	collisionSolver = new btSequentialImpulseConstraintSolver();
	dynamicWorld = new btDiscreteDynamicsWorld(collisionDispatcher, collisionBroadphase, collisionSolver, collisionConfig);
}

void PhysicsContext::UpdatePhysics()
{
	if (dynamicWorld)
		dynamicWorld->stepSimulation(FIXEDDELTATIME, 10);
}

void PhysicsContext::AddRigidBodyToWorld(btRigidBody* rigidBody)
{
	if(dynamicWorld && rigidBody)
		dynamicWorld->addRigidBody(rigidBody);
}

void PhysicsContext::RemoveRigidBodyFromWorld(btRigidBody* rigidBody)
{
	if(dynamicWorld && rigidBody)
		dynamicWorld->removeRigidBody(rigidBody);
}
