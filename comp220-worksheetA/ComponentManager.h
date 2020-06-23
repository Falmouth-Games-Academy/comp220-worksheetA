#pragma once
#include <assert.h>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "ComponentType.h"
#include "ComponentArray.h"

class ComponentManager
{
public:
	template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		assert(cm_componentType.find(typeName) == cm_componentType.end() && "Component already registered.");

		cm_componentType.insert({ typeName, cm_nextComponentType });
		cm_componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		std::cout << "Component " << typeName << " registered." << std::endl;

		++cm_nextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();

		return cm_componentType[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}
	template<typename T>
	T& GetComponent(Entity entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : cm_componentArrays)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}
	
private:
	std::unordered_map<const char*, ComponentType> cm_componentType{};
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> cm_componentArrays{};
	ComponentType cm_nextComponentType;

	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* typeName = typeid(T).name();

		return std::static_pointer_cast<ComponentArray<T>>(cm_componentArrays[typeName]);
	}
};