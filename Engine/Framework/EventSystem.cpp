#include "EventSystem.h"

namespace dwb
{
	void EventSystem::StartUp()
	{
	}
	void EventSystem::ShutDown()
	{
	}
	void EventSystem::Update(float dt)
	{
	}
	void EventSystem::Subscribe(const std::string& name, function_t function)
	{
		Observer observer;
		observer.function = function;

		observers[name].push_back(observer);
	}
	void EventSystem::Notify(const Event& event)
	{
		auto& eventObservers = observers[event.name];
	
		for (auto& observer : eventObservers)
		{
			observer.function(event);
		}
	}
}