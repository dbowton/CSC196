#pragma once
#include "core.h"

namespace dwb
{
	class System
	{
	public:
		virtual void StartUp() = 0;
		virtual void ShutDown() = 0;
		virtual void Update(float dt) = 0;
	};

	class GraphicsSystem : public System
	{
	public:
		virtual void Draw(Core::Graphics& graphics) = 0;
	};
}