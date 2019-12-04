#pragma once
#include "AudioBuffer.hpp"

namespace Swallow
{
	class AudioSource
	{
		public:
			AudioSource() = default;
			AudioSource(const AudioSource& rhs) = default;
			AudioSource &operator=(const AudioSource& rhs) = default;
			virtual ~AudioSource() = default;

			virtual void SetLooping(bool looping) = 0;
			virtual void SetPosition(const glm::vec3 &position) = 0;
			virtual void SetVelocity(const glm::vec3 &velocity) = 0;
			virtual void SetGain(float gain) = 0;

			virtual glm::vec3 GetPosition() const = 0;
			virtual glm::vec3 GetVelocity() const = 0;

			virtual void SetBuffer(const Ref<AudioBuffer>& buffer) = 0;
			virtual void Pause() = 0;
			virtual void Play() = 0;
			virtual void Stop() = 0;

			static Ref<AudioSource> Create();
	};
}