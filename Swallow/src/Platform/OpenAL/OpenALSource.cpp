#include "swpch.hpp"

#include "OpenALSource.hpp"

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"

namespace Swallow
{
	OpenALSource::OpenALSource()
	{
		alGenSources(1, &m_Id);
		alSourcef(m_Id, AL_GAIN, 1);
		alSourcef(m_Id, AL_PITCH, 1);
		alSourcef(m_Id,AL_ROLLOFF_FACTOR, 0.1f);
		alSourcef(m_Id,AL_REFERENCE_DISTANCE, 0.1f);
		alSourcef(m_Id,AL_MAX_DISTANCE, 1000.f);
	}

	OpenALSource::~OpenALSource()
	{
		alDeleteSources(1, &m_Id);
	}

	void OpenALSource::SetLooping(bool looping)
	{
		alSourcei(m_Id, AL_LOOPING, looping);
	}

	void OpenALSource::SetPosition(const glm::vec3 &position)
	{
		alSource3f(m_Id, AL_POSITION, position.x, position.y, position.z);
	}

	void OpenALSource::SetVelocity(const glm::vec3 &velocity)
	{
		alSource3f(m_Id, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	}

	void OpenALSource::SetGain(float gain)
	{
		alSourcef(m_Id, AL_GAIN, gain);
	}

	glm::vec3 OpenALSource::GetPosition() const
	{
		glm::vec3 retval;
		alGetSource3f(m_Id, AL_POSITION, &retval.x,&retval.y,&retval.z);
		return retval;
	}

	glm::vec3 OpenALSource::GetVelocity() const
	{
		glm::vec3 retval;
		alGetSource3f(m_Id, AL_VELOCITY, &retval.x,&retval.y,&retval.z);
		return retval;
	}

	void OpenALSource::SetBuffer(const Ref<AudioBuffer>& buffer)
	{

		alSourcei(m_Id, AL_BUFFER, buffer->GetID());
	}

	void OpenALSource::Pause()
	{
		alSourcePause(m_Id);
	}

	void OpenALSource::Stop()
	{
		alSourceStop(m_Id);
	}

	void OpenALSource::Play()
	{
		alSourcePlay(m_Id);
	}


}