#pragma once


namespace Swallow
{
	class AudioBuffer
	{
	public:
		AudioBuffer()=default;
		virtual			~AudioBuffer(){}

		//I NEED STUFF!!!
		static Ref<AudioBuffer>	Create(const std::string& fn);
		virtual uint32_t	GetID() = 0;
	private:
	};
}