#pragma once

#include "AudioAPI.hpp"
#include "AudioBuffer.hpp"

namespace Swallow
{
	class Audio
	{
	public:
		Audio();
		Audio(const Audio&) = default;
		Audio& operator=(const Audio&) = default;
		~Audio();

		static void Init();
		static void Submit(const Ref<AudioBuffer>& object);

		inline  static AudioAPI::API GetAPI() { return AudioAPI::GetAPI(); }
	};
}