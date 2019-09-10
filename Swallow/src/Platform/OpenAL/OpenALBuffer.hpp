#pragma once


#include "swpch.hpp"
#include "Swallow/Audio/AudioBuffer.hpp"

namespace Swallow
{
	class OpenALBuffer: public AudioBuffer
	{
	private:
		uint32_t		m_Id;
	public:
		OpenALBuffer(const std::string& fn);
		OpenALBuffer(const OpenALBuffer&) = default;
		OpenALBuffer &operator=(const OpenALBuffer&) = default;

		virtual uint32_t GetID() const override { return m_Id; }
		~OpenALBuffer();
	};
}