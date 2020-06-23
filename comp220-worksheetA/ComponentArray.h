#pragma once
#include "Entity.h"
#include <array>
#include <assert.h>
#include <unordered_map>
///<summary>
/// Interface for the component array
///</summary>
class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
	void InsertData(Entity entity, T component)
	{
		assert(ca_EntityToIndexMap.find(entity) == ca_EntityToIndexMap.end() && "Existing component, no data added.");

		size_t newIndex = ca_Size;
		ca_EntityToIndexMap[entity] = newIndex;
		ca_IndexToEntityMap[newIndex] = entity;
		ca_ComponentArray[newIndex] = component;
		++ca_Size;
	}
	void RemoveData(Entity entity)
	{
		assert(ca_EntityToIndexMap.find(entity) != ca_EntityToIndexMap.end() && "Non existant component, no data deleted.");

		size_t indexOfRemovedEntity = ca_EntityToIndexMap[entity];
		size_t indexOfLastElement = ca_Size - 1;
		ca_ComponentArray[indexOfRemovedEntity] = ca_ComponentArray[indexOfLastElement];

		Entity entityOfLastElement = ca_IndexToEntityMap[indexOfLastElement];
		ca_EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		ca_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		ca_EntityToIndexMap.erase(entity);
		ca_IndexToEntityMap.erase(indexOfLastElement);

		--ca_Size;
	}
	T& GetData(Entity entity)
	{
		assert(ca_EntityToIndexMap.find(entity) != ca_EntityToIndexMap.end() && "Non existant component, no data retrieved.");

		return ca_ComponentArray[ca_EntityToIndexMap[entity]];
	}
	T* GetDataPtr(Entity entity)
	{
		return &ca_ComponentArray[ca_EntityToIndexMap[entity]];
	}
	void EntityDestroyed(Entity entity) override
	{
		if (ca_EntityToIndexMap.find(entity) != ca_EntityToIndexMap.end())
			RemoveData(entity);
	}

private:
	std::array<T, MAX_ENTITIES> ca_ComponentArray;
	std::unordered_map<Entity, size_t> ca_EntityToIndexMap;
	std::unordered_map<size_t, Entity> ca_IndexToEntityMap;

	size_t ca_Size;
};
