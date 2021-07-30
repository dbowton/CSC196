#pragma once

#include "Base/System.h"
#include <fmod.hpp>
#include <string>
#include <map>

namespace dwb
{
	class AudioSystem : public System
	{
		public:
			void StartUp();
			void ShutDown();
			void Update(float dt);
			void AddAudio(const std::string& name, const std::string& filename);
			void PlayAudio(const std::string& name);
	
		private:
			FMOD::System* fmodSystem;
			std::map<std::string, FMOD::Sound*> sounds; 
	}; 
}