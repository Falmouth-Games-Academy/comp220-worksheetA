#pragma once

#include <btBulletDynamicsCommon.h>

#define FIXEDDELTATIME 0.6

///<summary>
/// Class containing physics configurations and setup, as well as the task to update all physics-enabled objects
///</summary>
class PhysicsContext
{
public:
	PhysicsContext();
	~PhysicsContext();

	void Init();

	void UpdatePhysics();

	void AddRigidBodyToWorld(btRigidBody* rigidBody);
	void RemoveRigidBodyFromWorld(btRigidBody* rigidBody);

private:
	// Physics
	btDefaultCollisionConfiguration* collisionConfig;
	// Dispatcher
	btCollisionDispatcher* collisionDispatcher;
	// Broadphase
	btBroadphaseInterface* collisionBroadphase;
	// Solver
	btSequentialImpulseConstraintSolver* collisionSolver;
	// World
	btDiscreteDynamicsWorld* dynamicWorld;
};