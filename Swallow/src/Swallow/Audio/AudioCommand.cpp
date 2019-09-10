#include "swpch.hpp"
#include "AudioCommand.hpp"
#include "Platform/OpenAL/OpenALAudioAPI.hpp"

namespace Swallow
{
	AudioAPI* AudioCommand::s_AudioAPI = new OpenALAudioAPI();
}