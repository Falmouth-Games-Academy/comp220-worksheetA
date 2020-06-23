#pragma once
#include <assert.h>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "Signature.h"
#include "System.h"

class SystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		assert(sm_systems.find(typeName) == sm_systems.end() && "Registering a system more than once.");

		auto system = std::make_shared<T>();
		std::cout << "System " << typeName << " registered." << std::endl;
		sm_systems.insert({typeName, system});
		
		return system;

	}

	template<typename T>
	void SetSignatures(Signature signature)
	{
		{
			const char* typeName = typeid(T).name();

			assert(sm_systems.find(typeName) != sm_systems.end() && "System used before registration.");

			sm_signatures.insert({ typeName, signature });
		}
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : sm_systems)
		{
			auto const& system = pair.second;
			system->sy_Entities.erase(entity);
		}
	}

	void EntitySignatureChanged(Entity entity, Signature entitySignature)
	{
		for (auto const& pair : sm_systems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = sm_signatures[type];

			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->sy_Entities.insert(entity);
			}
			else
				system->sy_Entities.erase(entity);
		}
	}
private:

protected:
	std::unordered_map<const char*, Signature> sm_signatures{};
	std::unordered_map<const char*, std::shared_ptr<System>> sm_systems{};
};