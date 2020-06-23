#pragma once
#include <assert.h>
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <list>
#include <vector>
#include <memory>
#include <unordered_map>

#include "Coordinator.h"

#include "DebugSystem.h"
#include "WindowUpdateSystem.h"
#include "MeshSystem.h"
#include "TextureSystem.h"
#include "CameraSystem.h"
#include "ShaderSystem.h"

#include "Vertex.h"
#include "WindowComponent.h"
#include "DebugComponent.h"
#include "MeshComponent.h"
#include "MeshCollectionComponent.h"
#include "CameraComponent.h"
#include "Texture.h"

namespace ByGL
{
	class Application
	{
	public:
		Application();
		~Application();
		int Init();
		int Run();

	private:
		void Events();
		/// <summary>Register all componentes needed in the application.</summary>
		///
		///
		///
		///
		void RegisterComponents();
		std::vector<Signature> AddSignature(std::vector<Signature> signatures, ComponentType newSignature);
		int Quit();
		std::unique_ptr<Coordinator> coordinator;
		SDL_Event ev;
		bool running;

		#pragma region Template Functions
		template<typename T>
		auto RegisterSystems(std::vector<Signature> signatures)
		{
			std::shared_ptr<T> newSystem = coordinator->RegisterSystem<T>();
			for (int i = 0; i < signatures.size(); i++)
			{
				coordinator->SetSystemSignature<T>(signatures[i]);
				std::cout << "Signature reisgered." << std::endl;
			}
			signatures.clear();
			return newSystem;
		}
		template<typename T>
		auto RegisterSystems()
		{
			std::shared_ptr<T> newSystem = coordinator->RegisterSystem<T>();
			return newSystem;
		}

		template<typename T>
		void SetSystemSignatures(std::vector<Signature> signatures, std::shared_ptr<T> system)
		{
			for (size_t i = 0; i < signatures.size(); i++)
			{
				coordinator->SetSystemSignature<T>(signatures[i]);
			}
		}
		#pragma endregion
	protected:

	};
}