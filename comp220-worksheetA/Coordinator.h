#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

class Coordinator
{
public:
	void Init()
	{
		co_entityManager = std::make_unique<EntityManager>();
		co_componentManager = std::make_unique<ComponentManager>();
		co_systemManager = std::make_unique<SystemManager>();
	}

	Entity CreateEntity()
	{
		return co_entityManager->CreateEntity();
	}
	void DestroyEntity(Entity entity)
	{
		co_entityManager->DestroyEntity(entity);
		co_componentManager->EntityDestroyed(entity);
		co_systemManager->EntityDestroyed(entity);
	}
	
	template<typename T>
	void RegisterComponent()
	{
		co_componentManager->RegisterComponent<T>();
	}
	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		co_componentManager->AddComponent<T>(entity, component);

		auto signature = co_entityManager->GetSignature(entity);
		signature.set(co_componentManager->GetComponentType<T>(), true);
		co_entityManager->SetSignature(entity, signature);

		co_systemManager->EntitySignatureChanged(entity, signature);
	}
	template<typename T>
	void RemoveComponent(Entity entity)
	{
		co_componentManager->RemoveComponent<T>(entity);

		auto signature = co_entityManager->GetSignature(entity);
		signature.set(co_componentManager->GetComponentType<T>(), false);
		co_entityManager->SetSignature(entity, signature);
		co_systemManager->EntitySignatureChanged(entity, signature);
	}
	template<typename T>
	T& GetComponent(Entity entity)
	{
		return co_componentManager->GetComponent<T>(entity);
	}
	template<typename T>
	T* GetComponentPtr(Entity entity)
	{
		return co_componentManager->GetComponentPtr<T>(entity);
	}
	template<typename T>
	ComponentType GetComponentType()
	{
		return co_componentManager->GetComponentType<T>();
	}

	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return co_systemManager->RegisterSystem<T>();
	}
	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		co_systemManager->SetSignatures<T>(signature);
	}
private:

protected:
	std::unique_ptr<EntityManager> co_entityManager;
	std::unique_ptr<ComponentManager> co_componentManager;
	std::unique_ptr<SystemManager> co_systemManager;
};