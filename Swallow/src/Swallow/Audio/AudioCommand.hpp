#pragma once

#include "AudioAPI.hpp"

namespace Swallow
{
	class AudioCommand
	{
	public:
		inline static void Init() { s_AudioAPI->GetAPI(); }
	
	private:
		static AudioAPI* s_AudioAPI;
	};
}