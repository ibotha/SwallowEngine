#pragma once

#include "SoundElement.hpp"

namespace Swallow
{
	class AudioBuffer
	{
	public:
		virtual void	Init() = 0;
		virtual void	Destory() = 0;

		virtual void	Play() = 0;
		virtual void	Pause() = 0;
		virtual			~AudioBuffer(){}

		static Ref<AudioBuffer>	Create();
	private:
		SoundElement	element;
	};
}