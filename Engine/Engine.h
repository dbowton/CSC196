#pragma once
#define NOMINMAX

//Base
#include "Base/Actor.h"
#include "Base/Object.h"
#include "Base/System.h"

//Systems
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/EventSystem.h"
#include "Framework/ResourceSystem.h"

//Graphics
#include "Graphics/Shape.h"
#include "Graphics/Renderer.h"

#include "Base/Scene.h"

//Math
#include "Math/Color.h"
#include "Math/MathUtils.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"

#include "core.h"
#include <vector>
#include <algorithm>
#include <memory>

namespace dwb
{
	class Engine
	{
	public:
		void StartUp();
		void ShutDown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		template<typename T>
		T* Get();

	private:
		std::vector<std::unique_ptr<System>> systems;
	};
	
	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}

		return nullptr;
	}
}