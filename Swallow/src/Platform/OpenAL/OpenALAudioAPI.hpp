#pragma once

#include "Swallow/Audio/AudioAPI.hpp"

namespace Swallow
{
	class OpenALAudioAPI : public AudioAPI
	{
	public:
		OpenALAudioAPI();
		OpenALAudioAPI(const OpenALAudioAPI&) = default;
		OpenALAudioAPI& operator=(const OpenALAudioAPI&) = default;
		virtual ~OpenALAudioAPI();

	private:
		virtual void Init() override;

	};
}