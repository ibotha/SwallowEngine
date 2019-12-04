#pragma once

namespace Swallow
{
	class AudioContext
	{
	public:
		virtual ~AudioContext() {}
		virtual void Init() = 0;
	};
}