#include "EntityManager.h"

EntityManager::EntityManager()
{
	em_LivingEntities = 0;
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		em_AvailableEntities.push(entity);
}

EntityManager::~EntityManager()
{
	em_AvailableEntities.empty();
	em_Signatures.empty();
	em_LivingEntities = NULL;
}

Entity EntityManager::CreateEntity()
{
	assert(em_LivingEntities < MAX_ENTITIES && "Cull the cattle");
	Entity id = em_AvailableEntities.front();
	em_AvailableEntities.pop();
	return id;
}

Entity EntityManager::CreateEntity(Signature signature)
{
	assert(em_LivingEntities < MAX_ENTITIES && "Cull the cattle");
	Entity id = em_AvailableEntities.front();
	em_AvailableEntities.pop();
	SetSignature(id, signature);

	return id;
}

void EntityManager::DestroyEntity(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity is far beyond our power!!!");

	em_Signatures[entity].reset();

	em_AvailableEntities.push(entity);
	--em_LivingEntities;
}

void EntityManager::SetSignature(Entity entity, Signature signature)
{
	assert(entity < MAX_ENTITIES && "HE'S TOO POWERFUL!");
	em_Signatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity)
{
	assert(entity < MAX_ENTITIES && "OH GOOD HE'S GOING TO DESTROY US ALL!");
	return em_Signatures[entity];
}
