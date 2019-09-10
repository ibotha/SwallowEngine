#pragma once


namespace Swallow
{
	class AudioBuffer
	{
	public:
		AudioBuffer() = default;
		AudioBuffer(const AudioBuffer& rhs) = default;
		AudioBuffer& operator=(const AudioBuffer& rhs) = default;
		virtual	~AudioBuffer() = default;

		//I NEED STUFF!!!
		static Ref<AudioBuffer>	Create(const std::string& fn);
		virtual uint32_t	GetID() const = 0;
	private:
	};
}