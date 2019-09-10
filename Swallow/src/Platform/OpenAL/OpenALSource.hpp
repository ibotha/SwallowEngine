#pragma once

#include "Swallow/Audio/AudioSource.hpp"

namespace Swallow
{
	class OpenALSource : public AudioSource
	{
		public:
			OpenALSource();
			OpenALSource(const OpenALSource& rhs) = default;
			OpenALSource &operator=(const OpenALSource& rhs) = default;
			virtual ~OpenALSource();

			virtual void SetLooping(bool looping) override;
			virtual void SetPosition(const glm::vec3 &position) override;
			virtual void SetVelocity(const glm::vec3 &velocity) override;

			virtual glm::vec3 GetPosition() const override;
			virtual glm::vec3 GetVelocity() const override;

			virtual void Play(const Ref<AudioBuffer>& buffer) override;

		private:

			uint32_t m_Id;
	};
}