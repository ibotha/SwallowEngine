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
		virtual void Init() override;
		virtual void SetPosition(const glm::vec3& pos) override;
		virtual void SetVelocity(const glm::vec3& vel) override;
		virtual void SetGain(float gain) override;
		virtual void SetAt(const glm::vec3& at) override;
		virtual void SetUp(const glm::vec3& up) override;

	private:
		glm::vec3 m_At;
		glm::vec3 m_Up;

	};
}