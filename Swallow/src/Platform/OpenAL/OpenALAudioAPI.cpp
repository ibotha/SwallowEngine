#include "swpch.hpp"
#include "OpenALAudioAPI.hpp"

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"

namespace Swallow
{
	OpenALAudioAPI::OpenALAudioAPI()
	{
		//TODO: uhm?
	}

	OpenALAudioAPI::~OpenALAudioAPI()
	{
	}

	void OpenALAudioAPI::Init()
	{
		m_At = glm::vec3(0, 0, -1.0);
		m_Up = glm::vec3(0, 1, 0);
		alListener3i(AL_POSITION, 0, 0, 0);
		float	x[] = {m_At.x, m_At.y, m_At.z,  m_Up.x, m_Up.y, m_Up.z};
		alListenerfv(AL_ORIENTATION, x);
		alListener3f(AL_VELOCITY, 0, 0, 0);
		alDistanceModel(AL_INVERSE_DISTANCE);
	}

	void OpenALAudioAPI::SetGain(float gain)
	{
		alListenerf(AL_GAIN, gain);
	}

	void OpenALAudioAPI::SetPosition(const glm::vec3& pos)
	{
		alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
	}

	
	void OpenALAudioAPI::SetVelocity(const glm::vec3& vel)
	{
		alListener3f(AL_POSITION, vel.x, vel.y, vel.z);
	}

	void OpenALAudioAPI::SetAt(const glm::vec3& at)
	{
		m_At = at;
		float	x[] = {m_At.x, m_At.y, m_At.z,  m_Up.x, m_Up.y, m_Up.z};
		alListenerfv(AL_ORIENTATION, x);
	}

	void OpenALAudioAPI::SetUp(const glm::vec3& up)
	{
		m_Up = up;
		float	x[] = {m_At.x, m_At.y, m_At.z,  m_Up.x, m_Up.y, m_Up.z};
		alListenerfv(AL_ORIENTATION, x);
	}

}

