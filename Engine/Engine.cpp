#include "Engine.h"

namespace dwb
{
	void Engine::StartUp()
	{
		systems.push_back(std::make_unique<ParticleSystem>());
		systems.push_back(std::make_unique<AudioSystem>());
		systems.push_back(std::make_unique<EventSystem>());
		systems.push_back(std::make_unique<ResourceSystem>());

		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->StartUp(); });
	}
	void Engine::ShutDown()
	{
		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->ShutDown(); });
	}
	void Engine::Update(float dt)
	{
		std::for_each(systems.begin(), systems.end(), [dt](auto& system) {system->Update(dt); });
	}

	void Engine::Draw(Core::Graphics& graphics)
	{
		std::for_each(systems.begin(), systems.end(), [graphics](auto& system) mutable
			{
				if (dynamic_cast<GraphicsSystem*>(system.get()))
				{
					dynamic_cast<GraphicsSystem*>(system.get())->Draw(graphics);
				}
			});
	}
}