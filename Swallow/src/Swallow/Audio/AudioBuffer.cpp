#include "swpch.hpp"

#include "Platform/OpenAL/OpenALBuffer.hpp"
#include "AudioBuffer.hpp"
#include "Audio.hpp"
#include "AudioAPI.hpp"

namespace Swallow
{
	Ref<AudioBuffer> AudioBuffer::Create(const std::string &fn)
	{
		switch (Audio::GetAPI())
		{
		case AudioAPI::API::None:
			return nullptr;
		case AudioAPI::API::OpenAL:
			return std::make_shared<OpenALBuffer>(fn);
		default:
			break;
		}
		return nullptr;
	}
}