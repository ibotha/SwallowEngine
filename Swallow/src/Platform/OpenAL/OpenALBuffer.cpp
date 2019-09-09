#include "swpch.hpp"
#include "Swallow/Audio/AudioBuffer.hpp"
#include "Platform/OpenAL/OpenALContext.hpp"
#include "OpenALBuffer.hpp"

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"

namespace Swallow
{
	static	bool isBigEndian()
	{
		int a = 1;
		return !((char*)&a)[0];
	}

	static	int convertToInt(char* buffer, int len)
	{
		int a = 0;
		if (!isBigEndian())
			for (int i = 0; i<len; i++)
				((char*)&a)[i] = buffer[i];
		else
			for (int i = 0; i<len; i++)
				((char*)&a)[3 - i] = buffer[i];
		return a;
	}

	OpenALBuffer::OpenALBuffer(const std::string& fn)
	{
		
		unsigned int	bps;
		unsigned int	samplerate;
		unsigned int	chan;
		unsigned int	size;
		unsigned int	format;

		// char			*data;

		char buffer[4];
		std::ifstream in(fn, std::ios::binary);
		in.read(buffer, 4);
		if (strncmp(buffer, "RIFF", 4) != 0)
		{
			m_Id = -1;
			SW_CORE_WARN("Could not load audio file {}", fn);
			return;
		}
		in.read(buffer, 4);
		in.read(buffer, 4);      //WAVE
		in.read(buffer, 4);      //fmt
		in.read(buffer, 4);      //16
		in.read(buffer, 2);      //1
		in.read(buffer, 2);
		chan = convertToInt(buffer, 2);
		in.read(buffer, 4);
		samplerate = convertToInt(buffer, 4);
		in.read(buffer, 4);
		in.read(buffer, 2);
		in.read(buffer, 2);
		bps = convertToInt(buffer, 2);
		in.read(buffer, 4);      //data
		in.read(buffer, 4);
		size = convertToInt(buffer, 4);
		char* data = new char[size];
		in.read(data, size);

		auto device = alcOpenDevice(0);
		auto context = alcCreateContext(device, 0);
		alcMakeContextCurrent(context);

		alGenBuffers(1, &m_Id);

		if (chan == 1)
		{
			if (bps == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else {
				format = AL_FORMAT_MONO16;
			}
		}
		else {
			if (bps == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else {
				format = AL_FORMAT_STEREO16;
			}
		}
		alBufferData(this->m_Id, format, data, size, samplerate);

		unsigned int	source;
		alGenSources(1, &source);

		alSourcei(source, AL_BUFFER, this->m_Id);
		alSourcei(source, AL_LOOPING, AL_TRUE);

		alSourcePlay(source);
	}

	OpenALBuffer::~OpenALBuffer()
	{
		alDeleteBuffers(1, &this->m_Id);
	}
}