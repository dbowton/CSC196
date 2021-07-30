#pragma once
#include <string>
#include "Base/System.h"
#include <functional>
#include <map>
#include <list>
#include <variant>

namespace dwb
{
	struct Event
	{
		std::string name;
		std::variant<int, bool, float, std::string> data;
	};

	class EventSystem : public System
	{
	public:
		using function_t = std::function<void(const Event&)>;

		virtual void StartUp() override;
		virtual void ShutDown() override;
		virtual void Update(float dt) override;

		void Subscribe(const std::string& name, function_t function);
		void Notify(const Event& event);

	private:
		struct Observer
		{
			function_t function;
		};

	private:
		std::map<std::string, std::list<Observer>> observers;
	};
}