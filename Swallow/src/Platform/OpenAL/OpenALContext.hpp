#pragma once

#include "Swallow/Audio/AudioContext.hpp"

namespace Swallow
{
	class OpenALContext : public AudioContext
	{
	public:
		OpenALContext();
		virtual void	Init() override;
	
	private:
		OpenALContext(const OpenALContext&) = default;
		OpenALContext& operator=(const OpenALContext&) = default;
	};
}