#pragma once

#include "Swallow/Audio/AudioContext.hpp"
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"

namespace Swallow
{
	class OpenALContext : public AudioContext
	{
	public:
		OpenALContext(ALCcontext *context);
		OpenALContext(const OpenALContext&) = default;
		OpenALContext& operator=(const OpenALContext&) = default;
		virtual ~OpenALContext() = default;
		virtual void	Init() override;
	
	private:
		ALCcontext *m_Context;
	};
}