#pragma once
#include <queue>
#include <array>
#include <assert.h>
#include "Entity.h"
#include "Signature.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	Entity CreateEntity();
	Entity CreateEntity(Signature signature);
	void DestroyEntity(Entity entity);
	void SetSignature(Entity entity, Signature signature);
	Signature GetSignature(Entity entity);
private:
	std::queue<Entity> em_AvailableEntities{};

	std::array<Signature, MAX_ENTITIES> em_Signatures{};

	uint32_t em_LivingEntities;
protected:

};