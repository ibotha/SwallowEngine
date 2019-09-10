#include "swpch.hpp"

#include "Audio.hpp"
#include "AudioSource.hpp"

#include "Platform/OpenAL/OpenALSource.hpp"

namespace Swallow
{
	Ref<AudioSource> AudioSource::Create()
	{
		switch (Audio::GetAPI())
		{
		case AudioAPI::API::None:
			return nullptr;
		case AudioAPI::API::OpenAL:
			return std::make_shared<OpenALSource>();
		default:
			break;
		}
		return nullptr;
	}
}