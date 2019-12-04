#pragma once

#include "AudioAPI.hpp"

namespace Swallow
{
	class AudioCommand
	{
	public:
		inline static void Init() { s_AudioAPI->Init(); }

		inline static void SetPosition(const glm::vec3& pos) { s_AudioAPI->SetPosition(pos); }
		inline static void SetVelocity(const glm::vec3& pos) { s_AudioAPI->SetVelocity(pos); }
		inline static void SetGain(float gain) { s_AudioAPI->SetGain(gain); }
		inline static void SetAt(const glm::vec3& pos) { s_AudioAPI->SetAt(pos); }
		inline static void SetUp(const glm::vec3& pos) { s_AudioAPI->SetUp(pos); }
	
	private:
		static AudioAPI* s_AudioAPI;
	};
}